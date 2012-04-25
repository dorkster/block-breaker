/*
    Block Breaker - A clone of THAT game
    Copyright (C) 2012 Justin Jacobs

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"

typedef enum { false = 0, true = 1 } bool;

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define SCREEN_BPP 32
#define FPS 60
#define DEGTORAD 0.0174532925 

extern SDL_Surface* screen;
extern TTF_Font* font;
extern SDL_Surface* text_info;
extern bool quit;

SDL_Event event;

// Timers
unsigned int startTimer;
unsigned int endTimer;
unsigned int deltaTimer;

// Functions
bool sys_init();
bool sys_loadfiles();
void sys_cleanup();
void sys_surfaceapply( int x, int y, int alpha, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip );
void sys_input();
bool sys_collide(int xa, int ya, int wa, int ha, int xb, int yb, int rb);
