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
 
 
 
// TransitionStarSet.cpp: implementation of the TransitionStarSet class.
//
//////////////////////////////////////////////////////////////////////

#include "TransitionStarSet.h"
#include "Logfile.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TransitionStarSet::TransitionStarSet() {
	TransitionStarSet(256);
}

TransitionStarSet::TransitionStarSet(int stars) {
	Logfile::log("+TransitionStarSet at 0x%x\n", this);

	star = new TransitionStar[stars];
	numStars = stars;
}

TransitionStarSet::~TransitionStarSet() {
	if(star) delete [] star;
	Logfile::log("-TransitionStarSet at 0x%x\n", this);
}


void TransitionStarSet::draw(BITMAP *buffer) {
	for(int i=0; i<numStars; i++) star[i].draw(buffer);
}

void TransitionStarSet::update(double timeElapsed, float x, float y) {
	for(int i=0; i<numStars; i++) star[i].update(timeElapsed,x,y);
}

void TransitionStarSet::drawAndUpdate(BITMAP *buffer, double timeElapsed, float x, float y) {
	for(int i=0; i<numStars; i++) {
		TransitionStar *s = &star[i];
		s->draw(buffer);
		s->update(timeElapsed,x,y);
	}
}


