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
 
 
 

// Configuration.cpp: implementation of the Configuration class.
//
//////////////////////////////////////////////////////////////////////

#include "Configuration.h"
#include "TheGame.h"
#include "Music.h"
#include "Sound.h"
#include "allegro.h"
#include "Logfile.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Configuration::Configuration() {
	Logfile::log("+Configuration at 0x%x\n", this);
	
	// Load in the config data
	set_config_file("lander.ini");

	showFPS = get_config_int("window","fps",0);
	fullscreen = get_config_int("window", "fullscreen", FALSE);

	sfx = get_config_int("audio","sfx",TRUE);
	music = get_config_int("audio","music",TRUE);

	musicVol = get_config_float("audio","musicvol",1.0f);
	soundVol = get_config_float("audio","soundvol",1.0f);
	
	Logfile::log("Configuration read:\n",0);
	Logfile::log(	"\tshowFPS: %d\n"
			"\tsfx: %d\n"
			"\tmusic: %d\n"
			"\tfullscreen: %d\n",
			showFPS, sfx, music, fullscreen);
	
	
	// This is lame, I know, but it gets the job done of turning
	// sound and music either on or off as specified in the file
	toggleSFX(); toggleSFX();
	toggleMusic(); toggleMusic();
}


void Configuration::reload() { Configuration(); }

Configuration::~Configuration() {
	// Save game information
	set_config_file("lander.ini");

	// todo: get the window's coordinates
	set_config_int("window","posx",-1);
	set_config_int("window","posy",-1);
	set_config_int("window","fullscreen",fullscreen);

	set_config_int("audio","sfx",sfx);
	set_config_int("audio","music",music);
	flush_config_file();
	
	Logfile::log("Window and Audio config settings saved.\n");
	
	Logfile::log("-Configuration at 0x%x\n", this);
}


void Configuration::toggleSFX() { 
	sfx = !sfx; 
	if(!sfx) sound.turnOff();
	else sound.turnOn();
}

void Configuration::toggleMusic() {
	music = !music;
	if(!music) ::music.turnOff();
	else ::music.turnOn();
}

void Configuration::toggleFullscreen() {
	fullscreen = !fullscreen;
	fullscreen = setup_screen(fullscreen);
}
