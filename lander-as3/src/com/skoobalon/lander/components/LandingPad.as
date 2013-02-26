package com.skoobalon.lander.components {
	import flash.geom.Rectangle;
	
	/**
	 * Holds data for a landing pad
	 * @author Steven Wallace
	 */
	public class LandingPad {
		
		private var _x:int;
		private var _y:int;
		private var _width:int;
		private var _multiplier:int;
		
		public function LandingPad(x:int, y:int, width:int, multiplier:int) {
			_x = x;
			_y = y;
			_width = width;
			_multiplier = multiplier;
		}
		
		public function get x():int {
			return _x;
		}
		
		public function get y():int {
			return _y;
		}
		
		public function get width():int {
			return _width;
		}
		
		public function get multiplier():int {
			return _multiplier;
		}
		
	}

}
