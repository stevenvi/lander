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
 
 
 
// Fireball.h: interface for the Fireball class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FIREBALL_H__186B79E0_E916_11DA_9D08_8431B7A07554__INCLUDED_)
#define AFX_FIREBALL_H__186B79E0_E916_11DA_9D08_8431B7A07554__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class Fireball  
{
public:
	Fireball() {x=y=dx=dy=angle=radius=originalRadius=color=0;}
	Fireball(float x, float y, float angle, float power);
	virtual ~Fireball();
	void draw(struct BITMAP *buffer, float zoom_factor, float screenX, float screenY);
	bool update(double timeElapsed, float avgLife);

	void set(float x, float y, float dx, float dy, float angle, float radius, float color);
	void setRadius(float rad) { radius = rad; }

	float getRadius() { return radius; }

private:
	float x, y;
	float dx, dy;
	float angle;
	float radius;
	float originalRadius;
	float color;		// cast to char when using it!  index in a palette!
};

#endif // !defined(AFX_FIREBALL_H__186B79E0_E916_11DA_9D08_8431B7A07554__INCLUDED_)
