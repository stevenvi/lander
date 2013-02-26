package com.skoobalon.lander.components {
	import flash.display.Shape;
	import flash.geom.Point;
	
	/**
	 * @author Steven Wallace
	 */
	public class Fireball {
		
		public var velocity:Point;
		public var angle:Number = 0;
		public var radius:Number = 0;
		public var originalRadius:Number = 0;
		public var color:Number = 0;
		
		public var x:Number;
		public var y:Number;
		
		public function redraw():void {
			//graphics.clear();
			if (radius > 0.25) {
				// TODO: Use the game's palette!
				//graphics.beginFill((color << 16) | (color << 8) | color, 1);
				//graphics.drawCircle(0, 0, radius);
			}
		}
		
	}

}
