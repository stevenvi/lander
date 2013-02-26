package com.skoobalon.lander.resources {
	import flash.events.ErrorEvent;
	import flash.events.Event;
	import flash.events.EventDispatcher;
	import flash.net.URLLoader;
	import flash.net.URLRequest;
	import mx.logging.ILogger;
	import mx.logging.Log;
	
	/**
	 * Loads and stores the configuration
	 * @author Steven Wallace
	 */
	public class LanderConfiguration extends EventDispatcher {
		
		public static const LEVEL_FILE:String = "config/planets.xml";
		
		public static const LOG:ILogger = Log.getLogger("com.skoobalon.lander.resources.LanderConfiguration");
		
		private var _levels:XML;
		
		public function LanderConfiguration() {
			
		}
		
		public function loadLevels():void {
			try {
				var assetLoader:URLLoader = new URLLoader();
				assetLoader.addEventListener(Event.COMPLETE, loadLevelsComplete);
				assetLoader.load(new URLRequest(LEVEL_FILE));
			} catch (error:Error) {
				LOG.error("Could not load planet information file");
				assetLoader.removeEventListener(Event.COMPLETE, loadLevelsComplete);
				dispatchEvent(new ErrorEvent(ErrorEvent.ERROR));
			}
			
			function loadLevelsComplete(event:Event):void {
				assetLoader.removeEventListener(Event.COMPLETE, loadLevelsComplete);
				_levels = XML(assetLoader.data);
				
				dispatchEvent(new Event(Event.COMPLETE));
			}
		}
		
		public function getLevelDetails(levelNumber:int):XMLList {
			return _levels.level.(@ordinal == levelNumber);
		}
		
	}
	
}
