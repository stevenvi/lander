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
 
 
 
// Menu1.h: interface for the Menu class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MENU1_H__C1606F42_E819_11DA_9D08_00D0594C1148__INCLUDED_)
#define AFX_MENU1_H__C1606F42_E819_11DA_9D08_00D0594C1148__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>
using namespace std;

#ifdef _WIN32
typedef unsigned int uint;
#endif

class Menu  
{
public:
	Menu();
	Menu(struct FONT *font, ...);
	virtual ~Menu();

	//void draw(struct BITMAP *buffer);
	int doMenu(double elapsedTime, struct BITMAP *buffer, struct DATAFILE *data[]);
	void setSelected(int i) { selected = i; }
	void selectLast();
	void label(uint idx, const char *label);

private:
	int selected;
	vector<const char*> items;
	struct FONT *item_font;

};

#endif // !defined(AFX_MENU1_H__C1606F42_E819_11DA_9D08_00D0594C1148__INCLUDED_)
