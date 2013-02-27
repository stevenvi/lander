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
 
 
 
// Level.cpp: implementation of the Level class.
//
//////////////////////////////////////////////////////////////////////

#include <allegro.h>
#include <stdio.h>
#include <string.h>
#include "Level.h"
#include "data.h"
#include "TheGame.h"
#include "Logfile.h"



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


Level::Level() {
	Logfile::log("+Level at 0x%x\n", this);
}

Level::Level(int level,BITMAP *field) { 
	Logfile::log("+Level at 0x%x\n", this);

	load(level); 
	levelNumber = level;
	
	bmpField = field;
	mk_spr_mask(field,0);
}

Level::~Level() {
	Logfile::log("-Level at 0x%x\n", this);
}


void Level::load(int level) {
	loadCore(level);
}


void Level::loadCore(int level)
{
	set_config_file("core.ini");

	char section[256];
	sprintf(section,"level%02d",level);

	zoom2x = get_config_int(section,"zoom2x",-1);
	zoom2y = get_config_int(section,"zoom2y",-1);
	zoom5x = get_config_int(section,"zoom5x",-1);
	zoom5y = get_config_int(section,"zoom5y",-1);
	zoom10x = get_config_int(section,"zoom10x",-1);
	zoom10y = get_config_int(section,"zoom10y",-1);

	pad2x1 = get_config_int(section,"pad2x1",-1);
	pad2x2 = get_config_int(section,"pad2x2",-1);
	pad2y = get_config_int(section,"pad2y",-1);

	pad5x1 = get_config_int(section,"pad5x1",-1);
	pad5x2 = get_config_int(section,"pad5x2",-1);
	pad5y = get_config_int(section,"pad5y",-1);

	pad10x1 = get_config_int(section,"pad10x1",-1);
	pad10x2 = get_config_int(section,"pad10x2",-1);
	pad10y = get_config_int(section,"pad10y",-1);

	label2x = get_config_int(section,"label2x",-1);
	label2y = get_config_int(section,"label2y",-1);

	label5x = get_config_int(section,"label5x",-1);
	label5y = get_config_int(section,"label5y",-1);

	label10x = get_config_int(section,"label10x",-1);
	label10y = get_config_int(section,"label10y",-1);

	brandx = get_config_int(section,"brandx",-1);
	brandy = get_config_int(section,"brandy",-1);

	const char *tmp = get_config_string(section,"name","name not specified");
	sprintf(name,tmp);

	levelNumber = level;
}


// A bounding box collision check.  Used to determine which labels are drawn for the level
// Returns true on collision, false otherwise
// This probably isn't efficient, but this is a quick hack
bool bb_col(int x1a, int y1a, int x2a, int y2a, int x1b, int y1b, int x2b, int y2b) {
	// Check x1b
	if(x1a < x1b && x1b < x2a) {
		// Check y1b
		if(y1a < y1b && y1b < y2a) return true;
			
		// Check y2b
		if(y1a < y2b && y2b < y2a) return true;
	}
	
	// Check x2b
	if(x1a < x2b && x2b < x2a) {
		// Check y1b
		if(y1a < y1b && y1b < y2a) return true;
			
		// Check y2b
		if(y1a < y2b && y2b < y2a) return true;
	}
	
	// Check x1a
	if(x1b < x1a && x1a < x2b) {
		// Check y1a
		if(y1b < y1a && y1a < y2b) return true;
			
		// Check y2a
		if(y1b < y2a && y2a < y2b) return true;
	}
	
	// Check x2a
	if(x1b < x2a && x2a < x2b) {
		// Check y1a
		if(y1b < y1a && y1a < y2b) return true;
			
		// Check y2a
		if(y1b < y2a && y2a < y2b) return true;
	}
	
	return false;
}


void Level::draw(BITMAP *buffer, float zoom_factor, float screenX, float screenY, 
				 int offsetX, int offsetY) 
{
	// determine the rectangle of the level we are to draw
	int x1 = (int)(screenX + 0.5f);
	int y1 = (int)(screenY + 0.5f);
	int w = (int)(bmpField->w/zoom_factor + 0.5f);
	int h = (int)(bmpField->h/zoom_factor + 0.5f);
	
	// Variables used to store label positions
	int lx1, ly1, lw, lh;
	
	// Draw the main level bitmap
	masked_stretch_blit(bmpField, buffer, 
		x1, y1, w, h,
		offsetX, offsetY,
		bmpField->w, bmpField->h);

	// Draw the labels
	BITMAP *l2 = (BITMAP*)data[B_LABEL2]->dat;
	lx1 = (int)((label2x - screenX) * zoom_factor);
	ly1 = (int)((label2y - screenY) * zoom_factor);
	lw = (int)(l2->w * zoom_factor);
	lh = (int)(l2->h * zoom_factor);
	if(bb_col(0, 0, bmpField->w, bmpField->h, lx1, ly1, lx1+lw, ly1+lh)) {
		masked_stretch_blit(l2, buffer, 0, 0, l2->w, l2->h,
			lx1 + offsetX, ly1 + offsetY, lw, lh);
		
		//textprintf_ex(buffer, font, 250, 15, makecol(255,255,255), -1, "L2");
	}

	BITMAP *l5 = (BITMAP*)data[B_LABEL5]->dat;
	lx1 = (int)((label5x - screenX) * zoom_factor);
	ly1 = (int)((label5y - screenY) * zoom_factor);
	lw = (int)(l5->w * zoom_factor);
	lh = (int)(l5->h * zoom_factor);
	if(bb_col(0, 0, bmpField->w, bmpField->h, lx1, ly1, lx1+lw, ly1+lh)) {
		masked_stretch_blit(l5, buffer, 0, 0, l5->w, l5->h,
			lx1 + offsetX, ly1 + offsetY, lw, lh);
		
		//textprintf_ex(buffer, font, 270, 15, makecol(255,255,255), -1, "L5");
	}

	BITMAP *l10 = (BITMAP*)data[B_LABEL10]->dat;
	lx1 = (int)((label10x - screenX) * zoom_factor);
	ly1 = (int)((label10y - screenY) * zoom_factor);
	lw = (int)(l10->w * zoom_factor);
	lh = (int)(l10->h * zoom_factor);
	if(bb_col(0, 0, bmpField->w, bmpField->h, lx1, ly1, lx1+lw, ly1+lh)) {
		masked_stretch_blit(l10, buffer, 0, 0, l10->w, l10->h,
			lx1 + offsetX, ly1 + offsetY, lw, lh);

		//textprintf_ex(buffer, font, 290, 15, makecol(255,255,255), -1, "L10");
	}


	// Draw the brand
	BITMAP *br = (BITMAP*)data[B_BRAND]->dat;
	lx1 = (int)((brandx - screenX) * zoom_factor);
	ly1 = (int)((brandy - screenY) * zoom_factor);
	lw = (int)(br->w * zoom_factor);
	lh = (int)(br->h * zoom_factor);
	if(bb_col(0, 0, bmpField->w, bmpField->h, lx1, ly1, lx1+lw, ly1+lh)) {
		masked_stretch_blit(br, buffer, 0, 0, br->w, br->h,
			lx1 + offsetX, ly1 + offsetY, lw, lh);
		
		//textprintf_ex(buffer, font, 310, 15, makecol(255,255,255), -1, "BR");
	}
}




