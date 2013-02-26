package com.skoobalon.lander.game {
	
	import caurina.transitions.Tweener;
	import com.skoobalon.lander.components.FireballSet;
	import com.skoobalon.lander.game.art.GameLander;
	import com.skoobalon.lander.Lander;
	import com.skoobalon.lander.resources.LanderResources;
	import com.skoobalon.lander.resources.LanderColors;
	import com.skoobalon.lander.resources.LanderConstants;
	import com.skoobalon.lander.resources.LanderStrings;
	import com.skoobalon.lander.utilities.PixelPerfectCollision;
	import com.skoobalon.lander.utilities.TextFactory;
	import flash.display.DisplayObject;
	import flash.display.DisplayObjectContainer;
	import flash.display.MovieClip;
	import flash.display.Shape;
	import flash.display.Sprite;
	import flash.geom.Point;
	import flash.text.TextField;
	import flash.text.TextFieldAutoSize;
	import flash.text.TextFormat;
	import flash.text.TextFormatAlign;
	import mx.logging.ILogger;
	import mx.logging.Log;
	
	/**
	 * @author Steven Wallace
	 */
	public class GameView extends Sprite {
		
		/**
		 * @private
		 * Flex logger
		 */
		private static const LOG:ILogger = Log.getLogger("GameView");
		
		/**
		 * @private
		 * Global game resources
		 */
		private var _resources:LanderResources;
		
		/**
		 * @private
		 * Container for the action of the game
		 */
		private var _actionFrame:Sprite = new Sprite();
		
		/**
		 * @private
		 * The graphic for the lander
		 */
		private var _lander:GameLander = new GameLander();
		
		private var _lastKnownLevel:GameLevel;
		private var _fpsText:TextField = new TextField();
		private var _statusText1:TextField = new TextField();
		private var _statusText2:TextField = new TextField();
		private var _statusText3:TextField = new TextField();
		private var _scoreLabel:TextField = new TextField();
		private var _hiscoreLabel:TextField = new TextField();
		private var _fuelLabel:TextField = new TextField();
		private var _fuelBar:Shape = new Shape();
		private var _velocityBar:Shape = new Shape();
		private var _velocityZone:Shape = new Shape();
		private var _velocityMarker:Shape = new Shape();
		
		private var _targetZoomFactor:int = 0;
		public var fireballs:FireballSet = new FireballSet();
		
		public function GameView(resources:LanderResources) {
			_resources = resources;
			
			var actionMask:Shape = new Shape();
			actionMask.graphics.beginFill(0);
			actionMask.graphics.drawRect(0, 0, LanderConstants.ACTIONVIEW_W, LanderConstants.ACTIONVIEW_H);
			actionMask.graphics.endFill();
			_actionFrame.mask = actionMask;
			_actionFrame.addChild(fireballs);
			_actionFrame.addChild(_lander);
			addChild(_actionFrame);
			
			_fpsText.textColor = 0xFFFFFF;
			addChild(_fpsText);
			
			TextFactory.format( _statusText1, 
								18, 
								0xFFFFFF, 
								LanderConstants.ACTIONVIEW_W, 
								LanderConstants.TEXT_H, 
								TextFormatAlign.CENTER );
			_statusText1.y = LanderConstants.ACTIONVIEW_H / 2 - LanderConstants.TEXT_H;
			addChild(_statusText1);
			
			TextFactory.format( _statusText2, 
								18, 
								0xFFFFFF, 
								LanderConstants.ACTIONVIEW_W, 
								LanderConstants.TEXT_H, 
								TextFormatAlign.CENTER );
			_statusText2.y = LanderConstants.ACTIONVIEW_H / 2;
			addChild(_statusText2);
			
			TextFactory.format( _statusText3, 
								18, 
								0xFFFFFF, 
								LanderConstants.ACTIONVIEW_W, 
								LanderConstants.TEXT_H, 
								TextFormatAlign.CENTER );
			_statusText3.y = LanderConstants.ACTIONVIEW_H / 2 + LanderConstants.TEXT_H;
			addChild(_statusText3);
			
			_velocityBar.graphics.beginFill(LanderColors.VELOCITY_BAR);
			_velocityBar.graphics.drawRect(0, 0, 8, LanderConstants.SCREEN_H - 77);
			_velocityBar.graphics.endFill();
			_velocityBar.x = LanderConstants.SCREEN_W - 8;
			addChild(_velocityBar);
			
			_velocityZone.graphics.beginFill(LanderColors.VELOCITY_ZONE);
			_velocityZone.graphics.drawRect(0, 0, 8, 8);
			_velocityZone.graphics.endFill();
			_velocityZone.x = LanderConstants.SCREEN_W - 8;
			_velocityZone.y = LanderConstants.SCREEN_H / 2 - 4;
			addChild(_velocityZone);
			
			_velocityMarker.graphics.beginFill(0);
			_velocityMarker.graphics.drawRect(0, 0, 8, 1);
			_velocityMarker.graphics.endFill();
			_velocityMarker.x = _velocityBar.x;
			addChild(_velocityMarker);
			
			TextFactory.format( _scoreLabel, 
								8, 
								LanderColors.SCORE_TEXT, 
								LanderConstants.SCREEN_W, 
								LanderConstants.TEXT_H );
			_scoreLabel.y = LanderConstants.SCREEN_H - 20;
			addChild(_scoreLabel);
			
			TextFactory.format( _hiscoreLabel,
								8,
								LanderColors.SCORE_TEXT,
								LanderConstants.SCREEN_W,
								LanderConstants.TEXT_H );
			_hiscoreLabel.x = LanderConstants.SCREEN_W / 2;
			_hiscoreLabel.y = _scoreLabel.y;
			addChild(_hiscoreLabel);
			
			TextFactory.format( _fuelLabel,
								8,
								LanderColors.FUEL_TEXT,
								LanderConstants.SCREEN_W,
								LanderConstants.TEXT_H );
			_fuelLabel.y = LanderConstants.SCREEN_H - 11;
			_fuelLabel.text = "FUEL:";
			addChild(_fuelLabel);
			
			_fuelBar.graphics.beginFill(LanderColors.FUEL);
			_fuelBar.graphics.drawRect(0, 0, LanderConstants.SCREEN_W - 40, 8);
			_fuelBar.graphics.endFill();
			_fuelBar.x = 40;
			_fuelBar.y = LanderConstants.SCREEN_H - 8;
			addChild(_fuelBar);
		}
		
		public function updateViewForState(state:GameState):void {
			
			// If the level changed, change the background
			if (state.level != _lastKnownLevel) {
				if (_lastKnownLevel) {
					_actionFrame.removeChild(_lastKnownLevel);
				}
				
				_lastKnownLevel = state.level;
				
				LOG.debug("Adding a new level to the view");
				_actionFrame.addChildAt(_lastKnownLevel, 0);
			}
			
			_lander.x = state.position.x;
			_lander.y = state.position.y;
			
			if (state.isAlive && !state.outOfSky) {
				_velocityMarker.y = LanderConstants.SCREEN_H / 2  - 4 * _actionFrame.scaleY + state.velocity.y * _actionFrame.scaleY * 250 - 1;
				_statusText1.text = _statusText2.text = _statusText3.text = "";
			}
			_fuelBar.scaleX = state.fuel;
			
			_scoreLabel.text = LanderStrings.SCORE + state.score + " / " + state.scoreToBeat;
			_hiscoreLabel.text = LanderStrings.HISCORE + state.hiScore;
			
			// Set the status bars
			var statusBar:Vector.<TextField> = new Vector.<TextField>();
			statusBar.push(_statusText1, _statusText2, _statusText3);
			var statusIndex:int = 0;
			
			if (state.hasLanded) {
				statusBar[statusIndex++].text = LanderStrings.LAND_SUCCESSFUL;
				statusBar[statusIndex++].text = state.landingScore + " × " + state.landingMultiplier + " = " + (state.landingScore * state.landingMultiplier);
				if (state.score >= state.scoreToBeat) {
					statusBar[statusIndex++].text = LanderStrings.GOOD_JOB;
				}
			} else if (state.outOfSky) {
				statusBar[statusIndex++].text = LanderStrings.OUT_OF_SKY;
			}
			
			if (state.fuel <= 0.0) {
				statusBar[statusIndex++].text = LanderStrings.OUT_OF_FUEL;
				if (!state.isAlive) {
					statusBar[statusIndex++].text = LanderStrings.GAME_OVER;
				}
			}
		}
		
		public function addFireballsDown(power:Number, dt:Number):void {
			fireballs.add(
				power, 
				new Point(
					_lander.x + _lander.width / 2 + 1,
					_lander.y + _lander.height - 2),
				90,
				4,
				dt);
		}
		
		public function addFireballsLeft(power:Number, dt:Number):void {
			fireballs.add(
				power,
				new Point(_lander.x, _lander.y + _lander.height / 2 + 3 ),
				160,
				4,
				dt);
		}
		
		public function addFireballsRight(power:Number, dt:Number):void {
			fireballs.add(
				power,
				new Point(_lander.x + _lander.width, _lander.y + _lander.height / 2 + 3 ),
				30,
				4,
				dt);
		}
		
		public function isColliding(level:GameLevel):Boolean {
			if (level) {
				return PixelPerfectCollision.isColliding(_lander, level, _actionFrame, true);
			} else {
				return false;
			}
		}
		
		public function set fps(value:Number):void {
			_fpsText.text = int(value) + " fps";
		}
		
		public function get lander():GameLander {
			return _lander;
		}
		
		public function zoomTo(point:Point, magnification:int):void {
			if (Tweener.isTweening(_actionFrame)) {
				if (magnification != _targetZoomFactor) {
					Tweener.removeTweens(_actionFrame);
				} else {
					return;
				}
			} else if (magnification == _actionFrame.scaleX) {
				return;
			}
			
			LOG.debug("Tweening to {0} at {1}x", point, magnification);
			_targetZoomFactor = magnification;
			var transition:String = _actionFrame.scaleX < magnification ? "easeInQuad" : "easeOutQuad";
			Tweener.addTween(_actionFrame, {
				x: -point.x * magnification,
				y: -point.y * magnification,
				scaleX: magnification,
				scaleY: magnification,
				time: 1,
				transition: transition,
				onComplete: zoomTweenComplete } );
				
			Tweener.addTween(_velocityZone, {
				y: LanderConstants.SCREEN_H / 2 - 4 * magnification,
				scaleY: magnification,
				transition: transition,
				time: 1} );
				
			function zoomTweenComplete():void {
				_targetZoomFactor = 0;
			}
		}
		
	}

}
