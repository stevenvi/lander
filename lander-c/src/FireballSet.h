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
 
 
 
// FireballSet.h: interface for the FireballSet class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FIREBALLSET_H__186B79E1_E916_11DA_9D08_8431B7A07554__INCLUDED_)
#define AFX_FIREBALLSET_H__186B79E1_E916_11DA_9D08_8431B7A07554__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



class FireballSet  
{
public:
	FireballSet(int numParticles, int maxInstances, float avgLife);
	virtual ~FireballSet();
	void drawAndUpdate(struct BITMAP *buffer, float zoom_factor, float screenX, float screenY, double timeElapsed);
	void update(double timeElapsed);
	void draw(struct BITMAP *buffer, float zoom_factor, float screenX, float screenY);
	void add(float strength, int x, int y, float angle, int maxRadius, float timeElapsed);
	void reset();

private:
	int numParticles;
	int maxInstances;
	float avgLife;

	class Fireball *ball;

};

#endif // !defined(AFX_FIREBALLSET_H__186B79E1_E916_11DA_9D08_8431B7A07554__INCLUDED_)
