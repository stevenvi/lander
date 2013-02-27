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
 
 
 
// TheGame.cpp: implementation of the TheGame class.
//
//////////////////////////////////////////////////////////////////////

#include <allegro.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.141592654f
#endif


#ifdef _DEBUG
#define UNHANDLED_CASE_ERROR	allegro_message("Unhandled case in %s line %d.", __FILE__, __LINE__);
#else
#define UNHANDLED_CASE_ERROR
#endif

#include "TheGame.h"
#include "Logfile.h"
#include "Timer.h"
#include "data.h"
#include "TheLander.h"
#include "KeyHandler.h"
#include "FireballSet.h"
#include "Credits.h"
#include "Sound.h"


int SND_ROCKET=-1, SND_SCORE=-1, SND_CRASH=-1;

int TheGame::LEVEL_W;
int TheGame::LEVEL_H;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TheGame::TheGame(int fullscr) :
// set up some variables
gameMode(INTRO),
oldGameMode(INTRO),
lastPlayingGameMode(PLAYING),
gameState(TITLE_SCREEN),
titleScreenMode(MOVE_IN),
stateTimer(0.0f),


// Define the credits
credits((FONT*)data[F_HUGE_0]->dat,
	"LANDER!  v" VERSION_STRING, "", 0, 
	"Director",
		"Steven Wallace", 0,
	"Producer",
		"Steven Wallace", 0,
	"Lead Programmer", 
		"Steven Wallace", 0,
	"Additional Programming",
		"Steven Wallace", 0,
	"Level Design", 
		"Steven Wallace", 0,
	"2D Art", 
		"Steven Wallace", 0,
	"3D Art", 
		"Steven Wallace", 0,
	"Music",
		"Steven Wallace", 0,
	"Sound Effect",
		"???", 0,
	"Play Testing", 
		"Isaac Jacobs",
		"Kirby \"Kirbles\" Runyon",
		"Steven Wallace", 0,
		
	"",
		"\"Special Thanks and much",
		"love to my supportive",
		"girlfriend who I love.",
		"I've been there for you,",
		"Steven, as you try making",
		"your theme to ... whatever.\"",
		"\"That's not funny!  Fix",
		"it!  You're such a dork!",
		"Stop it!\"",
		"    -Robyn Baker", 0,
	
	"", "", 0,

	"Credits for v1.0","", 0,
	"Research",
		"Devin Wallace", 0,
	"Play Testing",
		"Devin Wallace",
		"Ian Wallace",
		"Steven Wallace",0,

	"",
	"\"Did you fix it or did you",
	"leave it stupid?\"",

	"","","","","",0,
	"LANDER!", 
		"(c) Copyright 2001, 2006,", 
		"    2007 Chedda Cheeze",
		"",
		"No space vehicles were",
		"harmed during the",
		"production of this video",
		"game.  All space craft",
		"designs are original and",
		"do not reflect the current",
		"nature of scientific",
		"research.  Any resemblance",
		"to spacecraft living or",
		"dead is purely coincidental.",
		"",
		"This game was programmed",
		"in it's entirety over the",
		"course of a week.  You can ",
		"do it, too, kiddies!",
		"",
		"Note that the additions",
		"took six more years.  And",
		"it STILL has bugs.  Hrm.",
		"",
		"Well admittedly it was",
		"only about a total of two",
		"months' actual work.",
		"",
		"You should read the source",
		"code for this game, it's",
		"free under the GNU GPL.",
		"You can see the mess I",
		"made when the original",
		"goal was to clean up the",
		"LANDER v1.2 code."
		"",
		"",
		"",
		"",
		"", 
		"Have you heard of the",
		"band Isaac Jacobs & The ",
		"Abrahams?",
		"",
		"You ought to check 'em",
		"out, they friggin' rock!",
		"www.zendurl.com/jacobs",
		"",
		"Check out their Lander",
		"soundtrack album.  :)",
		"","","",""
		"I like bacon.",
		"","","","",
		"Pop in a can is sodalicious",
		"","","",""
		"Don't do drugs!",
		"","","","","","",
		"If you enjoyed this game, ",
		"you may be interested in",
		"the game Derek Smart's",
		"Desktop Commander, ",
		"available now for PC!",
		"Check with your local",
		"retailer for more details.",
		"","","","","","",0,
	"The Credits...",
		"...are over.",
		"",
		"",
		"",
		
	"\"Can you _PLEASE_ fix it",
	"and not make it stupid?\"", 0,
	
	"Special Thanks",
		"Robyn Baker", 
		"",
		"(I apologize for the",
		"merciless teasing above.",
		"You know it was funny",
		"though.  I'm writing",
		"this line right now on",
		"August 23rd, 2007.",
		"How long do you think",
		"it will be before you",
		"read these credits?)",
		0,
	0),

// Define the ending
ending((FONT*)data[F_HUGE_0]->dat,
	"Epilogue.",
		"And then it was over.",
		"The courageous LANDER",
		"Atmospheric Navigator",
		"Designed for Exploration",
		"and Research had collected",
		"information on each and",
		"every significant mass",
		"in the galaxy known as",
		"the Milky Way.  It is now",
		"time for it to return to",
		"its home, wherever that",
		"may be.........",0,
	 "....","....",0,
	 "....","....",0,
	 "....","....",0,
	 "","",0,
	 "","",0,
	 "","THE END",0,
	 0),


level(0),
buffer(0),
done(false),
starSpeed(1.0f),
bgFrame(NORMAL),
transitionX(0),
transitionY(0),
	


// Set up class variables
fireballs(256, 16, 1.0f),
nextLevelBalls(256, 16, 1.0f),
stars(256),
lander((BITMAP*)data[B_LANDER]->dat),



// Make the menu.
menu((FONT*)data[F_HUGE_0]->dat,
	"New Game",
	"Resume Game",
	"Options",
	"Credits",
	"View License",
	"Help",
	"Quit Game",
	0),

// Create the options menu
// We can't put conditionals here though, so we'll modify these values later
optionsMenu((FONT*)data[F_HUGE_0]->dat,
	"",
	"",
	"",
	"Return to Main Menu",
	0),

