/*
 *LANDER!
 *Copyright (c) 2001, 2006, 2007 Steven Wallace / Chedda Cheeze
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA
 */
 
 
 
// Menu1.cpp: implementation of the Menu class.
//
//////////////////////////////////////////////////////////////////////

#include <stdarg.h>
#include <allegro.h>
#include "Menu.h"
#include "data.h"
#include "TheGame.h"
#include "Logfile.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
Menu::Menu() {
	Menu(font,"The menu wasn't allocated properly!",0);
}

// number of arguments should be numMenuItems + 1
// First parameter: font to use
// Second parameter: title of first menu option
// Third: function pointer to action when menu item is selected
// Fourth: title of second menu option
// etc
// End it with null lables and pointers.
Menu::Menu(FONT *font, ...) {
	Logfile::log("+Menu at 0x%x\n", this);
	
	va_list ap;

	va_start(ap, font);
	while(1) {
		const char *lable = va_arg(ap, const char*);

		if(lable == 0) break;

		// Store menu items in a list.
		items.push_back(lable);
	}
	va_end(ap);

	item_font = font;
	selected = 0;
}

Menu::~Menu() {
	Logfile::log("-Menu at 0x%x\n", this);
}


// Returns the index of the selected item, or -1 if nothing was selected
int Menu::doMenu(double timeElapsed, BITMAP *buffer, DATAFILE *data[]) {
	static const int offset = 50;
	int ret = -1;

	static int col = COLOR_VELOCITY_ZONE;
    

	for(uint n=0; n<items.size(); n++) {
		textprintf_centre_ex(buffer, item_font, GAME_W/2+1, offset + GAME_H/5 + (text_height(item_font)+5)*n+1, 0, -1, items[n]);
		textprintf_centre_ex(buffer, item_font, GAME_W/2, offset + GAME_H/5 + (text_height(item_font)+5)*n, col, -1, items[n]);
	}

	draw_sprite(buffer,(BITMAP*)data[B_ARROW]->dat,
		GAME_W/2 - text_length(item_font, items[selected]) / 2 - 64, 
		offset+8 + GAME_H/5 + (text_height(item_font)+5)*selected - 8);
	draw_sprite_h_flip(buffer,(BITMAP*)data[B_ARROW]->dat,
		GAME_W/2 + text_length(item_font, items[selected]) / 2 + 32, 
		offset+8 + GAME_H/5 + (text_height(item_font)+5)*selected - 8);


	if(keypressed()) {
		int k = readkey() >> 8;
		switch(k) {
			case KEY_UP:
				selected--;
				if(selected < 0) selected = 0;
				break;
			case KEY_DOWN:
				selected++;
				if(selected >= items.size()) selected = items.size()-1;
				break;
			case KEY_ENTER:
			case KEY_ENTER_PAD:
				ret = selected;
				break;
//			case KEY_ESC:
//				selecteLast();
//				break;
		}
	}

	return ret;
}


void Menu::selectLast() {
	setSelected(items.size() - 1);
}



/* Changes a label for a menu item
 * Note that this will NOT free the memory for the previous string,
 * so if you had allocated that memory yourself you MUST free it yourself!
 */
void Menu::label(uint idx, const char *label) {
	// Make sure idx is valid
	if(idx > items.size()-1) return;

	// overwrite the string
	items[idx] = label;
}
