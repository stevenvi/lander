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
 
 
 
// Timer.cpp: implementation of the Timer class.
//
//////////////////////////////////////////////////////////////////////


#include <allegro.h>
#ifdef WIN32
#include <winalleg.h>
#else
#include <unistd.h>
#include <sys/time.h>
#endif
#include "Timer.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Timer::Timer()
{
#ifdef WIN32
	// Windows code
	LARGE_INTEGER temp;
	
	QueryPerformanceFrequency(&temp);
	pcFrequency = temp.QuadPart;

	QueryPerformanceCounter(&temp);
	lastTime = temp.QuadPart;
#else
	// Unix code
	timeval tv;
	gettimeofday(&tv,NULL);

	lastTime = tv;
#endif

	refresh = get_refresh_rate();
	if(refresh > 0) refresh1 = 1.0f/refresh;
	else refresh1 = 0.0f;
}

Timer::~Timer()
{

}


// Returns the time elapsed as percentage of a second
// since the last call to this function
double Timer::timeElapsed() {
#ifdef WIN32
	// Windows code
	LARGE_INTEGER temp;
	QueryPerformanceCounter(&temp);
	double ret = double(temp.QuadPart-lastTime)/pcFrequency;
	lastTime = temp.QuadPart;
#else
	// Unix code
	timeval tv;
	gettimeofday(&tv,NULL);

	long ds = tv.tv_sec - lastTime.tv_sec;
	long dus = tv.tv_usec - lastTime.tv_usec;

	lastTime = tv;
	long usecs = ds * 1000000 + dus;
	double ret = usecs / 1000000.0f;
#endif

	// If the user's system is lagging, don't penalize them with a ridiculous 
	// multiplier.
	if(ret > 0.25f) ret = 0.001f;

	// If we're running faster than the monitor refresh speed, then 
	// hold up briefly so that we don't waste too much time.
	//else if(ret < refresh1) rest((int)((refresh1 - ret) *1000));
	return ret;
}


