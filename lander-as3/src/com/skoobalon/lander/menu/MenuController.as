////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// Lander AS3                                                                 //
// (c) Copyright 2001-2010 Skoobalon Software                                 //
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

package com.skoobalon.lander.menu {
	import caurina.transitions.Tweener;
	import com.skoobalon.lander.resources.LanderResources;
	import flash.display.DisplayObject;
	import flash.events.Event;
	import flash.events.EventDispatcher;
	import flash.events.KeyboardEvent;
	import flash.ui.Keyboard;
	
	/**
	 * @author Steven Wallace
	 */
	public class MenuController extends EventDispatcher {
		
		private var _resources:LanderResources;
		
		private var _view:MenuView = new MenuView();
		
		public function MenuController(resources:LanderResources) {
			construct(resources);
		}
		
		private function construct(resources:LanderResources):void {
			_resources = resources;
		}
		
		
		public function open(showTitle:Boolean):void {
			if (showTitle) {
				_view.showTitle();
				_view.tweenTitleIn();
			} else {
				_view.hideTitle();
			}
			
			_view.stage.addEventListener(KeyboardEvent.KEY_DOWN, onKeyDown);
		}
		
		public function close():void {
			if (_view.isTitleVisible) {
				_view.tweenTitleOut();
			}
			
			_view.stage.removeEventListener(KeyboardEvent.KEY_DOWN, onKeyDown);
			dispatchEvent(new Event(Event.CLOSE));
		}
		
		private function onKeyDown(event:KeyboardEvent):void {
			switch (event.keyCode) {
				case Keyboard.ENTER:
					if (_view.isTitleVisible) {
						_view.tweenTitleOut(close);
					} else {
						// Make sure that we aren't tweening in
						_view.stopTweeningTitleIn();
					}
					break;
			}
		}
		
		
		public function get view():DisplayObject {
			return _view;
		}
		
	}

}
