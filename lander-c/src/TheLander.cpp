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
 
 
 
// TheLander.cpp: implementation of the TheLander class.
//
//////////////////////////////////////////////////////////////////////

#include <allegro.h>
#include "TheLander.h"
#include "collide.h"
#include "TheGame.h"
#include "Level.h"
#include "Logfile.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TheLander::TheLander(BITMAP *s) : LANDER_W(s->w), LANDER_H(s->h)
{
	Logfile::log("+TheLander at 0x%x\n", this);
	
	score = 0;
	fuel = 1.0f;

	x = 13.0f;
	y = 3.0f;
	vx = 0.1f;
	vy = 0.0f;

	sprite = s;
	mk_spr_mask(s,0);
}

TheLander::~TheLander() {
	Logfile::log("-TheLander at 0x%x\n", this);
}


void TheLander::update(double timeElapsed) {
	x += vx * timeElapsed * 100;
	y += vy * timeElapsed * 100;
	vy += GRAVITY * timeElapsed;

//	int old_bg_frame;


/*	if(gameMode == MODE_GAME)
	{
		//fLogfile("UPDATE GRAVITY\n");
		x += vx * timeElapsed;
		y += vy * timeElapsed;

		vy += .001 * timeElapsed;
		if(vx>0)vx-=.00003 * timeElapsed;
		if(vx<0)vx+=.00003 * timeElapsed;

		if(PLAY_ROCKET && !ROCKET_IS_PLAYING)
		{
			play_sample(data[S_ROCKET].dat,255,127,rocket_freq,TRUE);
			ROCKET_IS_PLAYING = TRUE;
		}
		if(ROCKET_IS_PLAYING) adjust_sample(data[S_ROCKET].dat,255,127,rocket_freq,TRUE);
		if(!PLAY_ROCKET)
		{
			stop_sample(data[S_ROCKET].dat);
			ROCKET_IS_PLAYING = FALSE;
		}



		// make sure fuel is above 0
		if(fuel < 0.0f)
		{
			fuel = 0.0f;
		}


		// land pads

		// check collisions
		if(check_pp_collision(0,player_x,player_y,1,0,0))
		{
			playerDie();
		}


	} // if gameMode == MODE_GAME
*/
}


void TheLander::draw(BITMAP *buffer, float zoom_factor, int screenX, int screenY, int offsetX, int offsetY) {
	masked_stretch_blit(sprite, buffer, 
		0, 0, 
		LANDER_W, LANDER_H, 
		(int)((x - screenX) * zoom_factor + offsetX), 
		(int)((y - screenY) * zoom_factor + offsetY), 
		(int)(LANDER_W * zoom_factor), (int)(LANDER_H * zoom_factor));
}


bool TheLander::checkCollision(int level) {
	return check_pp_collision(level+1, 0, 0, 0, (int)x, (int)y)?true:false;
}



bool TheLander::isOutOfSky() {
	if(x > GAME_W + LANDER_W*2 
	|| x < -LANDER_W*3 
	|| y > GAME_H + LANDER_H 
	|| y < -LANDER_H*3) 
		return true;
	return false;
}

bool TheLander::isOnPad(int pad, Level *level) {
	int px1, px2, py;
	switch(pad) {
	case 2:
		px1 = level->pad2x1;
		px2 = level->pad2x2;
		py = level->pad2y;
		break;
	case 5:
		px1 = level->pad5x1;
		px2 = level->pad5x2;
		py = level->pad5y;
		break;
	case 10:
		px1 = level->pad10x1;
		px2 = level->pad10x2;
		py = level->pad10y;
		break;
	default:
		return false;
	}
	
	if((int)y == py - LANDER_H 
	&& (int)x >= px1 
	&& (int)x <= px2 - LANDER_W) 
		return true;
	return false;
}


bool TheLander::inZoomRange(int pad, Level *level) {
	int zx, zy;
	switch(pad) {
	case 2: 
		zx = level->zoom2x; 
		zy = level->zoom2y;
		break;
	
	case 5: 
		zx = level->zoom5x; 
		zy = level->zoom5y;
		break;
	
	case 10:
		zx = level->zoom10x; 
		zy = level->zoom10y;
		break;
	
	default:
		return false;
	}
	
	if(x >= zx 
	&& x <= zx + ZOOM_W - LANDER_W 
	&& y >= zy 
	&& y <= zy + ZOOM_H - LANDER_H)
		return true;
	return false;
}


