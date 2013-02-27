/*  coreset.  Creates core data for expansion levels.
 *
 * Saves data to core_exp.ini
 *
 */



#include <allegro.h>
#include <stdio.h>
#include <stdlib.h>

#include "data.h"


char *msg[] = {"Click to set 2x zoom window",				// 0
				"Click to set 5x zoom window",				// 1
				"Click to set 10x zoom window",				// 2

				"Click to set left end of 2x pad",			// 3
				"Click to set right end of 2x pad",			// 4

				"Click to set left end of 5x pad",			// 5
				"Click to set right end of 5x pad",			// 6

				"Click to set left end of 10x pad",			// 7
				"Click to set right end of 10x pad",		// 8

				"Click to set 2x label",					// 9
				"Click to set 5x label",					// 10
				"Click to set 10x label",					// 11
				"Click to set brand" };						// 12

int mode=0;
int coreData[23];


int main(int argc, char *argv[]) {
	allegro_init();
	int depth = desktop_color_depth();
	if(depth == 0) depth = 24;
	set_color_depth(depth);
	if(set_gfx_mode(GFX_AUTODETECT,640,480,0,0) != 0) {
		allegro_message("Error setting screen mode.\n");
		return 1;
	}
	install_keyboard();
	install_mouse();

	char fn[512]="\0";
	int r = file_select_ex("Select level bitmap",fn,"bmp",512,0,0);
	if(r == 0) return 0;


	BITMAP *buffer = create_bitmap(SCREEN_W,SCREEN_H);

	PALETTE pal;
	BITMAP *bmp = load_bmp(fn,pal);
	BITMAP *temp;
	int WHITE = makecol(255,128,128);
	set_palette(pal);

	DATAFILE *data = load_datafile("lander.dat");


//	memset(coreData, 0, 15*sizeof(int));

	while(mode < 13) {
		// I do the drawing stuff first
		clear(buffer);
		switch(mode) {
		case 0:
		case 1:
		case 2:
			blit(bmp,buffer,0,0,0,0,bmp->w,bmp->h);
			rect(buffer,mouse_x,mouse_y,mouse_x+bmp->w/4,mouse_y+bmp->h/4,WHITE);
			break;

		case 3:
			coreData[6] = mouse_x/4;
			coreData[7] = mouse_y/4;
			stretch_blit(bmp,buffer,coreData[0],coreData[1],bmp->w/4,bmp->h/4,0,0,bmp->w,bmp->h);
			rectfill(buffer, coreData[6]*4,
							 coreData[7]*4,
							 coreData[6]*4 + 4,
							 coreData[7]*4 + 4, WHITE);
			break;

		case 4:
			stretch_blit(bmp,buffer,coreData[0],coreData[1],bmp->w/4,bmp->h/4,0,0,bmp->w,bmp->h);
			rectfill(buffer, coreData[6]*4 - coreData[0]*4,
							 coreData[7]*4 - coreData[1]*4,
							 mouse_x/4*4,
							 coreData[7]*4 - coreData[1]*4 + 4, WHITE);
			break;

		case 5:
			coreData[9] = mouse_x/4;
			coreData[10] = mouse_y/4;
			stretch_blit(bmp,buffer,coreData[2],coreData[3],bmp->w/4,bmp->h/4,0,0,bmp->w,bmp->h);
			rectfill(buffer, coreData[9]*4,
							 coreData[10]*4,
							 coreData[9]*4 + 4,
							 coreData[10]*4 + 4, WHITE);
			break;

		case 6:
			stretch_blit(bmp,buffer,coreData[2],coreData[3],bmp->w/4,bmp->h/4,0,0,bmp->w,bmp->h);
			rectfill(buffer, coreData[9]*4 - coreData[2]*4,
							 coreData[10]*4 - coreData[3]*4,
							 mouse_x/4*4,
							 coreData[10]*4 - coreData[3]*4 + 4, WHITE);
			break;

		case 7:
			coreData[12] = mouse_x/4;
			coreData[13] = mouse_y/4;
			stretch_blit(bmp,buffer,coreData[4],coreData[5],bmp->w/4,bmp->h/4,0,0,bmp->w,bmp->h);
			rectfill(buffer, coreData[12]*4,
							 coreData[13]*4,
							 coreData[12]*4 + 4,
							 coreData[13]*4 + 4, WHITE);
			break;

		case 8:
			stretch_blit(bmp,buffer,coreData[4],coreData[5],bmp->w/4,bmp->h/4,0,0,bmp->w,bmp->h);
			rectfill(buffer, coreData[12]*4 - coreData[4]*4,
							 coreData[13]*4 - coreData[5]*4,
							 mouse_x/4*4,
							 coreData[13]*4 - coreData[5]*4 + 4, WHITE);
			break;

		case 9:
			stretch_blit(bmp,buffer,coreData[0],coreData[1],bmp->w/4,bmp->h/4,0,0,bmp->w,bmp->h);
			temp = (BITMAP*)data[B_LABEL2].dat;
			stretch_sprite(buffer, temp, mouse_x/4*4, mouse_y/4*4, temp->w*4, temp->h*4);
			break;

		case 10:
			stretch_blit(bmp,buffer,coreData[2],coreData[3],bmp->w/4,bmp->h/4,0,0,bmp->w,bmp->h);
			temp = (BITMAP*)data[B_LABEL5].dat;
			stretch_sprite(buffer, temp, mouse_x/4*4, mouse_y/4*4, temp->w*4, temp->h*4);
			break;

		case 11:
			stretch_blit(bmp,buffer,coreData[4],coreData[5],bmp->w/4,bmp->h/4,0,0,bmp->w,bmp->h);
			temp = (BITMAP*)data[B_LABEL10].dat;
			stretch_sprite(buffer, temp, mouse_x/4*4, mouse_y/4*4, temp->w*4, temp->h*4);
			break;

		case 12:
			blit(bmp,buffer,0,0,0,0,bmp->w,bmp->h);
			draw_sprite(buffer, (BITMAP*)data[B_BRAND].dat, mouse_x, mouse_y);
			break;
		}

		textprintf_right_ex(buffer,font,SCREEN_W,0,WHITE,-1,msg[mode]);
		blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);

		
		// If we hit escape, kill the program
		if(key[KEY_ESC]) return 0;

		// Process mouse clicking
		if(mouse_b & 1) {
			switch(mode) {
			case 0:
			case 1:
			case 2:
				coreData[0+mode*2] = mouse_x;
				coreData[1+mode*2] = mouse_y;
				break;

			case 3:
				coreData[6] = coreData[0] + mouse_x/4;
				coreData[7] = coreData[1] + mouse_y/4;
			case 4:
				coreData[8] = coreData[0] + mouse_x/4;
				break;

			case 5:
				coreData[9] = coreData[2] + mouse_x/4;
				coreData[10] = coreData[3] + mouse_y/4;
			case 6:
				coreData[11] = coreData[2] + mouse_x/4;
				break;
			
			case 7:
				coreData[12] = coreData[4] + mouse_x/4;
				coreData[13] = coreData[5] + mouse_y/4;
			case 8:
				coreData[14] = coreData[4] + mouse_x/4;
				break;

			case 9:
				coreData[15] = coreData[0] + mouse_x/4;
				coreData[16] = coreData[1] + mouse_y/4;
				break;

			case 10:
				coreData[17] = coreData[2] + mouse_x/4;
				coreData[18] = coreData[3] + mouse_y/4;
				break;

			case 11:
				coreData[19] = coreData[4] + mouse_x/4;
				coreData[20] = coreData[5] + mouse_y/4;
				break;

			case 12:
				coreData[21] = mouse_x;
				coreData[22] = mouse_y;
				break;
			}

			mode++;

			// this is the worst way to prevent holding the button
			rest(200);
		}
		if(mouse_b & 2) {
			mode--;
			if(mode < 0) mode = 0;
			rest(150);
		}
	}

	destroy_bitmap(buffer);

	// Save data to core file
	set_config_file("core_exp.ini");
	int levels = get_config_int("","levels",0);

	char section[512];
	sprintf(section,"level%02d",levels);

	set_config_int(section,"zoom2x",coreData[0]);
	set_config_int(section,"zoom2y",coreData[1]);
	set_config_int(section,"zoom5x",coreData[2]);
	set_config_int(section,"zoom5y",coreData[3]);
	set_config_int(section,"zoom10x",coreData[4]);
	set_config_int(section,"zoom10y",coreData[5]);

	set_config_int(section,"pad2x1",coreData[6]);
	set_config_int(section,"pad2x2",coreData[8]);
	set_config_int(section,"pad2y",coreData[7]);

	set_config_int(section,"pad5x1",coreData[9]);
	set_config_int(section,"pad5x2",coreData[11]);
	set_config_int(section,"pad5y",coreData[10]);

	set_config_int(section,"pad10x1",coreData[12]);
	set_config_int(section,"pad10x2",coreData[14]);
	set_config_int(section,"pad10y",coreData[13]);

	set_config_int(section,"label2x",coreData[15]);
	set_config_int(section,"label2y",coreData[16]);

	set_config_int(section,"label5x",coreData[17]);
	set_config_int(section,"label5y",coreData[18]);

	set_config_int(section,"label10x",coreData[19]);
	set_config_int(section,"label10y",coreData[20]);

	set_config_int(section,"brandx",coreData[21]);
	set_config_int(section,"brandy",coreData[22]);


	set_config_int("", "levels", levels+1);

	flush_config_file();

	set_gfx_mode(GFX_TEXT,0,0,0,0);
	allegro_message("Saved as %s in core_exp.ini\nBe sure to set the filename accordingly.", section);
	return 0;
}
END_OF_MAIN();
