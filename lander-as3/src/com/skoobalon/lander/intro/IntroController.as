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

package com.skoobalon.lander.intro {
	import com.skoobalon.lander.resources.LanderResources;
	import flash.display.DisplayObject;
	import flash.events.Event;
	import flash.events.EventDispatcher;
	import flash.events.KeyboardEvent;
	
	/**
	 * @author Steven Wallace
	 */
	public class IntroController extends EventDispatcher {
		
		
		private var _resources:LanderResources;
		private var _view:IntroView = new IntroView();
		
		public function IntroController(resources:LanderResources) {
			construct(resources);
		}
		
		public function construct(resources:LanderResources):void {
			_resources = resources;
			_view.addEventListener(IntroEvent.INTRO_DONE, close, false, 0, true);
		}
		
		private function keyDownHandler(Event:KeyboardEvent):void {
			// The user pressed a key, kill the intro!
			close();
		}
		
		public function open():void {
			_view.stage.addEventListener(KeyboardEvent.KEY_DOWN, keyDownHandler);
			_view.restart();
		}
		
		public function close(event:Event = null):void {
			_view.stop();
			_view.stage.removeEventListener(KeyboardEvent.KEY_DOWN, keyDownHandler);
			dispatchEvent(new Event(Event.CLOSE));
		}
		
		public function get view():DisplayObject {
			return _view;
		}
		
	}

}
