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
 
 
 
// TheLander.h: interface for the TheLander class.
// Describes and draws and interacts with the lander,
// the player-controlled character.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_THELANDER_H__C1606F40_E819_11DA_9D08_00D0594C1148__INCLUDED_)
#define AFX_THELANDER_H__C1606F40_E819_11DA_9D08_00D0594C1148__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class TheLander  
{
public:
	TheLander(struct BITMAP *sprite);
	virtual ~TheLander();
	float getX() { return x; }
	float getY() { return y; }
	float getVX() { return vx; }
	float getVY() { return vy; }
	float getFuel() { return fuel; }

	void update(double timeElapsed);

	void setPosition(float x, float y) { this->x = x; this->y = y; }
	void changePosition(float dx, float dy) { x += dx; y += dy; }

	void setVelocity(float vx, float vy) { this->vx = vx; this->vy = vy; }
	void changeVelocity(float dx, float dy) { vx += dx; vy += dy; }
	void setFuel(float f) { fuel = f; }
	void changeFuel(float df) { fuel += df; }
	bool hasFuel() { return fuel>0.0f?true:false; }

	void draw(struct BITMAP *buffer, float zoom_factor, int screenX, int screenY, int offsetX, int offsetY);
	bool checkCollision(int level);
	
	bool isOutOfSky();
	
	// pad is the multiplier number, so valid inputs are 2, 5, or 10
	bool isOnPad(int pad, class Level *level);
	bool inZoomRange(int pad, class Level *level);

private:
	float x, y, vx, vy;
	float fuel;			// Float from 0 to 1
	int score;
	struct BITMAP *sprite;

	const int LANDER_W;
	const int LANDER_H;

};

#endif // !defined(AFX_THELANDER_H__C1606F40_E819_11DA_9D08_00D0594C1148__INCLUDED_)
