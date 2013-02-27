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
 
 
 
// Configuration.h: interface for the Configuration class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONFIGURATION_H__C1606F43_E819_11DA_9D08_00D0594C1148__INCLUDED_)
#define AFX_CONFIGURATION_H__C1606F43_E819_11DA_9D08_00D0594C1148__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class Configuration  
{
public:
	Configuration();
	virtual ~Configuration();
	void reload();

	bool isSFX() { return sfx?true:false; }
	bool isMusic() { return music?true:false; }
	bool isFullscreen() { return fullscreen?true:false; }
	bool isFPS() { return showFPS?true:false; }

	void setFullscreen(int fs) { fullscreen = fs; }

	void toggleSFX();
	void toggleMusic();
	void toggleFullscreen();

	float getMusicVol() { return musicVol; }
	float getSoundVol() { return soundVol; }

private:
	int sfx, music;				// Toggle for sound effects and music being turned on
	float soundVol, musicVol;		// 0.0=off, 1.0=full
	int fullscreen;				// Whether or not we are in a fullscreen mode
	int showFPS;				// Whether or not to show the fps


};

#endif // !defined(AFX_CONFIGURATION_H__C1606F43_E819_11DA_9D08_00D0594C1148__INCLUDED_)
