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
 
 
 
// Logfile.cpp: implementation of the Logfile class.
//
//////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <allegro.h>
#include "Logfile.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Logfile::Logfile()
{

}

Logfile::~Logfile()
{

}

void Logfile::flush() {
#ifdef _DEBUG
	FILE *file;
	file = fopen("log.txt","wt");
	fclose(file);
#endif
	return;
}

void Logfile::log(const char *format...) {
#ifdef _DEBUG
	static bool first = true;
	char str[1024];
	
	
	if(first) {
		first = false;
		flush();
	}
	
	snprintf(str, 1024, format);

	FILE *file;
	file = fopen("log.txt","at");
	
	va_list ap;
	va_start(ap, format);
	uvszprintf(str, sizeof(str), format, ap);
	va_end(ap);
	
	fprintf(file, str);
	printf(str);

	fclose(file);
#endif
	return;
}

