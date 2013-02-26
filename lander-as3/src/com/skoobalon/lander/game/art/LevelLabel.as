package com.skoobalon.lander.game.art {
	import flash.display.MovieClip;
	import mx.logging.ILogger;
	import mx.logging.Log;
	
	/**
	 * The "2x", "5x", "10x" label
	 * @author Steven Wallace
	 */
	[Embed(source = '/../resources/resources.swf', symbol = 'LevelLabel')]
	public class LevelLabel extends MovieClip {
		
		/**
		 * @private
		 * Flex logger
		 */
		private static const LOG:ILogger = Log.getLogger("com.skoobalon.lander.game.art.LevelLabel");
		
		public function LevelLabel(type:String) {
			super();
			
			switch (type) {
				case "2x":		gotoAndStop(1);	break;
				case "5x":		gotoAndStop(2);	break;
				case "10x":		gotoAndStop(3);	break;
				case "brand":	gotoAndStop(4);	break;
				default:		LOG.error("Invalid label type: {0}", type);
			}
		}
		
	}

}
