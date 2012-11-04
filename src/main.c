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
#include <stdlib.h>
#include <time.h>

#include "sys.h"
#include "draw.h"
#include "game.h"

int main(int argc, char* argv[]) {
    srand(time(0));

    char c = 0;
    while (--argc > 0 && (*++argv)[0] == '-') {
        while ((c = *++argv[0])) {
            if (c == 'x') {
                use_mouse = false;
                break;
            }
        }
    }

    if(sys_init() == false) return 1;
    if(sys_loadfiles() == false) return 1;

    game_init();

    while(quit == false) {
        startTimer = SDL_GetTicks();

        sys_input();
        game_logic();
        draw_everything();

        // Update the screen
        if(SDL_Flip(screen) == -1) return 1;
        
        // Limit the frame rate
        endTimer = SDL_GetTicks();
        deltaTimer = endTimer - startTimer;
        if(deltaTimer < (1000/FPS))
            SDL_Delay((1000/FPS)-deltaTimer);
    }
    sys_cleanup();
}
