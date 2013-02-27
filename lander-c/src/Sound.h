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
 
 
 


#ifndef _SOUND_H
#define _SOUND_H

#include <vector>
using namespace std;

#ifdef _WIN32
typedef unsigned int uint;
#endif


class SoundStat {
public:
	SoundStat(struct SAMPLE *s);
	~SoundStat();

	struct SAMPLE *sample;
	float vol, freq, pan;
	bool loop;
	int voice;
	int position;
	enum { STATUS_STOPPED, STATUS_PLAYING, STATUS_PAUSED } status;
};




class Sound {
public:
	Sound();
	~Sound();

	// Before a sound can be played, it must be registered
	uint registerSample(struct SAMPLE *s);

	bool play(uint id, float volume=-1, float pan=-1, float freq=-1, int loop=-123);
	bool alter(uint id, float volume=-1, float pan=-1, float freq=-1, int loop=-123);
	bool changePan(uint id, float pan);
	bool changeFreq(uint id, float freq);
	bool changeVol(uint id, float vol);
	bool changeLoop(uint id, bool loop);
	bool stop(uint id);
	void stopAll();
	bool isPlaying(uint id);
	void pauseAll();
	void unpauseAll();
	bool pause(uint id);
	bool unpause(uint id);
		
	void turnOn() { on = true; }
	void turnOff() { on = false; stopAll(); }
	bool on;

private:
	vector<SoundStat *> stat;
};




#endif // _SOUND_H
