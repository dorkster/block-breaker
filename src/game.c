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

#include "sys.h"
#include "game.h"

player obj_p;
block obj_b[6][10];
ball obj_l;

bool action_moveleft = false;
bool action_moveright = false;

void game_init()
{
    if (use_mouse == true) SDL_ShowCursor(0);
    game_playerinit();
    game_blockscreate();
    game_ballcreate();
}

void game_logic()
{
    if(obj_p.lives == 0)
    {
        game_playerinit();
        game_blockscreate();
        game_ballcreate();
    }
    else if(game_blocktotal == 0)
    {
        game_blockscreate();
        game_ballcreate();
        obj_p.score += 5000;
    }

    game_playermove();
    game_ballcollide();
    game_ballmove();
}

void game_playerinit()
{
    obj_p.w = 100;
    obj_p.h = 8;
    obj_p.x = SCREEN_WIDTH/2 - obj_p.w/2;
    obj_p.y = 440;
    obj_p.speed = 0;
    obj_p.score = 0;
    obj_p.lives = 5;
}

void game_playermove()
{
    if (use_mouse == true) {
        obj_p.speed = mouse_x - obj_p.x - obj_p.w/2;
    } else {
        const int max = 16;

        if(action_moveleft == true && obj_p.speed > -max)
            obj_p.speed -= 1;
        else if(action_moveleft == false && obj_p.speed < 0)
            obj_p.speed += 1;

        if(action_moveright == true && obj_p.speed < max)
            obj_p.speed += 1;
        else if(action_moveright == false && obj_p.speed > 0)
            obj_p.speed -= 1;
    }

    obj_p.x += obj_p.speed;

    if(obj_p.x < 0)
        obj_p.x = 0;
    if(obj_p.x + obj_p.w > SCREEN_WIDTH)
        obj_p.x = SCREEN_WIDTH - obj_p.w;
}

void game_blockscreate()
{
    game_blocktotal = 60;
    int i,j;

    for(i=0;i<6;i++)
    {
        for(j=0;j<10;j++)
        {
            obj_b[i][j].alive = true;
            obj_b[i][j].x = j*BLOCK_WIDTH;
            obj_b[i][j].y = i*BLOCK_HEIGHT;

            if(i%2 == 0)
                obj_b[i][j].color = 0;
            else
                obj_b[i][j].color = 1;
        }
    }
}

void game_ballcreate()
{
    obj_l.x = obj_p.x+(obj_p.w/2);
    obj_l.y = obj_p.y-BALL_SIZE;
    obj_l.xvel = 0;
    obj_l.yvel = 0;
    game_holdingball = true;
}

void game_balllaunch()
{
    if(game_holdingball == true)
    {
        game_holdingball = false;
        obj_l.xvel = obj_p.speed/2;
        obj_l.yvel = -4;
    }
}

void game_ballmove()
{
    if(game_holdingball == true)
    {
        obj_l.x = obj_p.x+(obj_p.w/2);
        obj_l.y = obj_p.y-BALL_SIZE;
    }

    obj_l.x += obj_l.xvel;
    obj_l.y += obj_l.yvel;
}

void game_ballcollide()
{
    // Keep the ball on the screen
    if(obj_l.x-BALL_SIZE <= 0)
    {
        obj_l.x = 0 + BALL_SIZE;
        obj_l.xvel *= -1;
    }
    if(obj_l.x+BALL_SIZE >= SCREEN_WIDTH)
    {
        obj_l.x = SCREEN_WIDTH - BALL_SIZE;
        obj_l.xvel *= -1;
    }
    if(obj_l.y-BALL_SIZE <= 0)
    {
        obj_l.y = 0 + BALL_SIZE;
        obj_l.yvel *= -1;
    }

    // Respawn the ball if it goes past the paddle
    if(obj_l.y-BALL_SIZE >= SCREEN_HEIGHT)
    {
        obj_p.lives -= 1;
        game_ballcreate();
    }

    // Bounce off the paddle
    if(sys_collide(obj_p.x,obj_p.y,obj_p.w,obj_p.h,obj_l.x,obj_l.y,BALL_SIZE) == true)
    {
        obj_l.y = obj_p.y - BALL_SIZE;
        obj_l.yvel *=-1;
        
        obj_l.xvel += obj_p.speed;

        if(obj_l.xvel > 8)
            obj_l.xvel = 8;
        if(obj_l.xvel < -8)
            obj_l.xvel = -8;
    }

    // Destroy blocks when they're hit with the ball
    int i,j;

    for(i=0;i<6;i++)
    {
        for(j=0;j<10;j++)
        {
            if(sys_collide(obj_b[i][j].x,obj_b[i][j].y,BLOCK_WIDTH,BLOCK_HEIGHT,obj_l.x,obj_l.y,BALL_SIZE) == true && obj_b[i][j].alive == true)
            {
                obj_b[i][j].alive = false;
                game_blocktotal -= 1;
                obj_p.score += 100;

                if(obj_b[i][j].x <= obj_l.x - obj_l.xvel && obj_b[i][j].x+BLOCK_WIDTH >= obj_l.x - obj_l.xvel)
                {
                    obj_l.yvel *= -1;
                    obj_l.y += obj_l.yvel;
                }
                else
                {
                    obj_l.xvel *= -1;
                }

            }
        }
    }
}
