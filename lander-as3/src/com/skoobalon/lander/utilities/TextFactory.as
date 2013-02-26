package com.skoobalon.lander.utilities {
	import flash.text.TextField;
	import flash.text.TextFieldAutoSize;
	import flash.text.TextFormat;
	import flash.text.TextFormatAlign;
	
	/**
	 * @author Steven Wallace
	 */
	public class TextFactory {
		
		public static function format( textField:TextField, 
									   textSize:Number,
									   textColor:uint,
									   width:Number, 
									   height:Number,
									   align:String = TextFormatAlign.LEFT, 
									   multiline:Boolean = false,
									   wordWrap:Boolean = false,
									   selectable:Boolean = false,
									   autoSize:String = "none" ):void
		{
			var textFormat:TextFormat = textField.defaultTextFormat;
			textFormat.align = align;
			textFormat.size = textSize;
			textFormat.color = textColor;
			textField.defaultTextFormat = textFormat;
			textField.setTextFormat(textFormat);
			
			textField.autoSize = autoSize;
			textField.selectable = selectable;
			textField.wordWrap = wordWrap;
			textField.multiline = multiline;
			
			textField.width = width;
			textField.height = height;
		}
		
	}

}
