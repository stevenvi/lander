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
 
 
 
// TransitionStar1.cpp: implementation of the TransitionStar class.
//
//////////////////////////////////////////////////////////////////////

#include <allegro.h>
#include "TransitionStar.h"
#include "TheGame.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TransitionStar::TransitionStar()
{
	x = rand()%(GAME_W);
	y = rand()%(GAME_H);
	distance = (rand()%512)/256.0f;
	char color = rand()%256;
	intensity = makecol(color,color,color);
	size = rand()%2;
}

TransitionStar::~TransitionStar()
{

}


void TransitionStar::draw(BITMAP *buffer) {
	circlefill(buffer, (int)x, (int)y, size, intensity);
}


void TransitionStar::update(double timeElapsed, float dx, float dy) {

	x += dx * distance * timeElapsed * 100;
	if(x < -10.0f)					x = GAME_W + 5.0f;
	else if(x > 10.0f + GAME_W)	x = -5.0f;

	y += dy * distance * timeElapsed * 100;
	if(y < -10.0f)					y = GAME_H + 5.0f;
	else if(y > 10.0f + GAME_H)	y = -5.0f;

}