confirmNewGameMenu( (FONT*)data[F_HUGE_0]->dat,
	"Erase Current Game",
	"Resume Current Game",
	"Return to Main Menu",
	0)
{
	Logfile::log("+TheGame at 0x%x\n", this);

	// For some reason, calling this constructor changes the pointer to config.
	// This makes absolutely no sense to me, so I have implemented this workaround,
	// which is terrible.  If you ever find the source of the problem I would love to
	// know, because I've been pulling my hair out over this one.
	config = config_backup;
	
	
	optionsMenu.label(0, config->isSFX()?"Sound FX: on":"Sound FX: off");
	optionsMenu.label(1, config->isMusic()?"Music: on":"Music: off");
	optionsMenu.label(2, config->isFullscreen()?"Change to Windowed":"Change to Fullscreen");
	
	
	
	init();
	if(currentLevel>0) menu.setSelected(1);

	double timeElapsed = timer.timeElapsed();
	clear(screen);
	
	// initialise sound constants
	SND_CRASH = sound.registerSample((SAMPLE*)data[S_CRASH]->dat);
	SND_SCORE = sound.registerSample((SAMPLE*)data[S_SCORE]->dat);
	SND_ROCKET = sound.registerSample((SAMPLE*)data[S_ROCKET]->dat);
	

	while(!done) {
		clear(buffer);
		timeElapsed = timer.timeElapsed();
		#ifdef _DEBUG
		if(key[KEY_SPACE]) timeElapsed *= 5;
		if(key[KEY_S]) timeElapsed /= 5;
		#endif


		// A global keychecking process
		if(keypressed()) {
			if(key[KEY_ESC]) {
				switch(gameMode) {

				// Place all events which trigger the title screen to reappear here
				case INTRO:
					music.queue(1);
					music.play();
				
				case PURE_TRANSITION:
				case LEVEL_TRANSITION:
				case ENDING:
					titleScreenMode = MOVE_IN;
					changeGameMode(THEMENU);
					break;

				case CREDITS:
				case HELP:
				case LICENSE:
				case OPTIONS:
					if(gameState == TITLE_SCREEN) titleScreenMode = MOVE_IN;
					// fall through


				// Place all events which trigger a return to the menu here
				case PLAYING:
				case RESUME:
				case RESTART_GAME:
					sound.pauseAll();
					changeGameMode(THEMENU);
					break;

				// If we're already at the menu, highlight the exit (last) option
				case THEMENU:
					menu.selectLast();
					break;

				default:
					UNHANDLED_CASE_ERROR;
				}
			}


			if((key[KEY_ALT] || key[KEY_ALTGR]) && key[KEY_ENTER]) {
				config->setFullscreen(setup_screen(config->isFullscreen()?FALSE:TRUE));
				
				/*
				switch(gameMode){
				case PLAYING:
				case LEVEL_TRANSITION:
				case RESUME:
				case CREDITS:
				case ENDING:
					set_palette_range((RGB*)data[P_1 + currentLevel]->dat,0,223,TRUE);
					set_palette_range((RGB*)data[P_STD]->dat,224,255,TRUE);
					break;

				case INTRO:
					set_palette((RGB*)data[P_COMPANY_LOGO]->dat);
					break;

				default:
					set_palette_range((RGB*)data[P_TITLESCREEN]->dat,0,223,TRUE);
					set_palette_range((RGB*)data[P_STD]->dat,224,255,TRUE);
					break;
				}*/

				clear_keybuf();
			}

			if(key[KEY_F12]) screenshot();
		}







		switch(gameMode) {
		case INTRO:
			doIntro(timeElapsed,buffer);
			break;

		case PURE_TRANSITION:
			doTransition(timeElapsed,buffer);
			break;

		case THEMENU:
			doMainMenu(timeElapsed,buffer);
			break;

		case OPTIONS:
			if(gameState == TITLE_SCREEN) doTransition(timeElapsed,buffer);
			else if(gameState == NEXT_LEVEL) doNextLevel(0.0f, buffer);
			else doGame(0.0f, buffer, 0);
			doConfigMenu(timeElapsed,buffer);
			break;


		case LEVEL_TRANSITION:
			doNextLevel(timeElapsed,buffer);
			break;

		case RESUME:
			// This line is called when we select "resume" but did not
			// immediately come from a game mode.  an example is being in 
			// the game, pausing, watching the credits, and then resuming
			sound.unpauseAll();
			changeGameMode(lastPlayingGameMode);
			break;


		case RESTART_GAME:
			// This code is called when a new game is started and we are
			// not on the title screen.
			doRestartGame(timeElapsed, buffer);
			break;

		case PLAYING:
			doGame(timeElapsed,buffer,keys.getKeys());
			break;

		case CREDITS:
			if(gameState == TITLE_SCREEN) doTransition(timeElapsed,buffer);
			else if(gameState == NEXT_LEVEL) doNextLevel(0.0f, buffer);
			else doGame(0.0f, buffer, 0);
			credits.doCredits(buffer,timeElapsed);
			break;

		case LICENSE:
			if(gameState == TITLE_SCREEN) doTransition(timeElapsed,buffer);
			else if(gameState == NEXT_LEVEL) doNextLevel(0.0f, buffer);
			else doGame(0.0f, buffer, 0);
			gpl.doCredits(buffer,timeElapsed);
			break;

		case ENDING:
			stars.drawAndUpdate(buffer,timeElapsed, 0.0f, 2.0f);
			if(!ending.doCredits(buffer,timeElapsed*0.4))
				if(!credits.doCredits(buffer, timeElapsed * 0.4))
					changeGameState(TITLE_SCREEN);
			break;
			
		case HELP:
			if(gameState == TITLE_SCREEN) doTransition(timeElapsed,buffer);
			else if(gameState == NEXT_LEVEL) doNextLevel(0.0f, buffer);
			else doGame(0.0f, buffer, 0);
			doHelp(timeElapsed, buffer);
			break;

		default:
			UNHANDLED_CASE_ERROR;
		}

		// Debug text
		if(config->isFPS())
			textprintf_ex(buffer,font,0,0,COLOR_WHITE,-1,"fps: %0.0f",1/timeElapsed);
#ifdef _DEBUG
		textprintf_ex(buffer,font,0,10,COLOR_WHITE,-1,"stateTimer: %0.1f",stateTimer);
#endif

		// Take care of showing the game on the screen
		flip_pages();



		// Poll DUMB
		music.poll();
//		rest(1);
	}


	quitGame();

}

TheGame::~TheGame() {
	if(level) delete [] level;
	if(buffer) destroy_bitmap(buffer);

	Logfile::log("-TheGame at 0x%x\n", this);
}



