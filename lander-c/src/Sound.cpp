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
 
 
 
// Note that this is modified so that all sounds max out at 50%.  It was easier than changing
// every other volume reference.

#include "Sound.h"
#include "TheGame.h"
#include "Configuration.h"
#include "Logfile.h"
#include <allegro.h>


#define MAX_VOLUME	127


SoundStat::SoundStat(SAMPLE *s) {
	Logfile::log("+SoundStat at 0x%x\n", this);
	
	sample = s;
	status = STATUS_STOPPED;
	vol = 1.0f;
	pan = 0.5f;
	freq = 1.0f;
	loop = true;
	voice = -1;
	position = -1;
}

SoundStat::~SoundStat() {
	Logfile::log("-SoundStat at 0x%x\n", this);
}

Sound::Sound() {
	Logfile::log("+Sound at 0x%x\n", this);
	turnOn();
}


Sound::~Sound() {
	uint i;
	for(i=0; i<stat.size(); i++) delete stat[i];
	
	Logfile::log("-Sound at 0x%x\n", this);
}


uint Sound::registerSample(SAMPLE *s) {
	// Make sure we haven't already registered this sample
	uint i;
	for(i=0; i<stat.size(); i++) {
		if(s == stat[i]->sample) return i;
	}

	Logfile::log("Registering sample at 0x%x.\n", s);
	stat.push_back(new SoundStat(s));
	return stat.size() - 1;
}


bool Sound::alter(uint id, float volume, float pan, float freq, int loop) {
	// First check: make sure the id is valid
	if(id >= stat.size()) return false;
		
	// Set all parameters in our list
	if(volume > 1.0f) volume = 1.0f;
	else if(volume == -1.0f) volume = stat[id]->vol; // (keep previous value)
	else if(volume < 0.0f) volume = 0.0f;
	stat[id]->vol = volume;
	
	if(pan > 1.0f) pan = 1.0f;
	else if(pan == -1.0f) pan = stat[id]->pan; // (keep previous value)
	else if(pan < 0.0f) pan = 0.0f;
	stat[id]->pan = pan;
		
	if(loop == -123) loop = stat[id]->loop?TRUE:FALSE; // (keep previous value)
	stat[id]->loop = loop?true:false;
	
	if(freq == -1.0f) freq = stat[id]->freq; // (keep previous value)
	else if(freq < 0.0f) freq = 0.0f;
	stat[id]->freq = freq;
	
	if(isPlaying(id)) 
		adjust_sample(stat[id]->sample, (int)(stat[id]->vol * MAX_VOLUME), 
			(int)(stat[id]->pan * 255), (int)(stat[id]->freq * 1000), stat[id]->loop?TRUE:FALSE);
	
	return true;
}


// Returns true if sample is playing at the end of the function call, false otherwise
bool Sound::play(uint id, float volume, float pan, float freq, int loop) {
	if(!on) return false;

	//printf("Altering sample %d.\n", id);
	alter(id, volume, pan, freq, loop);
	
	if(isPlaying(id)) {
		//printf("Sample %d is already playing!\n", id);
		return true;
	}

	// Actually play the sample
	//printf("Playing sample %d.\n", id);
	stat[id]->voice = play_sample(stat[id]->sample, (int)(stat[id]->vol * MAX_VOLUME), 
			(int)(stat[id]->pan * 255), (int)(stat[id]->freq * 1000), stat[id]->loop?TRUE:FALSE);
	//printf("(we're using voice %d for it)\n", stat[id]->voice);
	
	if(stat[id]->voice != -1) {
		stat[id]->status = SoundStat::STATUS_PLAYING;
		return true;
	}
	else {
		Logfile::log("Tried to play a sound, but got voice -1 instead.\n");
		stat[id]->status = SoundStat::STATUS_STOPPED;
		return false;
	}
}


// Returns true if the sample was stopped, false otherwise
bool Sound::stop(uint id) {
	if(id >= stat.size()) return false;
	if(isPlaying(id) || stat[id]->status == SoundStat::STATUS_PAUSED) stop_sample(stat[id]->sample);
	stat[id]->status = SoundStat::STATUS_STOPPED;
	return true;
}

void Sound::stopAll() {
	uint i;
	for(i=0; i<stat.size(); i++) stop(i);
}

bool Sound::isPlaying(uint id) {
	if(id >= stat.size()) return false;
	if(stat[id]->voice < 0) return false;
	return voice_get_position(stat[id]->voice)==-1?false:true;
}

void Sound::pauseAll() {
	uint i;
	for(i=0; i<stat.size(); i++) pause(i);
}


// Takes the voice currently playing the sample, sets it to loop, makes the volume go to zero,
// and saves the current position of the sample which is playing.
bool Sound::pause(uint id) {
	if(id >= stat.size()) return false;
	if(stat[id]->status != SoundStat::STATUS_PLAYING) return false;
	
	stat[id]->position = voice_get_position(stat[id]->voice);
	if(stat[id]->position == -1) {
		stat[id]->status = SoundStat::STATUS_STOPPED;
		return false;
	}
	
	voice_set_volume(stat[id]->voice, 0);
	voice_set_playmode(stat[id]->voice, PLAYMODE_LOOP);
	stat[id]->status = SoundStat::STATUS_PAUSED;
	return true;
}

void Sound::unpauseAll() {
	uint i;
	for(i=0; i<stat.size(); i++) unpause(i);
}

// Restores a sample to its previous state after a pause 
bool Sound::unpause(uint id) {
	if(id >= stat.size()) return false;
	if(stat[id]->status != SoundStat::STATUS_PAUSED) return false;
	
	voice_set_playmode(stat[id]->voice, stat[id]->loop?PLAYMODE_LOOP:PLAYMODE_PLAY);
	voice_set_position(stat[id]->voice, stat[id]->position);
	voice_set_volume(stat[id]->voice, (int)(stat[id]->vol * MAX_VOLUME));
	return true;
}


bool Sound::changeVol(uint id, float vol) {
	return alter(id, vol, -1, -1, -123);
}

bool Sound::changePan(uint id, float pan) {
	return alter(id, -1, pan, -1, -123);
}

bool Sound::changeFreq(uint id, float freq) {
	return alter(id, -1, -1, freq, -123);
}

bool Sound::changeLoop(uint id, bool loop) {
	return alter(id, -1, -1, -1, loop?TRUE:FALSE);
}

