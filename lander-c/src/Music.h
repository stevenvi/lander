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
 
 
 


#ifndef _MUSIC_H
#define _MUSIC_H



class Music {
public: 
	Music();
	Music(int track);
	~Music();
	void setTrack(int track);
	int musicUnload(bool forReal);	// 
	int play();
	void stop();
	void turnOff();
	void turnOn();
	void queue(int track, bool immediately=false);
	void musicSetCallback();
	void poll();					// This must be called once per frame to keep the music playing

private:

	struct DUH *bgsong;		// The currently loaded background music
	struct AL_DUH_PLAYER *bgsong_player;
	int track;					// Track number of currently playing song
	int track_queue;			// Track number of the currently queued song
	bool reloadFlag;			// When set, reload the music
	bool on;
	struct DATAFILE *data;
};



#endif // _MUSIC_H
