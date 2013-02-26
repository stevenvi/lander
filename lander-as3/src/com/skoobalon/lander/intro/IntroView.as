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
	import caurina.transitions.Tweener;
	import flash.display.Sprite;
	import flash.events.TimerEvent;
	import flash.geom.Point;
	import flash.utils.Timer;
	
	/**
	 * @author Steven Wallace
	 */
	public class IntroView extends Sprite {
		
		private var _logo:CompanyLogo;
		private var _timer:Timer = new Timer(750, 1);
		
		public function stop():void {
			Tweener.removeTweens(_logo);
			_timer.removeEventListener(TimerEvent.TIMER_COMPLETE, scrollDown);
		}
		
		public function restart():void {
			if (_logo) {
				removeChild(_logo);
			}
			
			_logo = new CompanyLogo();
			zoomIn();
		}
		
		private function zoomIn():void {
			var originalDims:Point = new Point(_logo.width, _logo.height);
			
			_logo.x = _logo.width / 2;
			_logo.y = _logo.height / 2;
			_logo.width = _logo.height = 0;
			
			addChild(_logo);
			Tweener.addTween(_logo, { x: 0, y: 0, width: originalDims.x, height: originalDims.y, onComplete: waitAbit, time: 2.25, transition: "linear" } );
		}
		
		private function waitAbit():void {
			_timer.reset();
			_timer.start();
			_timer.addEventListener(TimerEvent.TIMER_COMPLETE, scrollDown);
		}
		
		private function scrollDown(event:TimerEvent):void {
			_timer.removeEventListener(TimerEvent.TIMER_COMPLETE, scrollDown);
			
			Tweener.addTween(_logo, { y: _logo.height, onComplete: finish, time: 1.6, transition: "linear" } );
		}
		
		private function finish():void {
			dispatchEvent(new IntroEvent(IntroEvent.INTRO_DONE));
		}
		
	}

}
