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
 
 
 
// TheGame.h: interface for the TheGame class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_THEGAME_H__C1606F47_E819_11DA_9D08_00D0594C1148__INCLUDED_)
#define AFX_THEGAME_H__C1606F47_E819_11DA_9D08_00D0594C1148__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Logfile.h"
#include "Menu.h"
#include "Timer.h"
#include "Level.h"
#include "Credits.h"
#include "Configuration.h"
#include "TheLander.h"
#include "TransitionStarSet.h"
#include "KeyHandler.h"
#include "FireballSet.h"
#include "ParticleSource.h"
#include "Music.h"
#include "Sound.h"


enum gameModeEnum { PURE_TRANSITION, PLAYING, RESUME, 
					LEVEL_TRANSITION, THEMENU, INTRO, 
					CREDITS, HELP, OPTIONS, ENDING,
					RESTART_GAME, LICENSE };

enum gameStateEnum { ACTION, DEAD, LAND, OUT_OF_SKY, 
					 NEXT_LEVEL, GAME_OVER, TITLE_SCREEN };

enum titleScreenModeEnum {MOVE_IN, STOP, MOVE_OUT, IN_STATE, OUT_STATE};

enum thrustPowerEnum {HIGH, MEDIUM, LOW};

#define COLOR_BLACK0				COLOR_BLACK
#define COLOR_BLACK					makecol(0,0,0)
#define COLOR_WHITE					makecol(255,255,255)
#define COLOR_VELOCITY_BAR			makecol(255,255,0)
#define COLOR_VELOCITY_ZONE			makecol(0,255,0)
#define COLOR_FUEL_LEFT				makecol(157,44,40)
#define COLOR_FUEL_TEXT				makecol(214,105,101)
#define COLOR_SCORE					makecol(68,198,246)
#define COLOR_BLUE					makecol(0,0,255)
#define COLOR_GREEN					makecol(157,44,40)
#define COLOR_RED					makecol(255,0,0)


#define VERSION_MAJOR	2
#define VERSION_MINOR	51
#define VERSION_STRING	"2.51"


#define GAME_W	640
#define GAME_H	480
#define ZOOM_W	TheGame::LEVEL_W/4.0f
#define ZOOM_H	TheGame::LEVEL_H/4.0f


#define GRAVITY 0.1f


class TheGame  
{
public:
	TheGame(int fullscreen);
	virtual ~TheGame();

	static int LEVEL_W, LEVEL_H;	// width and height of each level



private:
	void init();

	void doIntro(double elapsedTime, struct BITMAP *buffer);
	void doTransition(double elapsetTime, struct BITMAP *buffer);
	void doGame(double elapsedTime, struct BITMAP *buffer, int keys);
	void doNextLevel(double elapsedTime, struct BITMAP *buffer);
	void doRestartGame(double elapsedTime, struct BITMAP *buffer);
	void doMainMenu(double elapsedTime, struct BITMAP *buffer);
	void doConfigMenu(double elapsedTime, struct BITMAP *buffer);
	void doHelp(double elapsedTime, struct BITMAP *buffer);

	void newGame();
	void restartLevel();
	void quitGame();
	void continueGame();
	void setPalette();
	void changeGameState(enum gameStateEnum);
	void changeGameMode(enum gameModeEnum);
	void screenshot();
	void drawPlayfield(BITMAP *buffer);
	void drawInterface(BITMAP *buffer);

	void flip_pages();

	void thrustLeft(float power, float timeElapsed);
	void thrustRight(float power, float timeElapsed);
	void thrustUp(float power, float timeElapsed);
	void thrust(float x, float y, float angle, float power, float timeElapsed);


private:
	class Logfile log;
	class Menu menu, optionsMenu, confirmNewGameMenu;
	class Credits credits, ending;
	class Timer timer;
	class TheLander lander;
	class TransitionStarSet stars;
	class KeyHandler keys;
	class FireballSet fireballs, nextLevelBalls;
	//class ParticleSource fireballs, nextLevelBalls;
	int currentLevel;
	class Level *level;

	gameModeEnum gameMode, oldGameMode, lastPlayingGameMode;					// Current mode of the game
	gameStateEnum gameState;	// Status of player (dead, outofsky, etc)
	titleScreenModeEnum titleScreenMode;		// Current mode of the title screen
	gameModeEnum transitionAction;				// Action to perform after transition completes

	bool flipping;			// if we are doing page flipping
	struct BITMAP *buffer;
	struct BITMAP *page1, *page2;

	float score;			// Player's current score
	int scoreToBeat;		// Score to beat to advance to next level
	int highScore;			// Highest score on record
	int targetScore;		// Score that will be counted up to when landed

	bool done;				// When true, program exits

	int LANDER_W, LANDER_H;
	
	// some legacy variables that i dont care enough to improve on
	int PLAY_ROCKET, rocket_freq;

	float zoom_factor;			// the level of zoom the game is currently in
	float screenX, screenY;
	float edgeR, edgeB;			// right and bottom edges of screen
	enum { NORMAL, 
		   ZOOM2X, 
		   ZOOM5X, 
		   ZOOM10X } bgFrame;
	
	float landerAdvY;			// y-coordinate of the lander between levels

	float stateTimer;			// For any state, to measure time
	float starSpeed;			// Speed of stars scrolling in background


	float transitionX, transitionY;			// Offsets for the screen during transitions

};

#define NUM_DATA_ELEMENTS  40

#ifndef IN_MAIN_CPP
extern int setup_screen(int fullscreen);
extern DATAFILE *data[NUM_DATA_ELEMENTS];
extern class Configuration *config, *config_backup;
extern class Music music;
extern class Sound sound;
extern class Credits gpl;
#endif

#endif // !defined(AFX_THEGAME_H__C1606F47_E819_11DA_9D08_00D0594C1148__INCLUDED_)
