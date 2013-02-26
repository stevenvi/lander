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
	import flash.events.Event;
	
	/**
	 * @author Steven Wallace
	 */
	public class IntroEvent extends Event {
		
		public static const INTRO_DONE:String = "introDone";
		
		public function IntroEvent(type:String, bubbles:Boolean = false, cancelable:Boolean = false) {
			super(type, bubbles, cancelable);
			
		}
		
	}

}