void TheGame::doMainMenu(double timeElapsed, BITMAP *buffer) {
	static int menuSelection;

	// Draw title screen if no game is active
	if(gameState == TITLE_SCREEN) doTransition(timeElapsed,buffer);
	else if(gameState == NEXT_LEVEL) {
		if(lastPlayingGameMode == ENDING) stars.drawAndUpdate(buffer, timeElapsed, 0.0f, 2.0f);
		else doNextLevel(0.0f, buffer);
	}
	// Otherwise, show the game as background.
	// This is a hack but it is excellent. 
	else doGame(0.0000001f, buffer, 0);

	menuSelection = menu.doMenu(timeElapsed,buffer,data);
	switch(menuSelection) {
	case -1:		// No selection
		break;

	case 0:			// New game
		// TODO: If game is in progress, prompt to clear it
		// else, transition out of the menu
		if(gameState == TITLE_SCREEN) {
			titleScreenMode = MOVE_OUT;
			transitionAction = PLAYING;
			changeGameMode(PURE_TRANSITION);
		}
		else {
			stateTimer = 0.0f;
			changeGameMode(RESTART_GAME);
		}
		music.queue(2, true);
		break;

	case 1:			// Resume game
		if(gameState == TITLE_SCREEN) {
			titleScreenMode = MOVE_OUT;
			transitionAction = PLAYING;
			changeGameMode(PURE_TRANSITION);
		}
		continueGame();
		break;

	case 2:			// Options
		changeGameMode(OPTIONS);
		break;

	case 3:			// Credits
		if(gameState == TITLE_SCREEN) titleScreenMode = MOVE_OUT;
		transitionAction = CREDITS;
		changeGameMode(CREDITS);
		credits.reset();
		break;
		
	case 4:			// View License
		if(gameState == TITLE_SCREEN) titleScreenMode = MOVE_OUT;
		transitionAction = LICENSE;
		changeGameMode(LICENSE);
		gpl.reset();
		break;

	case 5:			// Help
		if(gameState == TITLE_SCREEN) titleScreenMode = MOVE_OUT;
		transitionAction = HELP;
		changeGameMode(HELP);
		break;

	case 6:			// Quit
		done = true;
		break;

	default:
		UNHANDLED_CASE_ERROR;
	}
}


void TheGame::doConfigMenu(double timeElapsed, BITMAP *buffer) {
	static int opt;

	//doTransition(timeElapsed,buffer);
	opt = optionsMenu.doMenu(timeElapsed,buffer,data);
	switch(opt) {
	case -1:// no selection
		break;

	case 0: // toggle sfx
		config->toggleSFX();
		optionsMenu.label(0, (char*)(config->isSFX()?"Sound FX: on":"Sound FX: off"));
		break;


	case 1: // toggle music
		config->toggleMusic();
		optionsMenu.label(1, (char*)(config->isMusic()?"Music: on":"Music: off"));

		if(!config->isMusic()) {
			music.stop();
		}
		else {
			music.play();
		}
		break;


	case 2: // toggle fullscreen
		config->toggleFullscreen();
		optionsMenu.label(2, (char*)(config->isFullscreen()?"Change to Windowed":"Change to Fullscreen"));
		break;


	case 3: // return to main menu
		changeGameMode(THEMENU);
		break;

	default:
		UNHANDLED_CASE_ERROR;

	}
}


void TheGame::init() {
	log.log("Starting game.\n", 0);
//	text_mode(-1);
	clear_keybuf();

	/* -- For now, page flipping is disabled.
		Why?  Because I'm lazy and trying to finish
		the polish on the game without breaking too
		much.  After rewriting the entire game, I
		think it's about time for a rewrite.  Yikes this
		code is ugly!  Not here so much, but 
		everywhere else.
	page1 = create_video_bitmap(GAME_W,GAME_H);
	page2 = create_video_bitmap(GAME_W,GAME_H);
	if(page1 && page2) {
		flipping = true;
		buffer = page1;
	}
	else {*/
		flipping = false;
		buffer = create_bitmap(GAME_W,GAME_H);
	//}

	// For some reason P_COMPANY_LOGO has the wrong black
	RGB zero; zero.r = zero.g = zero.b = 0;
	set_color(0,&zero);
	music.queue(0, true);

	// Prepare us for the intro to be displayed
	set_palette_range((RGB*)data[P_COMPANY_LOGO]->dat,1,239,TRUE);

	// For some reason P_COMPANY_LOGO has junk in these entries
	set_palette_range((RGB*)data[P_STD]->dat,240,255,TRUE);
	clear(buffer);

	LANDER_W = ((BITMAP*)data[B_LANDER]->dat)->w;
	LANDER_H = ((BITMAP*)data[B_LANDER]->dat)->h;
	
	
	PLAY_ROCKET = FALSE;
	rocket_freq = 1250;

	

	// Load all the miniscule level data
	// The reason I load all the data at the beginning is because it
	// jitters while loading in between levels, making the animation
	// not smooth.
	level = new Level[9];
	for(int i=0; i<9; i++) {
		level[i].load(i);
		level[i].setField((BITMAP*)data[B_BG_1 + i]->dat);
	}

	set_config_file("lander.ini");

	currentLevel = get_config_int("game","level",0);
	highScore = get_config_int("game","hiscore",0);
	scoreToBeat = get_config_int("game","scoreToBeat",8000);
	lander.setFuel(get_config_float("game","fuel",0.0f));
	score = get_config_int("game","score",0);

	LEVEL_W = ((BITMAP*)data[B_BG_1]->dat)->w;
	LEVEL_H = ((BITMAP*)data[B_BG_1]->dat)->h;


	titleScreenMode = MOVE_IN;
	//changeGameState(ACTION);


}





void TheGame::newGame() {
	//if(level) delete level;
	//level = new Level(0,(BITMAP*)data[B_BG_1]->dat);
	currentLevel = 0;
	setPalette();
	restartLevel();
	score = 0;
	scoreToBeat = 8000;
	lander.setFuel(1.0f);
	
	transitionX = 0.0f;
	transitionY = GAME_H*3/2;

	changeGameMode(PLAYING);
	changeGameState(ACTION);

	// Load the music
	//music.play();
}


void TheGame::continueGame() {
	if(gameState == TITLE_SCREEN) {
		transitionAction = RESUME;
	//	titleScreenMode = MOVE_OUT;
	//	changeGameMode(PURE_TRANSITION);
		music.queue(currentLevel+2, true);
		return;
	}
	setPalette();


	switch(oldGameMode) {
	case PLAYING:
	case RESUME:
	case ENDING:
	case LEVEL_TRANSITION:
		changeGameMode(oldGameMode);
		break;

	case CREDITS:
	case PURE_TRANSITION:
	case THEMENU:
	case INTRO:
	case HELP:
	case OPTIONS:
		changeGameMode(RESUME);
		break;

	default:
		UNHANDLED_CASE_ERROR;
	}
}


// TODO: make me play nice with page flipping!
void TheGame::quitGame() {
	float pos=0;
	BITMAP *temp = create_bitmap(GAME_W, GAME_H);

	while(pos < GAME_H/2) {
		double dt = timer.timeElapsed();
		
		// Keep the music playing, but fade it out
		music.poll();
		int vol = (int)(config->getMusicVol() * 255 * (1 - 2*pos/GAME_H));
		set_volume(vol, vol);

		
		clear(temp);
		acquire_bitmap(buffer);
		stretch_blit(buffer, temp, 0, 0, GAME_W, GAME_H, 
					 (int)pos, (int)pos, GAME_W - (int)(2*pos), GAME_H - (int)(2*pos));
		blit(temp, screen, 0, 0, (SCREEN_W-GAME_W)/2, (SCREEN_H-GAME_H)/2, GAME_W, GAME_H);
		release_bitmap(buffer);

		pos += dt * 200;
	}

	if(gameState == NEXT_LEVEL) currentLevel++;
	else if(gameState == LAND && targetScore >= scoreToBeat) {
		currentLevel++;
		score = targetScore;
		if(highScore < score) highScore = score;
		scoreToBeat += 8000;
		if(score > scoreToBeat) scoreToBeat = (int)score + 100;
	}

	set_config_file("lander.ini");
	set_config_int("game","score",(int)score);
	set_config_float("game","fuel",lander.getFuel());
	set_config_int("game","hiscore",highScore);
	set_config_int("game","level",currentLevel);
	set_config_int("game","scoreToBeat",scoreToBeat);
	flush_config_file();
	
	Logfile::log("Game status saved.\n");
	
	destroy_bitmap(temp);
}


