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

void draw_everything()
{
    // Fill the screen with black
    SDL_FillRect(screen,NULL, 0xd9d9d9);
    
    draw_player();
    draw_blocks();
    draw_ball();
    draw_info();
}

void draw_player()
{
    boxRGBA(screen,
            obj_p.x,
            obj_p.y,
            obj_p.x+obj_p.w,
            obj_p.y+obj_p.h,
            43,43,43,255
            );
}

void draw_blocks()
{
    int i,j;
    const int gap = 2;

    for(i=0;i<6;i++)
    {
        for(j=0;j<10;j++)
        {
            if(obj_b[i][j].alive == true)
            {
                if(obj_b[i][j].color == 0)
                {
                    boxRGBA(screen,
                            obj_b[i][j].x+gap,
                            obj_b[i][j].y+gap,
                            obj_b[i][j].x+BLOCK_WIDTH-gap,
                            obj_b[i][j].y+BLOCK_HEIGHT-gap,
                            90,128,114,255
                            );
                }
                else if(obj_b[i][j].color == 1)
                {
                    boxRGBA(screen,
                            obj_b[i][j].x+gap,
                            obj_b[i][j].y+gap,
                            obj_b[i][j].x+BLOCK_WIDTH-gap,
                            obj_b[i][j].y+BLOCK_HEIGHT-gap,
                            109,90,128,255
                            );
                }

            }
        }
    }
}

void draw_ball()
{
    filledEllipseRGBA(screen,
                      obj_l.x,
                      obj_l.y,
                      BALL_SIZE,
                      BALL_SIZE,
                      43,43,43,255
                      );
}

void draw_info()
{
    char info[256];
    SDL_Color color = {43,43,43};

    sprintf(info,"Score: %-7d    Lives: %-2d",obj_p.score,obj_p.lives);
    text_info = TTF_RenderText_Solid(font,info,color);

    if(text_info == NULL){return;}
    sys_surfaceapply(8,460,255,text_info,screen,NULL);
    SDL_FreeSurface(text_info);
}
