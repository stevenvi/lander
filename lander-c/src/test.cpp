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
 
 
 
// a test of things...
#include <allegro.h>
#include <stdio.h>
#include <aldumb.h>



int main(int argc, char *argv[]) {
	printf("Initializing Allegro.\n");
	allegro_init();
	install_keyboard();
	install_timer();
	install_sound(DIGI_AUTODETECT, MIDI_NONE, NULL);
	
	printf("Initializing DUMB.\n");
	atexit(&dumb_exit);
	dumb_register_dat_s3m_quick(DUMB_DAT_S3M);
	
	printf("Loading datafile.\n");
	DATAFILE *music = load_datafile("music.dat");
	if(!music) {
		printf("Error loading music datafile.\n");
		return 1;
	}
	
	
	printf("Loading DUH.\n");
	DUH *bgsong = (DUH*)music[0].dat;
	if(!bgsong) {
		printf("Error getting song from datafile.\n");
		return 1;
	}
	
	printf("Starting DUH player.\n");
	AL_DUH_PLAYER *bgsong_player = al_start_duh(bgsong, 2, 0, 1.0f, 4096, 48000);
	if(!bgsong_player) {
		printf("Error starting player.\n");
		return 1;
	}
	
	
	printf("Entering main loop.\n");
	while(!key[KEY_ESC]) {
		al_poll_duh(bgsong_player);
		rest(0);
	}
	
	printf("Exiting successfully.\n");
	return 0;
}
END_OF_MAIN()
