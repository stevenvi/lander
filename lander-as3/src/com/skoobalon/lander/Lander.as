////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// Lander AS3                                                                 //
// (c) Copyright 2001-2010 Skoobalon Software.                                //
//                                                                            //
// This program is free software; you can redistribute it and/or modify it    //
// under the terms of the GNU General Public License as published by the Free //
// Software Foundation; version 2 of the License.                             //
//                                                                            //
// This program is distributed in the hope that it will be useful, but        //
// WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY //
// or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License   //
// for more details.                                                          //
//                                                                            //
// You should have received a copy of the GNU General Public License along    //
// with this program; if not, write to the Free Software Foundation, Inc., 51 //
// Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA                  //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

package com.skoobalon.lander {
	import com.skoobalon.lander.game.GameController;
	import com.skoobalon.lander.intro.IntroController;
	import com.skoobalon.lander.menu.MenuController;
	import com.skoobalon.lander.resources.LanderConstants;
	import com.skoobalon.lander.resources.LanderResources;
	import com.skoobalon.lander.resources.MessageBox;
	import flash.display.Sprite;
	import flash.events.ErrorEvent;
	import flash.events.Event;
	import flash.text.TextField;
	import mx.logging.ILogger;
	import mx.logging.Log;
	import mx.logging.targets.TraceTarget;
	
	/**
	 * @author Steven Wallace
	 */
	[SWF(width = "640", height = "480", frameRate = "60", backgroundColor = "#000000")]
	public class Lander extends Sprite {
		
		private static const LOG:ILogger = Log.getLogger("com.skoobalon.lander.Lander");
		private var _resources:LanderResources;
		
		private var _intro:IntroController;
		private var _menu:MenuController;
		private var _game:GameController;
		
		
		public function Lander():void {
			if (stage) {
				addedToStageHandler();
			} else {
				addEventListener(Event.ADDED_TO_STAGE, addedToStageHandler);
			}
		}
		
		private function addedToStageHandler(event:Event = null):void {
			removeEventListener(Event.ADDED_TO_STAGE, addedToStageHandler);
			
			// Set up the logging facilities
			var traceTarget:TraceTarget = new TraceTarget();
			Log.addTarget(traceTarget);
			
			// Load the configuration
			LOG.debug("Loading configuration");
			_resources = new LanderResources();
			_resources.config.addEventListener(ErrorEvent.ERROR, levelConfigError);
			_resources.config.addEventListener(Event.COMPLETE, levelConfigLoaded);
			_resources.config.loadLevels();
		}
		
		private function levelConfigLoaded(event:Event):void {
			_resources.config.removeEventListener(Event.COMPLETE, levelConfigLoaded);
			
			_intro = new IntroController(_resources);
			addChild(_intro.view);
			
			LOG.debug("Showing intro");
			_intro.addEventListener(Event.CLOSE, onIntroClose);
			_intro.open();
		}
		
		private function levelConfigError(event:ErrorEvent):void {
			var messageBox:MessageBox = new MessageBox("The level configuration file could not be loaded.  Please contact Skoobalon Software to remedy the situation.", "Fatal error");
			messageBox.x = (LanderConstants.SCREEN_W - messageBox.width) / 2;
			messageBox.y = (LanderConstants.SCREEN_H - messageBox.height) / 2;
			addChild(messageBox);
		}
		
		private function onIntroClose(event:Event):void {
			_intro.removeEventListener(Event.CLOSE, onIntroClose);
			removeChild(_intro.view);
			
			_menu = new MenuController(_resources);
			addChild(_menu.view);
			
			LOG.debug("Showing menu");
			_menu.addEventListener(Event.CLOSE, onMenuClose);
			_menu.open(true);
		}
		
		private function onMenuClose(event:Event):void {
			_menu.removeEventListener(Event.CLOSE, onMenuClose);
			removeChild(_menu.view);
			
			_game = new GameController(_resources);
			addChild(_game.view);
			
			LOG.debug("Starting game");
			_game.open();
		}
		
	}
	
}
