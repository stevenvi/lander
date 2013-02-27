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
 
 
 


#include <allegro.h>
#include "ParticleSource.h"
#include "Logfile.h"
#include <math.h>
#include "TheGame.h"
#include "data.h"


#ifndef M_PI
#define M_PI 3.141592654f
#endif

#ifndef TORAD
#define TORAD M_PI/180.0f
#endif


ParticleSource::ParticleSource(int numParts, int maxInst, int maxRad, int avgLif) {
	Logfile::log("+ParticleSource at 0x%x\n", this);
	
	numParticles = numParts;
	maxInstances = maxInst;
	maxRadius = maxRad;
	avgLife = avgLif;

	particle = new Particle[maxInstances * numParticles];
	if(!particle) {
		// Something bad happened.
		Logfile::log("Could not allocate particles.  This is bad.",0);
	}
}


ParticleSource::~ParticleSource() {
	if(particle) delete [] particle;
	Logfile::log("-ParticleSource at 0x%x\n", this);
}


void ParticleSource::add(int strength, int x, int y, float angle, double timeElapsed) {
	int n, added=0;

	for(n=0; n<maxInstances * numParticles; n++) {
		if(added >= strength * (250 * timeElapsed)) return;
		if(particle[n].radius < 1.0f) {
			particle[n].angle = angle + (-15 + rand()%30);
			particle[n].radius = MIN(maxRadius/(10.0f/strength),((rand()+1)%maxRadius - ((rand()+1)%(int)(maxRadius/(50.0f/strength) + 1))));
			particle[n].x = x + (-5 + rand()%10);
			particle[n].y = y + (-5 + rand()%10);
			particle[n].color = 64;	// This is the index in the palette that we start at
			particle[n].dx = cos(particle[n].angle*TORAD) * (strength/5.0f);
			particle[n].dy = sin(particle[n].angle*TORAD) * (strength/5.0f);
			added++;
		}
	}
}


int get_color_from_pal(int idx) {
	RGB *c = &((RGB*)(data[P_FLAMES]->dat))[(int)idx];
	return makecol(c->r*4, c->g*4, c->b*4);
}

void ParticleSource::drawAndUpdate(BITMAP *buffer, float zoom_factor, int screenX, int screenY, double timeElapsed) {
	int n;

	for(n=0; n<maxInstances * numParticles; n++) {
		if(particle[n].radius < 1.0f) continue;
		circlefill(buffer, (int)((particle[n].x - screenX) * zoom_factor), 
				(int)((particle[n].y - screenY) * zoom_factor), 
				(int)(particle[n].radius * zoom_factor), 
				get_color_from_pal((int)particle[n].color));

		particle[n].dy -= 10.0f * GRAVITY * timeElapsed;
		particle[n].y += particle[n].dy * timeElapsed;
		particle[n].x += particle[n].dx * timeElapsed;
		particle[n].radius -= (float)avgLife * maxRadius * timeElapsed;
		particle[n].color += 100.0f * timeElapsed;
	}
}


void ParticleSource::draw(BITMAP *buffer, float zoom_factor, int screenX, int screenY) {
	int n;

	for(n=0; n<maxInstances * numParticles; n++) {
		if(particle[n].radius < 1.0f) continue;
		circlefill(buffer, (int)((particle[n].x - screenX) * zoom_factor), 
				(int)((particle[n].y - screenY) * zoom_factor), 
				(int)(particle[n].radius * zoom_factor), 
				get_color_from_pal((int)particle[n].color));
	}
}


void ParticleSource::update(double timeElapsed) {
	int n;

	for(n=0; n<maxInstances * numParticles; n++) {
		if(particle[n].radius < 1.0f) continue;

		particle[n].dy -= 10.0f * GRAVITY * timeElapsed;
		particle[n].y += particle[n].dy * timeElapsed;
		particle[n].x += particle[n].dx * timeElapsed;
		particle[n].radius -= (float)avgLife * maxRadius * timeElapsed;
		particle[n].color += 100.0f * timeElapsed;
	}
}


void ParticleSource::reset() {
	int n;

	for(n=0; n<maxInstances * numParticles; n++) particle[n].radius = 0.0f;
}
