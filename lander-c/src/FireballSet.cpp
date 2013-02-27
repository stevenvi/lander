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
 
 
 
// FireballSet.cpp: implementation of the FireballSet class.
//
//////////////////////////////////////////////////////////////////////

#include <allegro.h>
#include <math.h>
#include "Fireball.h"
#include "FireballSet.h"
#include "Logfile.h"

#ifndef M_PI
#define M_PI	3.141592654
#endif

#ifndef TORAD
#define TORAD (M_PI / 180.0f)
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

FireballSet::FireballSet(int numParticles, int maxInstances, float avgLife) {
	Logfile::log("+FireballSet at 0x%x\n", this);

	this->numParticles = numParticles;
	this->maxInstances = maxInstances;
	this->avgLife = avgLife;

	ball = new Fireball[numParticles * maxInstances];
}

FireballSet::~FireballSet() {
	delete [] ball;
	Logfile::log("-FireballSet at 0x%x\n", this);
}


void FireballSet::add(float strength, int x, int y, float angle, int maxRadius, float timeElapsed) {
	int added = 0;
	for(int i=0; i<maxInstances * numParticles; i++) {
		if(added >= strength * 1500 * timeElapsed) return;
		if(ball[i].getRadius() <= 0.25f) {
			float a = angle + (-30 + (rand()%180) / 3.0f);
			float r = MIN(maxRadius/(10.0f/strength),((rand()+1)%maxRadius) - ((rand()+1)%(int)(maxRadius/(50.0f/strength) + 1)));
			float xx = x + (-50 + rand()%100) / 10.0f;
			float yy = y + (-50 + rand()%100) / 10.0f;
			//float yy = y + sqrt(25 - pow(xx-x,2)) * ((rand()%500) / 250.0f - 1.0f);
			float color = 64;
			float dx = cos(a * TORAD) * (strength / 5.0f);
			float dy = sin(a * TORAD) * (strength / 5.0f);
			ball[i].set(xx,yy,dx,dy,a,r,color);
			added++;
		}
	}
}


// It is more efficient to draw and update at the same time.
// Unfortunately, this is not always possible.
void FireballSet::drawAndUpdate(BITMAP *buffer, float zoom_factor, float screenX, float screenY, double timeElapsed) {
	for(int i=0; i<numParticles * maxInstances; i++) {
		if(ball[i].getRadius() > 0.25f) {
			ball[i].draw(buffer,zoom_factor, screenX, screenY);
			ball[i].update(timeElapsed,avgLife);
		}
	}
}


void FireballSet::draw(BITMAP *buffer, float zoom_factor, float screenX, float screenY) {
	for(int i=0; i<numParticles * maxInstances; i++)
		if(ball[i].getRadius() > 0.25f) ball[i].draw(buffer, zoom_factor, screenX, screenY);
}


void FireballSet::update(double timeElapsed) {
	for(int i=0; i<numParticles * maxInstances; i++)
		if(ball[i].getRadius() > 0.25f) ball[i].update(timeElapsed, avgLife);
}



// Makes all the fireballs be dead
void FireballSet::reset() {
	int i;
	for(i=0; i<numParticles; i++) ball[i].setRadius(0.0f);
}

