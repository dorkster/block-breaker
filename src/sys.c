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
#include "sys.h"
#include "game.h"

SDL_Surface* screen = NULL;
TTF_Font* font = NULL;
SDL_Surface* text_info = NULL;
bool quit = false;

bool sys_init()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) == -1) { return false; }
    
    screen = SDL_SetVideoMode(SCREEN_WIDTH,SCREEN_HEIGHT,SCREEN_BPP,SDL_SWSURFACE);

    if(screen == NULL) { return false; }
    
    if( TTF_Init() == -1 ) { return false; }
    
    SDL_WM_SetCaption("Block Breaker",NULL);
    
    return true;
}

bool sys_loadfiles()
{
    font = TTF_OpenFont("./font/LCD_Solid.ttf",16);
    if(font == NULL) {return false;}

    return true;
}

void sys_cleanup()
{
    TTF_CloseFont(font);
    SDL_Quit();
}

void sys_surfaceapply( int x, int y, int alpha, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip )
{
    //Make a temporary rectangle to hold the offsets
    SDL_Rect offset;

    //Give the offsets to the rectangle
    offset.x = x;
    offset.y = y;
    
    //Blit the surface
    SDL_SetAlpha( source, SDL_SRCALPHA, alpha);
    SDL_BlitSurface( source, clip, destination, &offset );
}

void sys_input()
{
    while(SDL_PollEvent(&event))
    {
        if( event.type == SDL_KEYDOWN )
        {
            if(event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == 'z')
                action_moveleft = true;
            if(event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == 'x')
                action_moveright = true;
            if(event.key.keysym.sym == ' ')
                game_balllaunch();

            if(event.key.keysym.sym == SDLK_ESCAPE)
                quit = true;
        }

        if( event.type == SDL_KEYUP )
        {
            if(event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == 'z')
                action_moveleft = false;
            if(event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == 'x')
                action_moveright = false;
        }
            
        if(event.type == SDL_QUIT)
        {
            quit = true;
        }
    }
}

bool sys_collide(int xa, int ya, int wa, int ha, int xb, int yb, int rb)
{
    if(ya >= yb+rb)
        return false;
    if(ya+ha <= yb-rb)
        return false;
    if(xa >= xb+rb)
        return false;
    if(xa+wa <= xb-rb)
        return false;

    return true;
}
