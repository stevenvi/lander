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
 
 
 
// KeyHandler1.h: interface for the KeyHandler class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_KEYHANDLER1_H__C1606F46_E819_11DA_9D08_00D0594C1148__INCLUDED_)
#define AFX_KEYHANDLER1_H__C1606F46_E819_11DA_9D08_00D0594C1148__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <allegro.h>


#define K_RIGHT	0x1
#define K_LEFT	0x2
#define K_MAX	0x4
#define K_MIN	0x8
#define K_MED	0x10


class KeyHandler  
{
public:
	KeyHandler();
	virtual ~KeyHandler();

	int getKeys();


private:
	int kLeft, kRight, kMax, kMed, kMin, kAll;

};

#endif // !defined(AFX_KEYHANDLER1_H__C1606F46_E819_11DA_9D08_00D0594C1148__INCLUDED_)
