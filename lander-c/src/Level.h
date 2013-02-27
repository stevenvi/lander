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
 
 
 
// Level.h: interface for the Level class.
// Describes a level.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LEVEL_H__C1606F41_E819_11DA_9D08_00D0594C1148__INCLUDED_)
#define AFX_LEVEL_H__C1606F41_E819_11DA_9D08_00D0594C1148__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "collide.h"

extern const char *levelName[10];




class Level  
{
public:
	Level();
	Level(int level, struct BITMAP *field);
	virtual ~Level();
	void load(int level);
	int getLevelNumber() { return levelNumber; }
	

	void loadCore(int level);
	void setField(struct BITMAP *f) { bmpField = f; mk_spr_mask(f,levelNumber+1); }
	void draw(struct BITMAP *buffer, float zoom_factor, float screenX, float screenY, int offsetX, int offsetY);
	const char *getName() { return name; }


	struct BITMAP *bmpField;
	struct RGB pal[256];
	int levelNumber;

	int pad2x1, pad2y, pad2x2,	// landing pad locations
		pad5x1, pad5y, pad5x2,
		pad10x1,pad10y,pad10x2;

	int zoom2x, zoom2y, 
		zoom5x, zoom5y,
		zoom10x,zoom10y;	// Starting locations of zoom ranges

	int label2x, label2y,	// location of the labels for all multipliers
		label5x, label5y,
		label10x, label10y;

	int brandx, brandy;		// location of the company logo

	char name[32];

};

#endif // !defined(AFX_LEVEL_H__C1606F41_E819_11DA_9D08_00D0594C1148__INCLUDED_)
