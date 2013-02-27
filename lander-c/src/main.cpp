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

#ifdef _WIN32
#include <winalleg.h>
#endif

#define IN_MAIN_CPP

#include "aldumb.h"

#include "Timer.h"
#include "Logfile.h"
#include "TheLander.h"
#include "TheGame.h"
#include "Music.h"
#include "Sound.h"
#include "Configuration.h"

#include "data.h"

DATAFILE_INDEX *data_idx;
DATAFILE *data[NUM_DATA_ELEMENTS];
Configuration *config, *config_backup;
Music music;
Sound sound;
int dw, dh, desktop_res_status;
float desktop_ratio;
int fs_w, fs_h;

int setup_screen(int fullscreen) {
	Logfile::log("Setting screen mode...\n");
	if(fullscreen) {
		if(set_gfx_mode(GFX_AUTODETECT_FULLSCREEN, fs_w, fs_h, 0, 0) != 0) {
			fullscreen = FALSE;
			if(set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640, 480, 0, 0) != 0) {
				Logfile::log("Couldn't create a window at all!\n");
				allegro_message("FATAL ERROR: Could not create a window.");
				allegro_exit();
				exit(-1);
			}
			else {
				Logfile::log("Using windowed 640x480 mode.\n");
				return FALSE;
			}
		}
		else {
			Logfile::log("Using fullscreen %dx%d mode.\n", fs_w, fs_h);
			return TRUE;
		}
	}
	else {
		if(set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640, 480, 0, 0) != 0) {
			fullscreen = TRUE;
			if(set_gfx_mode(GFX_AUTODETECT_FULLSCREEN, fs_w, fs_h, 0, 0) != 0) {
				Logfile::log("Couldn't create a window at all!\n");
				allegro_message("FATAL ERROR: Could not create a window.");
				allegro_exit();
				exit(-1);
			}
			else {
				Logfile::log("Using fullscreen %dx%d mode.\n", fs_w, fs_h);
				return TRUE;
			}
		}
		else {
			Logfile::log("Using windowed 640x480 mode.\n");
			return FALSE;
		}
	}
}


// returns the least common divisor of two numbers
int LCD(int a, int b) {
	if(a == b) return a;
	else if(a == 1 || b == 1) return 1;
	else if(a > b) return LCD(a-b, b);
	else return LCD(a, b-a);
}


void get_video_info() {
	// Determine depth
	int depth = desktop_color_depth();
	if(depth == -1) depth = 32;
	set_color_depth(depth);
	Logfile::log("%d bpp used.\n", depth);

	// Determine screen dimensions
	desktop_res_status = get_desktop_resolution(&dw, &dh);
	if(desktop_res_status == 0) desktop_ratio = dw / (float)dh;
	else desktop_ratio = 4/3.0f;
		
	if(desktop_ratio > 4/3.0f) {
		fs_w = (int)(desktop_ratio * 480);
		fs_h = 480;
		int lcd = LCD(fs_w, fs_h);
		Logfile::log("Widescreen (%d:%d) monitor detected.\n", fs_w/lcd, fs_h/lcd);
	}
	else if(desktop_ratio < 4/3.0f) {
		fs_w = 640;
		fs_h = (int)(desktop_ratio * 640);
		int lcd = LCD(fs_w, fs_h);
		Logfile::log("Tallscreen (%d:%d) monitor detected.\n", fs_w/lcd, fs_h/lcd);
		Logfile::log("Note that this type of monitor has never been tested with this game!\n");
	}
	else {
		fs_w = 640;
		fs_h = 480;
		Logfile::log("Standard (4:3) monitor detected.\n");
	}

	// If we're in 640x480, don't bother discovering video modes,
	// That thing is so standard that it's not an issue.
	if(fs_w == 640 && fs_h == 480) return;

	// Discover available modes
	Logfile::log("Discovering available video modes.\n");
	GFX_MODE_LIST *mode;
	int i, d;
#ifdef _WIN32
	int driver[] = { GFX_DIRECTX_ACCEL, GFX_DIRECTX_SOFT, GFX_DIRECTX_SAFE, 
		GFX_DIRECTX_WIN, GFX_GDI, 0 };
#elif DJGPP
	int driver[] = { GFX_VBEAF, GFX_VESA3, GFX_VESA2L, GFX_VESA2B, GFX_VESA1, 0 };
#else
	int driver[] = { GFX_XDGA2, GFX_XDGA2_SOFT, GFX_XWINDOWS_FULLSCREEN, 
		GFX_FBCON, GFX_VBEAF, GFX_SVGALIB, 0 };
#endif

	// Count how many drivers there are to consider
	int numDrivers;
	for(numDrivers=0; driver[numDrivers]!=0; numDrivers++);

	bool foundOurMode = false;

	for(d=0; d<numDrivers; d++) {
		mode = get_gfx_mode_list(driver[d]);
		if(!mode) continue;
		for(i=0; i<mode->num_modes; i++) {
			Logfile::log("\t%dx%dx%dbpp\n", mode->mode[i].width, mode->mode[i].height, mode->mode[i].bpp);
			if(mode->mode[i].bpp != depth) continue;
			if(mode->mode[i].height != fs_h) continue;
			if(mode->mode[i].width != fs_w) continue;
			Logfile::log("There is a driver with the mode we prefer!\n");
			i = mode->num_modes;
			d = numDrivers;
			foundOurMode = true;
		}
		destroy_gfx_mode_list(mode);
	}

	// If we haven't found our mode, then force the default mode
	if(!foundOurMode) {
		Logfile::log("No fullscreen drivers capable of our mode were found.  Forcing 640x480.\n");
		fs_w = 640;
		fs_h = 480;
	}
}


