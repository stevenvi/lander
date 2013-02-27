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
 
 
 
// COLLIDE.C
// PIXEL-PRECISION BITMAP COLLISION ROUTINES FOR LANDER
// 2003-01-15: Very old code, this stuff.  Taken from original game :-p


#include <allegro.h>
#include "collide.h"
#include "Logfile.h"



t_spr_mask spr_mask[MAX_SPRITES];


int get_trans_color() {
	switch(get_color_depth()) {
	case 8: return MASK_COLOR_8;
	case 15: return MASK_COLOR_15;
	case 16: return MASK_COLOR_16;
	case 24: return MASK_COLOR_24;
	case 32: return MASK_COLOR_32;
	default: return 0;
	}
}

void mk_spr_mask(BITMAP *s3, int spr_no)
{
	int bb_height=0;
	int bb_width=0;
	int x1,y1,z;
	int p;

	
	/* Clears the area is overwriting a mask */
	for(y1=0;y1<NUM_Y;y1++)
	{
		for(z=0;z<NUM_CHUNKS;z++)
		{
			for(x1=(z*32);x1<((z*32)+32);x1++)
			{
				spr_mask[spr_no].sp_mask[y1][z]=0x00000000 >> (x1 - ((z+1)*32));
			}
		}
	}

	// loop over all y values
	for(y1=0; y1<NUM_Y && y1<s3->h; y1++)
	{
		// loop over each 32-pixel chunk
		for(z=0; z<NUM_CHUNKS; z++)
		{
			// loop over the 32 pixels in each chunk
			for(x1=(z*32); x1<((z*32)+32) && x1<s3->w; x1++)
			{
				p = getpixel(s3,x1,y1);
				// here we make sure that p is the trans pixel
				if(p != get_trans_color())
				{
					if(z>spr_mask[spr_no].max_chunk) spr_mask[spr_no].max_chunk = z;
					if(y1>bb_height) bb_height=y1;
					if(x1>bb_width)  bb_width =x1;
					spr_mask[spr_no].sp_mask[y1][z] += 0x80000000 >> (x1 - ((z+1)*32));
				}
			}
		}
	}

	spr_mask[spr_no].bb_height=bb_height;
	spr_mask[spr_no].bb_width =bb_width;
}





int check_pp_collision(int spr1, int spr1x, int spr1y, int spr2, int spr2x, int spr2y)
{
	int dx1,dx2,dy1,dy2,ddy1,ddy2;
	int spr1_chunk,spr2_chunk;
	int dx1_chunk,dx2_chunk;

	{
		if(spr1x>spr2x)
		{
			dx1=0;               // don't need to shift sprite 1
			dx2=spr1x-spr2x;     // need to shift sprite 2 left
		}
		else
		{
			dx1=spr2x-spr1x;     // need to shift sprite 1 left
			dx2=0;               // don't need to shift sprite 2
		}

		if(spr1y>spr2y)
		{
			dy1=0;               // don't need to skip any rows for sprite 1
			dy2=spr1y-spr2y;     // need to skip this many rows for sprite 2
		}
		else
		{
			dy1=spr2y-spr1y;     // need to skip this many rows for sprite 1
			dy2=0;               // don't need to skip any rown for sprite 2
		}

		spr1_chunk = dx1/32;
		spr2_chunk = dx2/32;
		dx1_chunk = dx1 - (32 * spr1_chunk);
		dx2_chunk = dx2 - (32 * spr2_chunk);

		while((spr1_chunk <= spr_mask[spr1].max_chunk) & (spr2_chunk <= spr_mask[spr2].max_chunk))
		{
			ddy1 = dy1;
			ddy2 = dy2;
			while((ddy1<=spr_mask[spr1].bb_height)&&(ddy2<=spr_mask[spr2].bb_height))
			{
				if((spr_mask[spr1].sp_mask[ddy1][spr1_chunk]<<dx1_chunk)&(spr_mask[spr2].sp_mask[ddy2][spr2_chunk]<<dx2_chunk))
					return TRUE;
				ddy1++;
				ddy2++;
			}

			if((!dx1_chunk) && (!dx2_chunk)) //If both sprites lined up on x-axis
			{
				spr1_chunk++;
				spr2_chunk++;
			}
			else
			{
				if(!dx1_chunk)
				{
					spr2_chunk++;
					dx1_chunk = 32 - dx2_chunk;
					dx2_chunk = 0;
				}
				else if(!dx2_chunk)
				{
					spr1_chunk++;
					dx2_chunk = 32 - dx1_chunk;
					dx1_chunk = 0;
				}
			}
		}
		return FALSE;  // No collision
	}
}