void TheGame::doIntro(double timeElapsed, struct BITMAP *buffer) {
	static float w=0.0f,h=0.0f, y=0.0f;
	static BITMAP *bmp = (BITMAP*)data[B_COMPANY_LOGO]->dat;
	static float ticks1 = 0.0f, ticks2 = 0.0f;

	
	// zoom in on logo
	if(w < GAME_W)
	{
		stretch_blit(bmp,buffer,0,0,GAME_W,GAME_H, (int)(GAME_W/2 - w/2), (int)(GAME_H/2 - h/2), (int)w, (int)h); 
		w += GAME_W/2.25f * timeElapsed;
		h += GAME_H/2.25f * timeElapsed;
	}

	// wait 3/4 second
	else if((ticks1 += timeElapsed) < 0.75f) {
		blit(bmp,buffer,0,0,0,0,GAME_W,GAME_H);
	}

	// scroll downward
	else if(y < GAME_H)
	{
		rectfill(buffer,0,0,GAME_W,(int)y,0);
		stars.drawAndUpdate(buffer,timeElapsed,0,1.0f);
		blit(bmp,buffer,0,0,0,(int)y,GAME_W,GAME_H-(int)y+1);
		y += 300.0 * timeElapsed;
	}

	// Scroll stars for a second
	else if((ticks2 += timeElapsed) < 0.75f) {
		clear(buffer);
		stars.drawAndUpdate(buffer,timeElapsed,0,1.0f);
	}

	else {
		changeGameMode(THEMENU);
		music.queue(1);
		music.play();
	}

	if(keypressed()) {
		changeGameMode(THEMENU);
		music.queue(1);
		music.play();
		clear_keybuf();
	}
}

void TheGame::doTransition(double timeElapsed, struct BITMAP *buffer) {
	const static float TITLE_Y_START = -128.0f;
	static float titleY = TITLE_Y_START;
	static float landerX = -50.0f, landerY = 495.0f;

	switch(titleScreenMode) {
	case MOVE_IN:
		set_palette_range((RGB*)data[P_TITLESCREEN]->dat,0,223,TRUE);
		set_palette_range((RGB*)data[P_STD]->dat,224,255,TRUE);
		titleY += 25.0f * timeElapsed;
		landerX += 20.0f * timeElapsed;
		landerY -= 50.0f * timeElapsed;
		starSpeed = -titleY/128.0f;
		if(titleY >= 0.0f) {
			titleY = starSpeed = 0.0f;
			titleScreenMode = STOP;
		}
		break;

	case MOVE_OUT:
		titleY -= 25.0f * timeElapsed;
		landerX -= 20.0f * timeElapsed;
		landerY += 50.0f * timeElapsed;
		starSpeed = -titleY/128.0f;
		if(titleY <= TITLE_Y_START) {
			starSpeed = 1.0f;
			titleY = TITLE_Y_START;
			titleScreenMode = STOP;
			switch(transitionAction) {
			case HELP:
				changeGameMode(HELP);
				break;
				
			case CREDITS:
				changeGameMode(CREDITS);
				break;
				
			case LICENSE:
				changeGameMode(LICENSE);
				break;
				
			case PLAYING:
				newGame();
				break;
				
			case RESUME:
				changeGameMode(PLAYING);
				changeGameState(ACTION);
				continueGame();
				break;
				
			default:
				//allegro_message("Unhandled case in transitionAction assignment.");
				UNHANDLED_CASE_ERROR;
			}
		}
		break;

	case IN_STATE:
		set_palette_range((RGB*)data[P_TITLESCREEN]->dat,0,223,TRUE);
		set_palette_range((RGB*)data[P_STD]->dat,224,255,TRUE);
		titleY = 0.0f;
		starSpeed = 0.0f;
		titleScreenMode = STOP;
		landerX = 53;
		landerY = 238;
		clear_keybuf();
		break;

	case OUT_STATE:
		landerX = -50.0f; 
		landerY = 495.0f;
		titleY = TITLE_Y_START;
		starSpeed = 1.0f;
		titleScreenMode = STOP;
		break;

	case STOP:
		break;

	default:
		UNHANDLED_CASE_ERROR;
	}


	stars.drawAndUpdate(buffer,timeElapsed,0,starSpeed);
	draw_sprite(buffer, (BITMAP*)data[B_TITLESCREEN]->dat, 0, (int)titleY);
	draw_sprite(buffer, (BITMAP*)data[B_TITLE_LANDER]->dat, (int)landerX, (int)landerY);
}



void TheGame::doRestartGame(double timeElapsed, BITMAP *buffer) {
	if(stateTimer == 0.0f) {
		transitionY = 0.0f;
	}

	stateTimer += timeElapsed;
	stars.drawAndUpdate(buffer, timeElapsed, 0.0f, transitionY / GAME_H);
	level[currentLevel].draw(buffer, zoom_factor, screenX, screenY, (int)transitionX, (int)transitionY);
	lander.draw(buffer, zoom_factor, (int)screenX, (int)screenY, (int)transitionX, (int)transitionY);

	
	// scroll the game field out
	if(transitionY < GAME_H*1.2) // && state == LEVEL_OUT)
		transitionY += GAME_H * timeElapsed;

	else {
		newGame();
	}

}


