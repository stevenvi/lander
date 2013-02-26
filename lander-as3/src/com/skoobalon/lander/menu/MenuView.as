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

package com.skoobalon.lander.menu {
	
	import caurina.transitions.Tweener;
	import com.skoobalon.lander.resources.LanderConstants;
	import flash.display.Sprite;
	import flash.events.Event;
	import flash.events.KeyboardEvent;
	import flash.text.TextField;
	
	/**
	 * @author Steven Wallace
	 */
	public class MenuView extends Sprite {
		
		private var _title:Title = new Title();
		private var _lander:MenuLander = new MenuLander();
		private var _versionText:TextField = new TextField();
		private var _isTweeningTitleIn:Boolean = false;
		
		private var _option1:TextField = new TextField();
		
		public function MenuView() {
			_title.y = -_title.height;
			
			_lander.x = MenuConstants.LANDER_INITIAL.x;
			_lander.y = MenuConstants.LANDER_INITIAL.y;
			
			_versionText.text = "v" + LanderConstants.VERSION;
			_versionText.textColor = 0xFFFFFF;
			_versionText.x = LanderConstants.SCREEN_W - _versionText.textWidth - 4;
			_versionText.y = LanderConstants.SCREEN_H - _versionText.textHeight - 4;
			
			// This guy is just temporary until I put in a real recreation of the menu
			_option1.text = "Press ENTER to play";
			_option1.textColor = 0x00FF00;
			_option1.width = _option1.textWidth + 10;
			_option1.x = (LanderConstants.SCREEN_W - _option1.width) / 2;
			_option1.y = (LanderConstants.SCREEN_H - _option1.height) / 2;
			
			addChild(_title);
			addChild(_lander);
			addChild(_option1);
			addChild(_versionText);
		}
		
		public function tweenTitleIn():void {
			Tweener.removeTweens(_title);
			Tweener.removeTweens(_lander);
			
			var time:Number = -_title.y / _title.height * 5;
			_isTweeningTitleIn = true;
			Tweener.pauseTweens(_title, _lander);
			Tweener.addTween(_title, { y: 0, transition: "linear", time: time, onComplete: function():void { _isTweeningTitleIn = false; } } );
			Tweener.addTween(_lander, { x: MenuConstants.LANDER_FINAL.x, y: MenuConstants.LANDER_FINAL.y, transition: "linear", time: time } );
			Tweener.resumeTweens(_title, _lander);
		}
		
		public function stopTweeningTitleIn():void {
			if (_isTweeningTitleIn) {
				Tweener.removeTweens(_title);
				Tweener.removeTweens(_lander);
				_title.y = 0;
				_lander.x = MenuConstants.LANDER_FINAL.x;
				_lander.y = MenuConstants.LANDER_FINAL.y;
				_isTweeningTitleIn = false;
			}
		}
		
		public function tweenTitleOut(callback:Function = null):void {
			Tweener.removeTweens(_title);
			Tweener.removeTweens(_lander);
			
			var time:Number = (_title.height + _title.y) / _title.height * 5;
			Tweener.pauseTweens(_title, _lander);
			Tweener.addTween(_title, { y: -_title.height, transition: "linear", time: time, onComplete: callback } );
			Tweener.addTween(_lander, { x: MenuConstants.LANDER_INITIAL.x, y: MenuConstants.LANDER_INITIAL.y, transition: "linear", time: time } );
			Tweener.resumeTweens(_title, _lander);
		}
		
		public function showTitle():void {
			_title.visible = true;
		}
		
		public function hideTitle():void {
			_title.visible = false;
		}
		
		public function get isTitleVisible():Boolean {
			return _title.visible;
		}
		
	}

}
