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
/* XPM */
static const char *allegico_xpm[] = {
/* columns rows colors chars-per-pixel */
"32 32 12 1",
"  c #202020",
". c #646464",
"X c #747474",
"o c #888888",
"O c #989898",
"+ c gray66",
"@ c gray72",
"# c gray80",
"$ c gainsboro",
"% c #ECECEC",
"& c gray99",
"* c None",
/* pixels */
"********************************",
"********************************",
"********************************",
"*************++oo***************",
"***********++++oooo*************",
"*********++++++oooooo***********",
"******+++++++++ooooooooo********",
"****+++++++++++ooooooooooo******",
"**+++++++++++++ooooooooooooo****",
"+++++++++++++++ooooooooooooooo**",
"*@@@@@@@@@@@@@XXXXXXXXXXXXXXX***",
"**@@@@@@@@@@@@XXXXXXXXXXXXXXX***",
"**@@@@@@@@@@@XXXXXXXXXXXXXXX****",
"***@@@@@@@@@@XXXXXXXXXXXXXX*****",
"****@@@@@@@@XXXXXXXXXXXXXXX*****",
"*****@@@@@@@XXXXXXXXXXXXXX******",
"***%%OOOO@@XXXXXXXXXXX$$$$$$****",
"**%%%OOOOO@XXXXXXXXXX$$$$$$$****",
"*%%%*     XXXXXXXXXXXX.....$$***",
"*&&*      XXXXXXXXXXXX.....#$$**",
"&&&*****@XXXXXXXXXXXXXX*****$$**",
"&&&******XXXXXXXXXXXXX*****.$$$*",
"%%%************************.$$$*",
"%%%************************.$$$*",
"%%%************************.$$$*",
"%%%************************.$$$*",
"%%%************************.$$$*",
"%%%************************.$$$*",
"%%%************************.$$$*",
"********************************",
"********************************",
"********************************"
};
#if defined ALLEGRO_WITH_XWINDOWS && defined ALLEGRO_USE_CONSTRUCTOR
extern void *allegro_icon;
CONSTRUCTOR_FUNCTION(static void _set_allegro_icon(void));
static void _set_allegro_icon(void)
{
    allegro_icon = allegico_xpm;
}
#endif