void TheGame::doNextLevel(double timeElapsed, BITMAP *buffer) {
	static const int LANDER_ADV_W = ((BITMAP*)data[B_ADVANCE]->dat)->w;
	static const int LANDER_ADV_H = ((BITMAP*)data[B_ADVANCE]->dat)->h;
	static const int LANDERX = (GAME_W - LANDER_ADV_W)/2;

	static float nextLevelTextTargetY = GAME_H/10;
	static float nextLevelTextStartY = -text_height((FONT*)data[F_HUGE_0]->dat);
	static float nextLevelTextY;


	if(stateTimer == 0.0f) {
		nextLevelTextY = nextLevelTextStartY;
	}
	
	stateTimer += timeElapsed;
	stars.drawAndUpdate(buffer, timeElapsed, 0.0f, transitionY / GAME_H);
	drawInterface(buffer);
	level[currentLevel].draw(buffer, zoom_factor, screenX, screenY, (int)transitionX, (int)transitionY);
	lander.draw(buffer, zoom_factor, (int)screenX, (int)screenY, (int)transitionX, (int)transitionY);
	
	
	lander.setVelocity(0.0f,0.0f);

	// Scroll the game field out
	if(transitionY < GAME_H*2) {
		transitionY += GAME_H * timeElapsed;
		
	}

	// handle end of game condition
	else if(currentLevel == 8) {
		// if we just completed Pluto (level 8) then 
		// show the end game stuff
		changeGameMode(ENDING);
		//changeGameState(NEXT_LEVEL);
		music.queue(11, TRUE);		
		currentLevel=0;
		lander.setFuel(1.0f);
		score=0.0f;
		scoreToBeat = 8000;
	}

	// 
	else if(stateTimer < 14.0f) {
		if(gameMode == LEVEL_TRANSITION) sound.play(SND_ROCKET, 1.0f, 0.5f, 1.0f, TRUE);
		else sound.stop(SND_ROCKET);

		transitionY = GAME_H*2 + 0.1;
		nextLevelBalls.add(25, GAME_W/2 - 20 + (int)(rand()%81 / 2.0f), 
				(int)(landerAdvY + LANDER_ADV_H - 24), 90.0f,20, timeElapsed);
		nextLevelBalls.drawAndUpdate(buffer,1,0,0,timeElapsed);
// these two lines are for when using ParticleSource objects
//		nextLevelBalls.add(25,GAME_W/2, landerAdvY + LANDER_ADV_H - 24, 270, timeElapsed);
//		nextLevelBalls.drawAndUpdate(buffer, 1, 0, 0, timeElapsed);
		
		draw_sprite(buffer, (BITMAP*)data[B_ADVANCE]->dat, LANDERX, (int)landerAdvY);
		landerAdvY -= timeElapsed * GAME_H/8;


		// Draw the text saying "Now approaching...."
		if(landerAdvY >= GAME_H*9/10 && nextLevelTextY < nextLevelTextTargetY) {
			nextLevelTextY += nextLevelTextTargetY*timeElapsed*4;
		}
		else if(nextLevelTextY > nextLevelTextTargetY && landerAdvY > -16.0f) {
			nextLevelTextY = nextLevelTextTargetY;
		}

		if(landerAdvY <= -16.0f && nextLevelTextY != nextLevelTextStartY) {
			nextLevelTextY += nextLevelTextTargetY*timeElapsed * 4;
		}
		else if(landerAdvY <= -36.0f) {
			nextLevelTextY = nextLevelTextStartY;
		}
		textprintf_centre_ex(buffer, (FONT*)data[F_HUGE_0]->dat, GAME_W/2, (int)nextLevelTextY,
			COLOR_RED, -1, "NOW APPROACHING %s", level[currentLevel+1].getName());

		// Once we're sufficiently offscreen we end the transition
		if(landerAdvY < -GAME_H/2) stateTimer = 15.0f;
	}


	// Kill the transition, start the next level
	else {
		sound.stop(SND_ROCKET);
		
		landerAdvY = GAME_H;
		transitionY = GAME_H*2;
		changeGameMode(PLAYING);

		currentLevel++;
		setPalette();
		restartLevel();
	}
}


void TheGame::drawPlayfield(BITMAP *buffer) {
	// Draw stars behind level
	stars.draw(buffer);

	// Draw the background
	level[currentLevel].draw(buffer, zoom_factor, screenX, screenY, (int)transitionX, (int)transitionY);

	// Draw the fireballs
//	fireballs.draw(buffer,zoom_factor,screenX,screenY);
	fireballs.draw(buffer, zoom_factor, screenX, screenY);

	// Draw the lander
	if(gameState != GAME_OVER && gameState != DEAD)
		lander.draw(buffer, zoom_factor, (int)screenX, (int)screenY, (int)transitionX, (int)transitionY);


#ifdef _DEBUG
	Level *l = &level[currentLevel];
	// Draw the zoom areas
	rect(buffer, (int)((l->zoom2x + transitionX - screenX)*zoom_factor),
			 (int)((l->zoom2y + transitionY - screenY)*zoom_factor),
			 (int)((l->zoom2x + LEVEL_W/4 + transitionX - screenX)*zoom_factor),
			 (int)((l->zoom2y + LEVEL_H/4 + transitionY - screenY)*zoom_factor),
			 COLOR_WHITE);

	rect(buffer, (int)((l->zoom5x + transitionX - screenX)*zoom_factor),
			 (int)((l->zoom5y + transitionY - screenY)*zoom_factor),
			 (int)((l->zoom5x + LEVEL_W/4 + transitionX - screenX)*zoom_factor),
			 (int)((l->zoom5y + LEVEL_H/4 + transitionY - screenY)*zoom_factor),
			 COLOR_WHITE);

	rect(buffer, (int)((l->zoom10x + transitionX - screenX)*zoom_factor),
			 (int)((l->zoom10y + transitionY - screenY)*zoom_factor),
			 (int)((l->zoom10x + LEVEL_W/4 + transitionX - screenX)*zoom_factor),
			 (int)((l->zoom10y + LEVEL_H/4 + transitionY - screenY)*zoom_factor),
			 COLOR_WHITE);


	// Draw landing pads
	hline(buffer, (int)((l->pad2x1 + transitionX - screenX)*zoom_factor),
			  (int)((l->pad2y + transitionY - screenY)*zoom_factor),
			  (int)((l->pad2x2 + transitionX - screenX)*zoom_factor),
			  COLOR_WHITE);

	hline(buffer, (int)((l->pad5x1 + transitionX - screenX)*zoom_factor),
			  (int)((l->pad5y + transitionY - screenY)*zoom_factor),
			  (int)((l->pad5x2 + transitionX - screenX)*zoom_factor),
			  COLOR_WHITE);

	hline(buffer, (int)((l->pad10x1 + transitionX - screenX)*zoom_factor),
			  (int)((l->pad10y + transitionY - screenY)*zoom_factor),
			  (int)((l->pad10x2 + transitionX - screenX)*zoom_factor),
			  COLOR_WHITE);

#endif


}


