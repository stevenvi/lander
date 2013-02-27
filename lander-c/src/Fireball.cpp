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
 
 
 
// Fireball.cpp: implementation of the Fireball class.
//
//////////////////////////////////////////////////////////////////////

#include <allegro.h>
#include <math.h>
#include "Fireball.h"
#include "TheGame.h"
#include "data.h"

#ifndef M_PI
#define M_PI 3.141592654
#endif

#ifndef MAX
#define MAX(a,b)	( (a)>(b)?(a):(b) )
#endif

#ifndef MIN
#define MIN(a,b)	( (a)>(b)?(b):(a) )
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Fireball::Fireball(float x, float y, float angle, float power) {
	this->x = x;
	this->y = y;
	this->angle = angle;
	dx = power * cos(angle * M_PI / 180.0f);
	dy = power * sin(angle * M_PI / 180.0f);
	//if(power < 10) radius = 1;
	originalRadius = radius = 2 + rand()%(int)ceil(power/15 + 0.001) ;
	color = 0;
	//colorSpeed = radius, 240-color;
}

Fireball::~Fireball() {
}



void Fireball::draw(BITMAP *buffer, float zoom_factor, float screenX, float screenY) {
	RGB *c = &((RGB*)(data[P_FLAMES]->dat))[(int)MAX(0,MIN(256,color))];
	if(radius > 0.0f) 
		circlefill(buffer, (int)((x - screenX) * zoom_factor), (int)((y - screenY) * zoom_factor), 
				(int)(radius * zoom_factor), makecol(c->r*4, c->g*4, c->b*4));
}

// Returns true if this fireball needs to be deleted
bool Fireball::update(double timeElapsed, float avgLife) {
	dy -= 15.0f * GRAVITY * timeElapsed;
	y += dy * timeElapsed * 10.0f;
	x += dx * timeElapsed * 10.0f;
	radius -= originalRadius/(avgLife * (0.25f + (rand()%75)/50.0f)) * timeElapsed;
	color += (224-64) * avgLife * timeElapsed;
	if(color > 255) color = 255;

	return radius<=0.0f?true:false;
}


void Fireball::set(float x, float y, float dx, float dy, float angle, float radius, float color) {
	this->x = x;
	this->y = y;
	this->dx = dx;
	this->dy = dy;
	this->angle = angle;
	originalRadius = this->radius = radius;
	this->color = color;
}
