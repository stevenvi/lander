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
 
 
 
// KeyHandler1.cpp: implementation of the KeyHandler class.
//
//////////////////////////////////////////////////////////////////////

#include "KeyHandler.h"
#include "Logfile.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

KeyHandler::KeyHandler() {
	Logfile::log("+KeyHandler at 0x%x\n", this);

	set_config_file("lander.ini");
	kLeft = get_config_int("keys","left",KEY_RIGHT);
	kRight= get_config_int("keys","right",KEY_LEFT);
	kMax = get_config_int("keys","max",KEY_Q);
	kMed = get_config_int("keys","med",KEY_A); 
	kMin = get_config_int("keys","mid",KEY_Z);
	kAll = get_config_int("keys","all",KEY_W);
}

KeyHandler::~KeyHandler()
{
	// Save key configuration
	set_config_file("lander.ini");
	set_config_int("keys","left",kLeft);
	set_config_int("keys","right",kRight);
	set_config_int("keys","max",kMax);
	set_config_int("keys","med",kMed); 
	set_config_int("keys","min",kMin);
	set_config_int("keys","all",kAll);

	flush_config_file();
	Logfile::log("-KeyHandler at 0x%x\n", this);
}


// Returns a bitmask of the keys that were pressed
int KeyHandler::getKeys() {
	int ret = 0;

	if(keypressed()) {
		if(key[kRight]) ret += K_RIGHT;
		if(key[kLeft]) ret += K_LEFT;

		if(key[kMax]) ret += K_MAX;
		else if(key[kMed]) ret += K_MED;
		else if(key[kMin]) ret += K_MIN;

		if(key[kAll]) ret = 0x7;

		if(key[KEY_ESC]) ret = -1;
	}

	return ret;
}