void TheGame::drawInterface(BITMAP *buffer) {

	// Black out everything behind us
	// Technically, this is a poor idea,
	// but it gets the job done.
	rectfill(buffer, (int)transitionX, (int)(GAME_H - 17 + transitionY), GAME_W, GAME_H, COLOR_BLACK);
	rectfill(buffer, (int)(GAME_W - 9 + transitionX), (int)transitionY, GAME_W, GAME_H, COLOR_BLACK);


	// Score
	textprintf_ex(buffer, font, 0 + (int)transitionX, GAME_H-16 + (int)transitionY, 
			COLOR_SCORE, -1, "SCORE: %.0f / %d", score, scoreToBeat);
	textprintf_ex(buffer, font, GAME_W/2 + (int)transitionX, GAME_H-16 + (int)transitionY, 
			COLOR_SCORE, -1, "HISCORE: %d", highScore);

	// FUEL
	textout(buffer, font, "FUEL:", 
		0 + (int)transitionX, 
		GAME_H-8 + (int)transitionY, 
		COLOR_FUEL_TEXT);

	if(lander.getFuel()>0) 
		rectfill(buffer, 
			40 + (int)transitionX, GAME_H-8 + (int)transitionY, 
			(int)(40 + (GAME_W-40) * lander.getFuel() + transitionX), GAME_H + (int)transitionY, 
			COLOR_FUEL_LEFT);
	else
		textprintf_centre_ex(buffer, (FONT*)data[F_HUGE_0]->dat,
			GAME_W/2, 50, COLOR_BLUE, -1, "OUT OF FUEL");

	textprintf_ex(buffer, font, 41 + (int)transitionX, GAME_H - 8 + (int)transitionY, 65536, -1,  "%.0f%%", lander.getFuel() * 100.0f);

	// M/S GAUGE
	rectfill(buffer, 
		GAME_W - 8 + (int)transitionX, 0 + (int)transitionY, 
		GAME_W + (int)transitionX, GAME_H - 77 + (int)transitionY, 
		COLOR_VELOCITY_BAR);

	rectfill(buffer, 
		GAME_W - 8 + (int)transitionX, (int)(GAME_H/2 - 4*zoom_factor + transitionY), 
		GAME_W + (int)transitionX, (int)(GAME_H/2 + 4*zoom_factor + transitionY), 
		COLOR_VELOCITY_ZONE);

	hline(buffer, 
		GAME_W - 8 + (int)transitionX, 
		(int)((GAME_H/2 - 4*zoom_factor) + lander.getVY()*zoom_factor * 250 + transitionY - 1), 
		GAME_W + (int)transitionX, COLOR_BLACK);
}


