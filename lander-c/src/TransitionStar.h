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
 
 
 
// TransitionStar1.h: interface for the TransitionStar class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRANSITIONSTAR1_H__7F7D9BE1_E835_11DA_9D08_00D0594C1148__INCLUDED_)
#define AFX_TRANSITIONSTAR1_H__7F7D9BE1_E835_11DA_9D08_00D0594C1148__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class TransitionStar  
{
public:
	TransitionStar();
	virtual ~TransitionStar();

	void draw(struct BITMAP *buffer);
	void update(double timeElapsed, float x, float y);

private:
	float distance, x, y;
	int intensity;
	char size;
	
};

#endif // !defined(AFX_TRANSITIONSTAR1_H__7F7D9BE1_E835_11DA_9D08_00D0594C1148__INCLUDED_)
