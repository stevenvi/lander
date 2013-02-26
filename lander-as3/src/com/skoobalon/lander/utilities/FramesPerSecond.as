package com.skoobalon.lander.utilities {
	import flash.utils.getTimer;
	
	/**
	 * Computes the frames per second of the game loop.  This is done by sending
	 * the time of each frame to this class, which keeps a tally of the last N
	 * frames, and determines approximately how many are being drawn each
	 * second.
	 * 
	 * @author Steven Wallace
	 */
	public class FramesPerSecond {
		
		/**
		 * The size of the framecount buffer -- must be a power of 2 due to
		 * certain code optimizations used!
		 */
		public static const BUFFER_SIZE:int = 32;
		
		private var _index:int = 0;
		private var _buffer:Vector.<int> = new Vector.<int>(BUFFER_SIZE);
		private var _fps:Number;
		
		public function FramesPerSecond() {
			// (Do nothing)
		}
		
		public function frame():void {
			var time:int = getTimer();
			var oldIndex:int = _index;
			_index = (_index + 1) & (BUFFER_SIZE - 1);
			
			_buffer[oldIndex] = time;
			
			_fps = BUFFER_SIZE / (time - _buffer[_index]) * 1000;
		}
		
		public function get fps():Number {
			return _fps;
		}
		
	}

}
