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
 
 
 
// Credits.h: interface for the Credits class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CREDITS_H__AA6CF660_EA4D_11DA_9D08_00D0594C1148__INCLUDED_)
#define AFX_CREDITS_H__AA6CF660_EA4D_11DA_9D08_00D0594C1148__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include <vector>
#include "CreditItem.h"
using namespace std;

class Credits  
{
public:
	Credits(struct FONT *font, ...);
	virtual ~Credits();
	bool doCredits(struct BITMAP *buffer, double timeElapsed);
	void reset() { scroll = 0.0f; }

private:
	struct FONT *font;
	vector<class CreditItem> credit;
	float scroll;

};

#endif // !defined(AFX_CREDITS_H__AA6CF660_EA4D_11DA_9D08_00D0594C1148__INCLUDED_)
