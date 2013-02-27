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
 
 
 


#ifndef _PARTICLESOURCE_H
#define _PARTICLESOURCE_H


#include "Particle.h"


class ParticleSource {
public:
	ParticleSource(int numParts, int maxInst, int maxRad, int avgLif);
	~ParticleSource();

	void add(int strength, int x, int y, float angle, double timeElapsed);
	void drawAndUpdate(struct BITMAP *buffer, float zoom_factor, int screenX, int screenY, double timeElapsed);
	void draw(struct BITMAP *buffer, float zoom_factor, int screenX, int screenY);
	void update(double timeElapsed);
	void reset();
	
	int getMaxRadius() { return maxRadius; }
	

private:
	int numParticles;
	int maxInstances;
	int maxRadius;
	int avgLife;

	Particle *particle;
};






#endif // _PARTICLESOURCE_H

