package com.skoobalon.lander.resources {
	import flash.display.MovieClip;
	import flash.text.TextField;
	
	/**
	 * @author Steven Wallace
	 */
	[Embed(source = '/../resources/resources.swf', symbol = 'MessageBox')]
	public class MessageBox extends MovieClip {
		
		public var titleText:TextField;
		public var messageText:TextField;
		
		public function MessageBox(messageText:String = "", titleText:String = "") {
			super();
			stop();
			
			this.messageText.text = messageText;
			this.titleText.text = titleText;
		}
		
	}

}