void TheGame::doGame(double timeElapsed, BITMAP *buffer, int keys) {
	// All the static variables we're going to want to use
	// Perhaps move these to the class definition?

	static int padMultiplier, landingScore;



	// All non-static variables
	float landerX = lander.getX();
	float landerY = lander.getY();
	
	float lx = (lander.getX() - screenX) * zoom_factor + LANDER_W * zoom_factor / 2.0f;
	int pan = (int)(127 - (0.5f - (lx/LEVEL_W)) * 127);



	

	// only for testing!
#ifdef _DEBUG
		if(key[KEY_F1]) lander.setPosition(250,25);
		else if(key[KEY_F2]) lander.setPosition(15,15);
		else if(key[KEY_F3]) score += 16000*timeElapsed;
		else if(key[KEY_F4]) lander.setFuel(1.0f);
		else if(key[KEY_F5]) restartLevel();
		else if(key[KEY_F6]) changeGameState(LAND);
#endif
		
	// Determine if we're zoomed in or not
	Level *clevel = &level[currentLevel];
	if(lander.inZoomRange(10, clevel)) bgFrame = ZOOM10X;
	else if(lander.inZoomRange(5, clevel)) bgFrame = ZOOM5X;
	else if(lander.inZoomRange(2, clevel)) bgFrame = ZOOM2X;
	else bgFrame = NORMAL;


	// Set the proper variables if we're zoomed or not
	float finalL, finalT, finalR, finalB, dR, dB;
	switch(bgFrame) {
	case NORMAL:
		screenX = screenY = 0;
		edgeR = LEVEL_W;
		edgeB = LEVEL_H;
		zoom_factor = 1.0f;
		break;

	case ZOOM2X:
		// We must move finalX pixels in 1 second.
		finalL = clevel->zoom2x;
		finalT = clevel->zoom2y;
		finalR = finalL + ZOOM_W;
		finalB = finalT + ZOOM_H;
		dR = LEVEL_W - finalR;
		dB = LEVEL_H - finalB;

		screenX += finalL * timeElapsed;
		screenY += finalT * timeElapsed;
		edgeR -= dR * timeElapsed;
		edgeB -= dR * timeElapsed;
		zoom_factor = LEVEL_W / (edgeR - screenX);

		if(zoom_factor > 4.0f) {
			zoom_factor = 4.0f;
			screenX = clevel->zoom2x;
			screenY = clevel->zoom2y;
			edgeR = finalR;
			edgeB = finalB;
		}
		break;

	case ZOOM5X:
		// We must move finalX pixels in 1 second.
		finalL = clevel->zoom5x;
		finalT = clevel->zoom5y;
		finalR = finalL + ZOOM_W;
		finalB = finalT + ZOOM_H;
		dR = LEVEL_W - finalR;
		dB = LEVEL_H - finalB;

		screenX += finalL * timeElapsed;
		screenY += finalT * timeElapsed;
		edgeR -= dR * timeElapsed;
		edgeB -= dR * timeElapsed;
		zoom_factor = LEVEL_W / (edgeR - screenX);

		if(zoom_factor > 4.0f) {
			zoom_factor = 4.0f;
			screenX = clevel->zoom5x;
			screenY = clevel->zoom5y;
			edgeR = finalR;
			edgeB = finalB;
		}
		break;

	case ZOOM10X:
		// We must move finalX pixels in 1 second.
		finalL = clevel->zoom10x;
		finalT = clevel->zoom10y;
		finalR = finalL + ZOOM_W;
		finalB = finalT + ZOOM_H;
		dR = LEVEL_W - finalR;
		dB = LEVEL_H - finalB;

		screenX += finalL * timeElapsed;
		screenY += finalT * timeElapsed;
		edgeR -= dR * timeElapsed;
		edgeB -= dR * timeElapsed;
		zoom_factor = LEVEL_W / (edgeR - screenX);

		if(zoom_factor > 4.0f) {
			zoom_factor = 4.0f;
			screenX = clevel->zoom10x;
			screenY = clevel->zoom10y;
			edgeR = finalR;
			edgeB = finalB;
		}
		break;

	default:
		UNHANDLED_CASE_ERROR;
	}


	// Draw the new frame
	drawPlayfield(buffer);

	// Update various elements
	fireballs.update(timeElapsed);
	if(gameState != GAME_OVER) lander.update(timeElapsed);


	// See if we're out of sky
	if(gameState == ACTION && lander.isOutOfSky()) {
		changeGameState(OUT_OF_SKY);

		// Reposition the lander so we're still in out of sky mode, but
		// will not hit this conditional again.
		//
		// Instead what happens is it waits 2.5 seconds then restarts the level
		lander.setPosition(-25,-25);
	}



	// See if we've landed on a landing pad
	if(lander.getVY() < 0.0348f && gameState != LAND) {
		if(lander.isOnPad(2, clevel)) {
			changeGameState(LAND);
			padMultiplier = 2;
		}
		else if(lander.isOnPad(5, clevel)) {
			changeGameState(LAND);
			padMultiplier = 5;
		}
		else if(lander.isOnPad(10, clevel)) {
			changeGameState(LAND);
			padMultiplier = 10;
		}
	}



	// Different game states require different work:

	switch(gameState) {
	case ACTION:
		
		// First make sure the game has slid into full view
		if(transitionY > 0) {
			transitionY -= GAME_H/2 * timeElapsed;
			stars.update(timeElapsed,0.0f,transitionY / GAME_H);
			restartLevel();
			break;
		}
		else if(transitionY < 0) transitionY = 0;



		if(lander.checkCollision(currentLevel)) {
			changeGameState(DEAD);
			break;
		}

		if(lander.hasFuel()) {
			if(PLAY_ROCKET) 
				sound.play(SND_ROCKET, 1.0f, pan / 255.0f, rocket_freq / 1000.0f, TRUE);
			else sound.stop(SND_ROCKET);
			rocket_freq = 1250;
			
			// Draw the flames and update status based on input

			// Thrusters
			if(keys & K_RIGHT) thrustRight(1.0f, timeElapsed);
			if(keys & K_LEFT) thrustLeft(1.0f, timeElapsed);
			
			if(keys & K_MAX) thrustUp(1.0f, timeElapsed);
			else if(keys & K_MED) thrustUp(0.5f, timeElapsed);
			else if(keys & K_MIN) thrustUp(0.3f, timeElapsed);
		}
		
		if(keys == 0) PLAY_ROCKET = FALSE;

		break;

	case DEAD:
		if(stateTimer <= 0.01f) {
			sound.stop(SND_ROCKET);
			sound.stop(SND_CRASH);
			sound.play(SND_CRASH, 1.0f, pan / 255.0f, 1.0f, FALSE);
		}
		else if(stateTimer < 1.0f) {
			fireballs.add(10, (int)landerX + rand()%LANDER_W, (int)landerY + rand()%LANDER_H,
				rand()%1080 / 3.0f, 2 + rand()%3, timeElapsed);
		}
		else if(stateTimer > 2.5f) {
			lander.changeFuel(-0.075);
			if(lander.getFuel() > 0.0f) restartLevel();
			else changeGameState(GAME_OVER);
		}
		break;

	case OUT_OF_SKY:
		sound.stop(SND_ROCKET);
		textout_centre(buffer,(FONT*)data[F_HUGE_0]->dat,"OUT OF SKY",GAME_W/2,25,COLOR_BLUE);
		if(stateTimer > 1.0f) {
			changeGameState(ACTION);
			restartLevel();
		}
		break;

	case LAND:
		sound.stop(SND_ROCKET);
		PLAY_ROCKET = FALSE;
		if(stateTimer == 0.0f) {
			landingScore = (int)ceil(fabs(lander.getVY() - 0.0348f)*28735);
			targetScore = (int)(score + padMultiplier * landingScore);
			lander.setPosition(lander.getX(), lander.getY()-0.1f);
		}
		lander.setVelocity(0.0f,0.0f);

		
		if(score < targetScore) {
			if(gameMode == PLAYING) sound.play(SND_SCORE, 0.5f, 0.5f, 1.0f, TRUE);
			score += 900.0f * timeElapsed;
			lander.changeFuel(0.1f * timeElapsed);
			if(lander.getFuel() > 1.0f) lander.setFuel(1.0f);

			if(score > targetScore) {
				score = targetScore;
				stateTimer = 0.0f;
				sound.stop(SND_SCORE);
			}
			if(score > highScore) highScore = (int)score;
		}
		else if(score == targetScore) {
			if(stateTimer >= 1.5f) {
				if(score < scoreToBeat) restartLevel();
				else {
					changeGameState(NEXT_LEVEL);
					changeGameMode(LEVEL_TRANSITION);
					scoreToBeat += 8000;
					if(score > scoreToBeat) scoreToBeat = (int)score+100;
					landerAdvY = GAME_H;
					stateTimer = 0.0f;
					nextLevelBalls.reset();
					music.queue(currentLevel+3);
				}
			}
		}

		if(score >= scoreToBeat) {
			textprintf_centre_ex(buffer, (FONT*)data[F_HUGE_0]->dat,
				GAME_W/2, GAME_H/2 - 90, COLOR_BLUE, -1, "GOOD JOB!");
		}

		textprintf_ex(buffer,font,0,GAME_H - 16, COLOR_SCORE, -1, 
			"SCORE: %0.0f / %d (%d)",score, scoreToBeat, targetScore);
		
		textprintf_centre_ex(buffer,(FONT*)data[F_HUGE_0]->dat,
			GAME_W/2,
			GAME_H/2-40,
			COLOR_BLUE, -1,
			"LAND SUCCESSFUL");
		textprintf_centre_ex(buffer,(FONT*)data[F_HUGE_0]->dat,
			GAME_W/2,
			GAME_H/2,
			COLOR_BLUE, -1, 
			" %d x %d = %d! ",landingScore,padMultiplier,padMultiplier*landingScore);

		break;


	case GAME_OVER:
		textprintf_centre_ex(buffer, (FONT*)data[F_HUGE_0]->dat,
			GAME_W/2, 75, COLOR_BLUE, -1, "GAME OVER");
		break;

	case NEXT_LEVEL:
		// this is now handled by changing the gameMode to LEVEL_TRANSITION
		break;

	default:
		UNHANDLED_CASE_ERROR;
	}



	stateTimer += timeElapsed;


		
	// Draw the interface
	drawInterface(buffer);







	// Mouse hack
	// Use this with a gyro mouse, the game is pretty neat that way!
/*	static const int MOUSE_LEFT_BOUND = GAME_W*2/5;
	static const int MOUSE_RIGHT_BOUND= GAME_W*3/5;
	static const int MOUSE_UP_BOUND   = GAME_H*9/10;
	
	// Draw range for left and right
	vline(buffer,MOUSE_LEFT_BOUND,0,GAME_H, makecol(255,255,255));
	vline(buffer,MOUSE_RIGHT_BOUND,0,GAME_H, makecol(255,255,255));

	// Draw range for up and down
	hline(buffer,0,MOUSE_UP_BOUND, GAME_W, makecol(255,255,255));

	// Draw the mouse pointer
	circle(buffer,mouse_x,mouse_y,5,0);
	vline(buffer, mouse_x,mouse_y-5,mouse_y+5,0);
	hline(buffer, mouse_x-5, mouse_y, mouse_x+5, 0);


	// Left button resets the pointer
	if(mouse_b & 1) position_mouse(GAME_W/2,GAME_H);

	// Right button fires all thrusters for swift upward motion
	if(mouse_b & 2) {
		// todo: me!
	}


	// Thrust based on mouse position
	if(mouse_x < MOUSE_LEFT_BOUND) {
		float multiplier = 1 - (float)mouse_x / MOUSE_LEFT_BOUND;
		textprintf(buffer,font,GAME_W-32,0,makecol(0,0,0),"%f",multiplier);

		fireballs.add(landerX, landerY + LANDER_H/2, 160, 40*multiplier, 5*multiplier, 1000*multiplier* timeElapsed);
		lander->changeVelocity(0.12f * timeElapsed * multiplier, -0.08f * timeElapsed * multiplier);
		lander->changeFuel(-0.02f * timeElapsed * multiplier);
	}
	else if(mouse_x > MOUSE_RIGHT_BOUND) {
		float multiplier = (float)(mouse_x - MOUSE_RIGHT_BOUND) / (GAME_W - MOUSE_RIGHT_BOUND);
		textprintf(buffer,font,GAME_W-32,0,makecol(0,0,0),"%f",multiplier);

		fireballs.add(landerX + LANDER_W, landerY + LANDER_H/2, 30, 40*multiplier, 5*multiplier, 1000*multiplier* timeElapsed);
		lander->changeVelocity(-0.12f * timeElapsed * multiplier, -0.08f * timeElapsed * multiplier);
		lander->changeFuel(-0.02f * timeElapsed * multiplier);
	}

	if(mouse_y < MOUSE_UP_BOUND) {
		float multiplier = 1 - (float)mouse_y / MOUSE_UP_BOUND;
		textprintf(buffer,font,GAME_W-32,8,makecol(0,0,0),"%f",multiplier);

		fireballs.add(landerX + LANDER_W/2, landerY + LANDER_H, 90, 40*multiplier, 5*multiplier, 1000*multiplier * timeElapsed);
		lander->changeVelocity(0.0f, -0.2f * timeElapsed * multiplier);
		lander->changeFuel(-0.02f * timeElapsed * multiplier);
	}
*/
}


