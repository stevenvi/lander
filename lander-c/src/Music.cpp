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
 
 
 

#include <allegro.h>
#include <aldumb.h>
#include "Music.h"
#include "TheGame.h"
#include "Logfile.h"


// Set DUMB loop callback
// This must be called each time a new player is created!
int musicLoopCallback(void *music) {
	return ((Music*)music)->musicUnload(false);
}

void Music::musicSetCallback() {
	DUH_SIGRENDERER *sr = al_duh_get_sigrenderer(bgsong_player);
	DUMB_IT_SIGRENDERER *itsr = duh_get_it_sigrenderer(sr);
	dumb_it_set_loop_callback(itsr, &musicLoopCallback, this);
}


void Music::poll() {
	if(!on) return;
	if(reloadFlag || !bgsong_player || !bgsong) {
		play();
		reloadFlag = false;
	}
	al_poll_duh(bgsong_player);
}


int Music::musicUnload(bool forReal) {
	// If we don't really want to unload music, but instead
	// just want to set a flag if we should, mark this
	if(!forReal) {
		if(track != track_queue) {
			reloadFlag = true;
			return 1;
		}
		else return 0;
	}


	// Unload the song and the player
	if(bgsong) {
		if(bgsong_player) {
			al_stop_duh(bgsong_player);
			bgsong_player = 0;
		}

		// We use DUHs in datafiles, so this is unnecessary
		//unload_duh(bgsong);
		bgsong = 0;
		return 1;
	}

	else return 0;
}


void Music::queue(int track, bool immediately) {
	track_queue = track;		// Queue the new track
	
	if(immediately) reloadFlag = true;
	
	//printf("Queuing track %d...\n", track);
}

int Music::play() {
	int ret=0;
	if(!data) {
		data = load_datafile("music.dat");
		if(data) Logfile::log("Loaded music datafile.\n");
		else {
			Logfile::log("ERROR: Could not load music datafile!\n");
			return FALSE;
		}
	}

	if(track != track_queue || !bgsong_player || !bgsong) {
		musicUnload(true);

		// load the current level's song
		track = track_queue;
		//track_queue = -1;
		Logfile::log("Playing track %d.\n", track);

		/* We use DUHs in datafiles, so this is unnecessary
		char fn[512];
		sprintf(fn,"tr%02d.s3m", track);
		bgsong = dumb_load_s3m_quick(fn);*/
		bgsong = (DUH*)data[track].dat;
		if(!bgsong) {
			Logfile::log("ERROR: could not load track %d!", track);
		}
	}
	
	// stop music if it is playing
	if(bgsong_player) al_stop_duh(bgsong_player);

	// Start the music
	bgsong_player = al_start_duh(bgsong, 2, 0, config->getMusicVol(), 4096, 48000);
	musicSetCallback();


	//printf("Playing track %d.\n", track);
	return ret;
}


void Music::stop() {
	//printf("Music stopped.\n");
	if(bgsong && bgsong_player) {
		al_stop_duh(bgsong_player);
		bgsong_player = 0;
	}
}

void Music::turnOn() {
	on = true;
}

void Music::turnOff() {
	on = false;
	stop();
}


Music::Music() {
	Logfile::log("+Music at 0x%x\n", this);
	
	bgsong_player = 0;
	bgsong = 0;
	data = 0;
	track = track_queue = -1;
	reloadFlag = false;
	turnOn();
}

Music::Music(int track) {
	Logfile::log("+Music at 0x%x\n", this);
	
	bgsong_player = 0;
	bgsong = 0;
	data = 0;
	reloadFlag = false;
	
	if(track >= 0) {
		this->track = -1;
		track_queue = track;
		play();
	}
}


Music::~Music() {
	if(bgsong_player) {
		al_stop_duh(bgsong_player);
		bgsong_player = 0;
	}
	/* We now use DUHs in datafiles, so this is unnecessary
	if(bgsong) {
		unload_duh(bgsong);
		bgsong = 0;
	}*/
	if(data) {
		unload_datafile(data);
		data = 0;
	}

	Logfile::log("-Music at 0x%x\n", this);
}


