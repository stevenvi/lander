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
 
 
 
// collide.h


#ifndef _COLLIDE_H
#define _COLLIDE_H



#define NUM_CHUNKS  20  // The number of x 32 bit chunks in the ppcol mask
#define NUM_Y       480 // The number of y rows in the ppcol mask
#define MAX_SPRITES 10  // Number of bitmaps in datafile




typedef struct 
{
  int bb_height;
  int bb_width;
  int max_chunk;
  unsigned long int sp_mask[NUM_Y][NUM_CHUNKS];
} t_spr_mask;



extern void mk_spr_mask(struct BITMAP *s3, int spr_no);
extern int check_pp_collision(int spr1, int spr1x, int spr1y, int spr2, int spr2x, int spr2y);



#endif // _COLLIDE_H