void TheGame::restartLevel() {
	lander.setPosition(13,3);			// For some reason this is what I chose
	lander.setVelocity(0.1f,0.0f);
	zoom_factor = 1.0f;
	screenX = screenY = 0.0f;
	changeGameState(ACTION);
}


void TheGame::setPalette() {
	set_palette_range((RGB*)data[P_1 + currentLevel]->dat,0,223,TRUE);
	set_palette_range((RGB*)data[P_STD]->dat,224,255,TRUE);
}


void TheGame::changeGameState(gameStateEnum e) {
	stateTimer = 0.0f;
	gameState = e;
}




// Power should be in the range of 0 to 1, for off to full
void TheGame::thrustLeft(float power, float timeElapsed) {
	thrust(lander.getX(), lander.getY() + LANDER_H/2 + 3, 160, 50 * power, timeElapsed);
}

void TheGame::thrustRight(float power, float timeElapsed) {
	thrust(lander.getX() + LANDER_W, lander.getY() + LANDER_H/2 + 3, 30, 50 * power, timeElapsed);
}

void TheGame::thrustUp(float power, float timeElapsed) {
	thrust(lander.getX() + LANDER_W/2 + 1, lander.getY() + LANDER_H - 2, 90, 50 * power, timeElapsed);
}

void TheGame::thrust(float x, float y, float angle, float power, float timeElapsed) {
	fireballs.add(power/5.0f, (int)x, (int)y, angle, 4, timeElapsed);
	lander.changeVelocity(-cos(angle * M_PI / 180.0f) * power * 0.004 * timeElapsed,
				-sin(angle * M_PI / 180.0f) * power * 0.004 * timeElapsed);
	lander.changeFuel(-0.0004f * timeElapsed * power);

	rocket_freq -= (int)(5 * power);
	PLAY_ROCKET = TRUE;
}



void TheGame::screenshot() {
	// Find the first filename not already in use
	char fn[512]="lander000.bmp";
	int i;
	for(i=0;exists(fn);i++) {
		sprintf(fn,"lander%03d.bmp",i);
	}

	// Save the screen's contents
	PALETTE pal;
	BITMAP *bmp = create_sub_bitmap(screen,0,0,GAME_W,GAME_H);

	get_palette(pal);
	save_bitmap(fn, bmp, pal);
	destroy_bitmap(bmp);
}



void TheGame::changeGameMode(gameModeEnum gme) {
	switch(gameMode) {
	case LEVEL_TRANSITION:
	case PLAYING:
	case RESUME:
	case ENDING:
		lastPlayingGameMode = gameMode;
		break;

	case THEMENU:
		//music.stop();
		//music.queue(1);
	case INTRO:
	case RESTART_GAME:
	case PURE_TRANSITION:
	case OPTIONS:
	case HELP:
	case CREDITS:
	case LICENSE:
		// Do nothing special
		break;

	default:
		UNHANDLED_CASE_ERROR;
	}
	oldGameMode = gameMode;
	gameMode = gme;
}


void TheGame::flip_pages() {
	vsync();
	/*if(flipping) {
		show_video_bitmap(buffer);
		if(buffer == page1) buffer = page2;
		else buffer = page1;
	}
	else */blit(buffer, screen, 0, 0, (SCREEN_W-GAME_W)/2, (SCREEN_H-GAME_H)/2, GAME_W, GAME_H);
	rest(1);
}

void TheGame::doHelp(double timeElapsed, BITMAP *buffer) {
	static FONT *f = (FONT*)data[F_HUGE_0]->dat;
	static int fs = text_height(f);
	static int col = makecol(127,127,255);
	static int w = GAME_W / 2;
	
	
	textprintf_centre_ex(buffer, f, w, 0*fs, col, -1, "Objective: To land softly ");
	textprintf_centre_ex(buffer, f, w, 1*fs, COLOR_VELOCITY_BAR, -1, "(velocity gauge in the green)");
	textprintf_ex(buffer, f, 499, 1*fs, COLOR_VELOCITY_ZONE, -1, "green");
	textprintf_centre_ex(buffer, f, w, 2*fs, col, -1, "on a landing pad.  Once you");
	textprintf_centre_ex(buffer, f, w, 3*fs, col, -1, "score enough points you can");
	textprintf_centre_ex(buffer, f, w, 4*fs, col, -1, "go on to the next planet.");
	
	
	//"Default keys:"
	textprintf_ex(buffer, f, 75, (int)(5.5*fs), col, -1, "Left");
	textprintf_ex(buffer, f, 75, (int)(6.5*fs), col, -1, "Right");
	textprintf_ex(buffer, f, 75, (int)(7.5*fs), col, -1, "Q");
	textprintf_ex(buffer, f, 75, (int)(8.5*fs), col, -1, "A");
	textprintf_ex(buffer, f, 75, (int)(9.5*fs), col, -1, "Z");
	textprintf_ex(buffer, f, 75,(int)(10.5*fs), col, -1, "W");
	
	textprintf_ex(buffer, f, 300, (int)(5.5*fs), col, -1, "Thrust left");
	textprintf_ex(buffer, f, 300, (int)(6.5*fs), col, -1, "Thrust right");
	textprintf_ex(buffer, f, 300, (int)(7.5*fs), col, -1, "Thrust max");
	textprintf_ex(buffer, f, 300, (int)(8.5*fs), col, -1, "Thrust med");
	textprintf_ex(buffer, f, 300, (int)(9.5*fs), col, -1, "Thrust min");
	textprintf_ex(buffer, f, 300,(int)(10.5*fs), col, -1, "All thrusters");
}


