package com.skoobalon.lander.game {
	import caurina.transitions.Tweener;
	import com.skoobalon.lander.components.FireballSet;
	import com.skoobalon.lander.components.LandingPad;
	import com.skoobalon.lander.resources.LanderConstants;
	import com.skoobalon.lander.resources.LanderResources;
	import flash.display.DisplayObject;
	import flash.events.Event;
	import flash.events.EventDispatcher;
	import flash.events.KeyboardEvent;
	import flash.geom.Point;
	import flash.geom.Rectangle;
	import flash.ui.Keyboard;
	import flash.utils.getTimer;
	import mx.collections.errors.ItemPendingError;
	import mx.logging.ILogger;
	import mx.logging.Log;
	
	/**
	 * @author Steven Wallace
	 */
	public class GameController extends EventDispatcher {
		
		private static const LOG:ILogger = Log.getLogger("GameController");
		
		private var _resources:LanderResources;
		private var _view:GameView;
		private var _state:GameState;
		private var _lastTick:int;
		private var _gameInProgress:Boolean = false;
		
		public function GameController(resources:LanderResources) {
			construct(resources);
		}
		
		private function construct(resources:LanderResources):void {
			_resources = resources;
			_view = new GameView(_resources);
		}
		
		public function get view():DisplayObject {
			return _view;
		}
		
		public function open():void {
			if (!_gameInProgress) {
				resetGame();
				_gameInProgress = true;
			}
			
			_lastTick = getTimer();
			_view.stage.addEventListener(Event.ENTER_FRAME, onEnterFrame);
			_view.stage.addEventListener(KeyboardEvent.KEY_DOWN, onKeyEvent);
			_view.stage.addEventListener(KeyboardEvent.KEY_UP, onKeyEvent);
		}
		
		private function resetGame():void {
			LOG.debug("Resetting");
			_state = new GameState();
			_state.level.initialize(_resources.config.getLevelDetails(0));
			LOG.debug("Level: {0}", _state.level);
		}
		
		public function close():void {
			_view.stage.removeEventListener(Event.ENTER_FRAME, onEnterFrame);
			_view.stage.removeEventListener(KeyboardEvent.KEY_DOWN, onKeyEvent);
			_view.stage.removeEventListener(KeyboardEvent.KEY_UP, onKeyEvent);
		}
		
		private function onEnterFrame(event:Event):void {
			var time:int = getTimer();
			//var dt:Number = 1 / _view.stage.frameRate;
			var dt:Number = (time - _lastTick) / 1000;
			_lastTick = time;
			if (dt > 0.25) {
				dt = 0.001;
			}
			
			// Add this frame to the fps counter
			_resources.fps.frame();
			_view.fps = _resources.fps.fps;
			
			// Always update the position unless we're on the ground, whether we show it or not
			if (!_state.hasLanded) {
				_state.position.x += _state.velocity.x * dt * 100;
				_state.position.y += _state.velocity.y * dt * 100;
				_state.velocity.y += GameConstants.GRAVITY * dt;
			}
			
			if (!_state.isAlive) {
				// We crashed
				if (time - _state.timeOfDeath < 1000) {
					_view.fireballs.add(
						10, 
						new Point(
							_state.position.x + Math.random() * _view.lander.width,
							_state.position.y + Math.random() * _view.lander.height),
						Math.random() * 360,
						2 + Math.random() * 3,
						dt);
				}
			} else {
				// We are alive
				// Update logic
				if (!_state.hasLanded) {
					// We've not landed
					// Check if we're still in sky
					if (!_state.outOfSky
					&& (_state.position.x > LanderConstants.ACTIONVIEW_W + _view.lander.width * 2
					|| _state.position.x < -_view.lander.width * 3
					|| _state.position.y > LanderConstants.ACTIONVIEW_H + _view.lander.height
					|| _state.position.y < -_view.lander.height * 3))
					{
						_state.outOfSky = true;
						_state.timeOfLeavingSky = time;
					}
					
					// Thrust
					if (_state.fuel > 0) {
						if (_state.thrustMaximum) {
							thrust(90, 50, dt);
							_view.addFireballsDown(10, dt);
						} else if (_state.thrustMedium) {
							thrust(90, 25, dt);
							_view.addFireballsDown(5, dt);
						} else if (_state.thrustMinimum) {
							thrust(90, 15, dt);
							_view.addFireballsDown(3, dt);
						}
						
						if (_state.thrustLeft) {
							thrust(160, 50, dt);
							_view.addFireballsLeft(10, dt);
						}
						if (_state.thrustRight) {
							thrust( 30, 50, dt);
							_view.addFireballsRight(10, dt);
						}
					}
				} else {
					// We've landed
					if (_state.score < _state.targetScore) {
						// Score is incrementing
						_state.score += 900 * dt;
						_state.fuel += 0.1 * dt;
						
						if (_state.score >= _state.targetScore) {
							_state.score = _state.targetScore;
							_state.timeOfLanding = getTimer();
						}
					} else {
						// Score is done incrementing
						if (time - _state.timeOfLanding > 1500) {
							if (_state.score < _state.scoreToBeat) {
								resetLevel();
							} else {
								// Load next level
								LOG.debug("Advancing to the next level.  Current level is: {0}", _state.level);
								var oldLevel:GameLevel = _state.level;
								_state.level = new GameLevel();
								_state.level.initialize(_resources.config.getLevelDetails(oldLevel.ordinal + 1));
								LOG.debug("Next level is: {0}", _state.level);
								_state.scoreToBeat += 8000;
								if (_state.scoreToBeat > _state.scoreToBeat) {
									_state.scoreToBeat = _state.score + 100;
								}
							}
						}
					}
				}
				
				_view.updateViewForState(_state);
			}
			
			if (_view.isColliding(_state.level) && _state.isAlive) {
				_state.isAlive = false;
				_state.timeOfDeath = time;
				_view.lander.visible = false;
			}
			
			zoomViewIfApplicable();
			landIfApplicable();
			
			_view.fireballs.update(dt);
		}
		
		private function thrust(angle:int, power:Number, dt:Number):void {
			_state.velocity.x += -Math.cos(angle * Math.PI / 180) * power * 0.004 * dt;
			_state.velocity.y += -Math.sin(angle * Math.PI / 180) * power * 0.004 * dt;
			_state.fuel -= 0.0004 * dt * power;
		}
		
		private function onKeyEvent(event:KeyboardEvent):void {
			var toggle:Boolean = event.type == KeyboardEvent.KEY_DOWN ? true : false;
			var now:int = getTimer();
			
			switch (String.fromCharCode(event.charCode)) {
				case "q":
				case "Q": {
					_state.thrustMaximum = toggle;
					break;
				}
				
				case "a":
				case "A": {
					_state.thrustMedium = toggle;
					break;
				}
				
				case "z":
				case "Z": {
					_state.thrustMinimum = toggle;
					break;
				}
			}
			
			switch (event.keyCode) {
				case Keyboard.LEFT:
					_state.thrustRight = toggle;
					break;
				
				case Keyboard.RIGHT:
					_state.thrustLeft = toggle;
					break;
				
				case Keyboard.F1:
					_state.velocity = new Point();
					_state.position = _state.level.zooms[_state.level.zooms.length - 1].add(new Point(LanderConstants.ZOOM_W / 2, LanderConstants.ZOOM_H / 2));
					break;
			}
			
			
			if ((!_state.isAlive && now - _state.timeOfDeath >= 1000)
			|| (_state.outOfSky && now - _state.timeOfLeavingSky >= 1000))
			{
				resetLevel();
			}
		}
		
		private function resetLevel():void {
			_view.lander.visible = true;
			_state.newLevelState();
		}
		
		private function zoomViewIfApplicable():void {
			if (!_state.isAlive) {
				return;
			}
			
			// Check if we're in a zoom region
			for each (var zoom:Point in _state.level.zooms) {
				var xx:int = zoom.x + LanderConstants.ZOOM_W - _view.lander.width;
				var yy:int = zoom.y + LanderConstants.ZOOM_H - _view.lander.height;
				
				if (_state.position.x >= zoom.x
				&& _state.position.x <= xx
				&& _state.position.y >= zoom.y
				&& _state.position.y <= yy) {
					_view.zoomTo(zoom, LanderConstants.ZOOM_FACTOR);
					return;
				}
			}
			
			_view.zoomTo(new Point(), 1);
		}
		
		private function landIfApplicable():void {
			if (_state.hasLanded) {
				return;
			}
			
			// Check if we're on a landing pad
			for each (var landingpad:LandingPad in _state.level.landingPads) {
				var xx:int = landingpad.x + int(landingpad.width) - _view.lander.width;
				
				if (int(_state.position.y + _view.lander.height) == landingpad.y
				&& _state.position.x >= landingpad.x 
				&& _state.position.x <= xx
				&& _state.velocity.y < 0.0348) {
					LOG.info("LANDED");
					_state.hasLanded = true;
					_state.timeOfLanding = getTimer();
					_state.landingMultiplier = landingpad.multiplier;
					// Gotta love this algorithm...
					_state.landingScore = Math.ceil(Math.abs(_state.velocity.y - 0.0348) * 28735);
					_state.targetScore = _state.score + _state.landingMultiplier * _state.landingScore;
				}
			}
		}
		
	}

}
