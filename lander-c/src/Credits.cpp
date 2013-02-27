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
 
 
 
// Credits.cpp: implementation of the Credits class.
//
//////////////////////////////////////////////////////////////////////

#include <allegro.h>
#include <stdarg.h>
#include "Credits.h"
#include "CreditItem.h"
#include "TheGame.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Credits::Credits(struct FONT *font, ...)
{
	Logfile::log("+Credits at 0x%x\n", this);
	
	this->font = font;

	va_list ap;
	va_start(ap, font);

	while(1) {
		const char *heading = va_arg(ap, const char*);

		if(heading == 0) break;
		credit.push_back(CreditItem(heading,true));

		while(1) {
			const char *entry = va_arg(ap, const char*);
			if(entry == 0) break;
			credit.push_back(CreditItem(entry,false));
		}

		// Space each section out a little
		credit.push_back(CreditItem("",false));
	}
	va_end(ap);

	scroll = 0.0f;
}

Credits::~Credits() {
	Logfile::log("-Credits at 0x%x\n", this);
}



// returns false when credits end
bool Credits::doCredits(BITMAP *buffer, double timeElapsed) {
	int fontSize = text_height(font);
	int linesPerScreen = GAME_H/(fontSize * 5 / 4);
	static const int HEADING_X = GAME_W / 12;
	static const int ENTRY_X = GAME_W / 9;



	for(uint i=(int)MIN(credit.size(),MAX(0, scroll - linesPerScreen-12)); i<MIN((int)scroll+1,credit.size()); i++) {
		static int x_off;
		static int color;
		if(credit[i].heading) {
			x_off = HEADING_X;
			color = COLOR_RED;
		}
		else {
			x_off = ENTRY_X;
			color = COLOR_GREEN;
		}

		textprintf_ex(buffer,font,x_off+1, GAME_H - int((scroll-i)*fontSize)+1, 0, -1, credit[i].content);
		textprintf_ex(buffer,font,x_off,GAME_H - (int)((scroll - i)*fontSize), color, -1, credit[i].content);
	}


	scroll += timeElapsed * 1.25f;
	if(scroll > credit.size() + linesPerScreen) return false;
	else return true;
}




