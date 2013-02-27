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
 
 
 
// Logfile.h: interface for the Logfile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOGFILE_H__C1606F44_E819_11DA_9D08_00D0594C1148__INCLUDED_)
#define AFX_LOGFILE_H__C1606F44_E819_11DA_9D08_00D0594C1148__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class Logfile  
{
public:
	Logfile();
	virtual ~Logfile();
	static void flush();
	static void log(const char *format...);

};

#endif // !defined(AFX_LOGFILE_H__C1606F44_E819_11DA_9D08_00D0594C1148__INCLUDED_)
