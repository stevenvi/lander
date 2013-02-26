package com.skoobalon.lander.utilities {
	
	import flash.display.GradientType;
	import flash.display.Loader;
	import flash.display.Shape;
	import flash.display.Sprite;
	import flash.events.Event;
	import flash.events.ProgressEvent;
	
	/**
	 * A simple progress bar
	 * @author Steven Wallace
	 */
	public class LoadingBar extends Sprite {
		
		private var _outline:Shape = new Shape();
		private var _progress:Shape = new Shape();
		private var _loader:Loader;
		
		public function LoadingBar() {
			_outline.graphics.beginFill(0x000000, 1.0);
			_outline.graphics.drawRect(0, 0, 320, 100);
			_outline.graphics.endFill();
			
			addChild(_outline);
			addChild(_progress);
		}
		
		public function listenOn(loader:Loader):void {
			_loader = loader;
			loader.contentLoaderInfo.addEventListener(Event.COMPLETE, completeHandler);
			loader.contentLoaderInfo.addEventListener(ProgressEvent.PROGRESS, progressHandler);
		}
		
		public function removeListeners():void {
			if (_loader) {
				_loader.contentLoaderInfo.removeEventListener(Event.COMPLETE, completeHandler);
				_loader.contentLoaderInfo.removeEventListener(ProgressEvent.PROGRESS, progressHandler);
			}
		}
		
		private function completeHandler(event:Event):void {
			progress = 1.0;
			removeListeners();
		}
		
		private function progressHandler(event:ProgressEvent):void {
			progress = event.bytesLoaded / event.bytesTotal;
		}
		
		private function set progress(value:Number):void {
			_progress.graphics.beginFill(0xFFFFFF, 0.9);
			_progress.graphics.drawRect(1, 1, 318 * value, 98);
			_progress.graphics.endFill();
		}
		
	}

}
