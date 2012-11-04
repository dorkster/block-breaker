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

#include "SDL/SDL_ttf.h"
#include "SDL/SDL_gfxPrimitives.h"
#include "sys.h"
#include "draw.h"
#include "game.h"

void draw_everything() {
    // Fill the screen with black
    SDL_FillRect(screen,NULL, 0xd9d9d9);
    
    draw_player();
    draw_blocks();
    draw_ball();
    draw_info();
    draw_power();
}

void draw_player() {
    boxRGBA(screen,
            player.x,
            player.y,
            player.x+player.w,
            player.y+player.h,
            43,43,43,255
            );
}

void draw_blocks() {
    int i,j;
    const int gap = 2;

    for(i=0;i<6;i++) {
        for(j=0;j<10;j++) {
            if(blocks[i][j].alive == true) {
                if(blocks[i][j].color == 0) {
                    boxRGBA(screen,
                            blocks[i][j].x+gap,
                            blocks[i][j].y+gap,
                            blocks[i][j].x+BLOCK_WIDTH-gap,
                            blocks[i][j].y+BLOCK_HEIGHT-gap,
                            90,128,114,255
                            );
                }
                else if(blocks[i][j].color == 1) {
                    boxRGBA(screen,
                            blocks[i][j].x+gap,
                            blocks[i][j].y+gap,
                            blocks[i][j].x+BLOCK_WIDTH-gap,
                            blocks[i][j].y+BLOCK_HEIGHT-gap,
                            109,90,128,255
                            );
                }
            }
        }
    }
}

void draw_ball() {
    filledEllipseRGBA(screen,
                      ball.x,
                      ball.y,
                      BALL_SIZE,
                      BALL_SIZE,
                      43,43,43,255
                      );
}

void draw_info() {
    char info[256];
    SDL_Color color = {43,43,43};

    sprintf(info,"Score: %-7d    Lives: %-2d",player.score,player.lives);
    text_info = TTF_RenderText_Solid(font,info,color);

    if(text_info == NULL) return;
    sys_surfaceapply(8,460,255,text_info,screen,NULL);
    SDL_FreeSurface(text_info);
}

void draw_power() {
    if (power.alive == false) return;

    short x[4] = { power.x, power.x+POWER_SIZE, power.x, power.x-POWER_SIZE };
    short y[4] = { power.y-POWER_SIZE, power.y, power.y+POWER_SIZE, power.y };

    filledPolygonRGBA(screen,
                      x, y,
                      4,
                      43, 43, 43, 255);
}
