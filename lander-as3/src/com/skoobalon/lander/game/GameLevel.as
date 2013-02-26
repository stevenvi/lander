package com.skoobalon.lander.game {
	import __AS3__.vec.Vector;
	import caurina.transitions.Tweener;
	import com.skoobalon.lander.components.LandingPad;
	import com.skoobalon.lander.game.art.LevelLabel;
	import com.skoobalon.lander.resources.LanderConstants;
	import com.skoobalon.lander.utilities.LoadingBar;
	import flash.display.DisplayObject;
	import flash.display.Loader;
	import flash.display.Shape;
	import flash.display.Sprite;
	import flash.events.Event;
	import flash.events.EventDispatcher;
	import flash.events.HTTPStatusEvent;
	import flash.events.IOErrorEvent;
	import flash.geom.Point;
	import flash.geom.Rectangle;
	import flash.net.URLRequest;
	import mx.logging.ILogger;
	import mx.logging.Log;
	
	/**
	 * @author Steven Wallace
	 */
	public class GameLevel extends Sprite {
		
		private static const LOG:ILogger = Log.getLogger("GameLevel");
		
		private var _loadingBar:LoadingBar = new LoadingBar();
		private var _background:DisplayObject;
		
		private var _name:String;
		private var _ordinal:int;
		private var _pads:Vector.<LandingPad> = new Vector.<LandingPad>();
		private var _zooms:Vector.<Point> = new Vector.<Point>();
		
		public function GameLevel() {
			
		}
		
		public function initialize(xml:XMLList):void {
			LOG.debug("Initializing: {0}", xml);
			
			_name = xml.@name;
			_ordinal = xml.@ordinal;
			
			// Start fetching the background bitmap
			var loader:Loader = new Loader();
			_loadingBar.listenOn(loader);
			loader.contentLoaderInfo.addEventListener(Event.COMPLETE, backgroundLoaded);
			loader.contentLoaderInfo.addEventListener(IOErrorEvent.IO_ERROR, loadError);
			loader.load(new URLRequest(xml.@background));
			_loadingBar.x = (LanderConstants.ACTIONVIEW_W - _loadingBar.width) / 2;
			_loadingBar.y = (LanderConstants.ACTIONVIEW_H - _loadingBar.height) / 2;
			addChild(_loadingBar);
			
			function backgroundLoaded(event:Event):void {
				removeListeners();
				removeChild(_loadingBar);
				_background = loader.content;
				_background.scaleX = _background.scaleY = 0.25;
				addChildAt(_background, 0);
				LOG.debug("Background loaded -- it's {0}x{1}", _background.width, _background.height);
				
				// NOTE: For debugging only
				for each (var pad:LandingPad in _pads) {
					var padshape:Shape = new Shape();
					padshape.graphics.beginFill(0xFF00FF, 1);
					padshape.graphics.drawRect(pad.x, pad.y, pad.width, 1);
					padshape.graphics.endFill();
					addChild(padshape);
				}
			}
			
			function loadError(event:IOErrorEvent):void {
				LOG.error("Error loading level {0}: {1}", xml.@background, event);
				removeListeners();
			}
			
			function removeListeners():void {
				loader.contentLoaderInfo.removeEventListener(Event.COMPLETE, backgroundLoaded);
				loader.contentLoaderInfo.removeEventListener(IOErrorEvent.IO_ERROR, loadError);
			}
			
			
			// Pull out landing pads
			for each (var pad:XML in xml.landingpads.landingpad) {
				_pads.push(new LandingPad(pad.@x, pad.@y, pad.@width, pad.@multiplier));
			}
			
			// Pull out zoom regions
			for each (var zoom:XML in xml.zooms.zoom) {
				_zooms.push(new Point(zoom.@x, zoom.@y));
			}
			
			// Pull out the labels
			for each (var label:XML in xml.labels.label) {
				var ll:LevelLabel = new LevelLabel(label.@type);
				ll.x = label.@x;
				ll.y = label.@y;
				addChild(ll);
			}
		}
		
		public function get zooms():Vector.<Point> {
			return _zooms.slice();
		}
		
		public function get landingPads():Vector.<LandingPad> {
			return _pads.slice();
		}
		
		override public function get name():String {
			return _name;
		}
		
		public function get ordinal():int {
			return _ordinal;
		}
		
		override public function toString():String {
			return "Level {name: " + name + ", ordinal: " + ordinal + "]";
		}
		
	}

}