int main(int argc, char *argv[]) {
	allegro_init();
	install_keyboard();
	install_mouse();
	install_sound(DIGI_AUTODETECT, MIDI_NONE, NULL);

	// Determine what sort of screen we're displaying this on
	get_video_info();


	// Read configuration file
	//set_config_file("lander.ini");
	//int fullscreen = get_config_int("window","fullscreen",FALSE);
	
	// load the config settings
	config = new Configuration();
	config_backup = config;
	Logfile::log("config is at address 0x%x.\n", config);

	config->setFullscreen(setup_screen(config->isFullscreen()?TRUE:FALSE));

	set_window_title("Lander!  v" VERSION_STRING);
	//set_close_button_callback

	Logfile::log("Initializing DUMB.\n");
	atexit(&dumb_exit);
	dumb_register_dat_s3m_quick(DUMB_DAT_S3M);


	// Load data file -- I finally got rid of that dumb password
	packfile_password(NULL);
	data_idx = create_datafile_index("lander.dat");
	if(!data_idx)
	{
		allegro_exit();
		allegro_message("Error loading datafile!\nPlease reinstall the software.");
		exit(1);
	}

	set_color_conversion(COLORCONV_EXPAND_256 | COLORCONV_KEEP_TRANS);



	// Is there a better way to load data files without having to manually
	// convert all 8-bit bitmaps?  I suppose not, as we need to know the palettes.
	// 
	// Then again, if I loaded it into memory as an 8-bit image and applied the
	// palette at drawing time, it would save memory.  But it requires extra
	// processing.  Hmmm.

	// Level backgrounds
	int i;
	for(i=0; i<9; i++) {
		data[P_1 + i] = load_datafile_object_indexed(data_idx, P_1 + i);
		set_palette((RGB*)data[P_1 + i]->dat);
		data[B_BG_1 + i] = load_datafile_object_indexed(data_idx, B_BG_1 + i);
	}

	// Company logo
	data[P_COMPANY_LOGO] = load_datafile_object_indexed(data_idx, P_COMPANY_LOGO);
	set_palette((RGB*)data[P_COMPANY_LOGO]->dat);
	data[B_COMPANY_LOGO] = load_datafile_object_indexed(data_idx, B_COMPANY_LOGO);


	// Standard palette bitmaps
	data[P_STD] = load_datafile_object_indexed(data_idx, P_STD);
	set_palette((RGB*)data[P_STD]->dat);
	data[B_ADVANCE] = load_datafile_object_indexed(data_idx, B_ADVANCE);
	data[B_ARROW] = load_datafile_object_indexed(data_idx, B_ARROW);
	data[B_LANDER] = load_datafile_object_indexed(data_idx, B_LANDER);

	// Titlescreen
	data[P_TITLESCREEN] = load_datafile_object_indexed(data_idx, P_TITLESCREEN);
	
	set_palette_range((RGB*)data[P_TITLESCREEN]->dat,0,223,TRUE);
	data[B_TITLE_LANDER] = load_datafile_object_indexed(data_idx, B_TITLE_LANDER);

	set_palette((RGB*)data[P_TITLESCREEN]->dat);
	data[B_TITLESCREEN] = load_datafile_object_indexed(data_idx, B_TITLESCREEN);

	// Brand
	data[P_BRAND] = load_datafile_object_indexed(data_idx, P_BRAND);
	set_palette((RGB*)data[P_BRAND]->dat);
	data[B_BRAND] = load_datafile_object_indexed(data_idx, B_BRAND);

	// Labels
	data[P_LABEL] = load_datafile_object_indexed(data_idx, P_LABEL);
	set_palette((RGB*)data[P_LABEL]->dat);
	data[B_LABEL2] = load_datafile_object_indexed(data_idx, B_LABEL2);
	data[B_LABEL5] = load_datafile_object_indexed(data_idx, B_LABEL5);
	data[B_LABEL10] = load_datafile_object_indexed(data_idx, B_LABEL10);

	// The fonts and extra stuff
	data[F_HUGE_0] = load_datafile_object_indexed(data_idx, F_HUGE_0);
	data[F_SMALL_0] = load_datafile_object_indexed(data_idx, F_SMALL_0);
	data[P_FLAMES] = load_datafile_object_indexed(data_idx, P_FLAMES);
	
	
	// Load all samples
	data[S_ROCKET] = load_datafile_object_indexed(data_idx, S_ROCKET);
	data[S_SCORE] = load_datafile_object_indexed(data_idx, S_SCORE);
	data[S_CRASH] = load_datafile_object_indexed(data_idx, S_CRASH);


	// Once upon a time I thought it was a good idea to keep the entire
	// game loop in a constructor.  Dumb idea in hindsight.
	TheGame *game = new TheGame(0);
	if(game) delete game;
	
	Logfile::log("config points to: 0x%x.\n", config);
	if(config) {
		delete config;
		config = 0;
	}
	flush_config_file();
	
	for(i=0; i<NUM_DATA_ELEMENTS; i++) if(data[i]) unload_datafile_object(data[i]);
	
	return 0;
}
END_OF_MAIN();
