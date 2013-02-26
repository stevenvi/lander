package com.skoobalon.lander.game {
	import flash.geom.Point;
	
	/**
	 * Holds state variables for a game instance
	 * @author Steven Wallace
	 */
	public class GameState {
		
		public var level:GameLevel = new GameLevel();
		
		private var _score:int;
		public var hiScore:int;
		public var scoreToBeat:int;
		
		public var position:Point;
		public var velocity:Point;
		private var _fuel:Number;
		
		public var thrustMaximum:Boolean;
		public var thrustMedium:Boolean;
		public var thrustMinimum:Boolean;
		public var thrustLeft:Boolean;
		public var thrustRight:Boolean;
		
		public var isAlive:Boolean
		public var timeOfDeath:int;
		
		public var outOfSky:Boolean;
		public var timeOfLeavingSky:int;
		
		public var hasLanded:Boolean;		// Flags if we've landed
		public var timeOfLanding:int;		// The getTimer() value when we landed
		public var landingScore:int;		// Score earned from this landing
		public var landingMultiplier:int;	// Multiplier for pad we're on
		public var targetScore:int;			// The final score we should have after it all tallies up
		
		public function GameState() {
			newLevelState();
			score = 0;
			hiScore = 0;
			fuel = 1.0;
			scoreToBeat = 8000;
		}
		
		public function newLevelState():void {
			position = GameConstants.START_POSITION.clone();
			velocity = GameConstants.START_VELOCITY.clone();
			isAlive = true;
			hasLanded = false;
			outOfSky = false;
		}
		
		public function get fuel():Number {
			return _fuel;
		}
		
		public function set fuel(value:Number):void {
			_fuel = value;
			if (_fuel < 0) {
				_fuel = 0
			} else if (_fuel > 1) {
				_fuel = 1;
			}
		}
		
		public function get score():int {
			return _score;
		}
		
		public function set score(value:int):void {
			_score = value;
			if (_score > hiScore) {
				hiScore = _score;
			}
		}
		
	}

}
