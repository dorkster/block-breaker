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

#include <stdlib.h>

#include "sys.h"
#include "game.h"

Player player;
Block blocks[6][10];
Ball ball;
Power power;

const int POWER_SMALL=0;
const int POWER_NORMAL=1;
const int POWER_LARGE=2;

bool action_moveleft = false;
bool action_moveright = false;

void game_init() {
    if (use_mouse == true) SDL_ShowCursor(0);

    power.alive = false;

    game_playerinit();
    game_blockscreate();
    game_ballcreate();
}

void game_logic() {
    if(player.lives == 0) {
        game_playerinit();
        game_blockscreate();
        game_ballcreate();
        power.alive = false;
    }
    else if(game_blocktotal == 0) {
        game_blockscreate();
        game_ballcreate();
        player.score += 5000;
        power.alive = false;
    }

    game_playermove();
    game_ballmove();
    game_powermove();
    game_collide();
}

void game_playerinit() {
    player.w = 100;
    player.h = 8;
    player.x = SCREEN_WIDTH/2 - player.w/2;
    player.y = 440;
    player.speed = 0;
    player.score = 0;
    player.lives = 5;
}

void game_playermove() {
    if (use_mouse == true) {
        player.speed = mouse_x - player.x - player.w/2;
    } else {
        const int max = 16;

        if(action_moveleft == true && player.speed > -max)
            player.speed -= 1;
        else if(action_moveleft == false && player.speed < 0)
            player.speed += 1;

        if(action_moveright == true && player.speed < max)
            player.speed += 1;
        else if(action_moveright == false && player.speed > 0)
            player.speed -= 1;
    }

    player.x += player.speed;

    if(player.x < 0)
        player.x = 0;
    if(player.x + player.w > SCREEN_WIDTH)
        player.x = SCREEN_WIDTH - player.w;
}

void game_blockscreate() {
    game_blocktotal = 60;
    int i,j;

    for(i=0;i<6;i++) {
        for(j=0;j<10;j++) {
            blocks[i][j].alive = true;
            blocks[i][j].x = j*BLOCK_WIDTH;
            blocks[i][j].y = i*BLOCK_HEIGHT;

            if(i%2 == 0)
                blocks[i][j].color = 0;
            else
                blocks[i][j].color = 1;
        }
    }
}

void game_ballcreate() {
    ball.x = player.x+(player.w/2);
    ball.y = player.y-BALL_SIZE;
    ball.xvel = 0;
    ball.yvel = 0;
    game_holdingball = true;
}

void game_balllaunch() {
    if(game_holdingball == true) {
        game_holdingball = false;
        ball.xvel = player.speed/2;
        ball.yvel = -4;
    }
}

void game_ballmove() {
    if(game_holdingball == true) {
        ball.x = player.x+(player.w/2);
        ball.y = player.y-BALL_SIZE;
    }

    ball.x += ball.xvel;
    ball.y += ball.yvel;
}

void game_collide() {
    // Keep the ball on the screen
    if(ball.x-BALL_SIZE <= 0) {
        ball.x = 0 + BALL_SIZE;
        ball.xvel *= -1;
    }
    if(ball.x+BALL_SIZE >= SCREEN_WIDTH) {
        ball.x = SCREEN_WIDTH - BALL_SIZE;
        ball.xvel *= -1;
    }
    if(ball.y-BALL_SIZE <= 0) {
        ball.y = 0 + BALL_SIZE;
        ball.yvel *= -1;
    }

    // Respawn the ball if it goes past the paddle
    if(ball.y-BALL_SIZE >= SCREEN_HEIGHT) {
        player.lives -= 1;
        game_ballcreate();
    }

    // Bounce off the paddle
    if(sys_collide(player.x,player.y,player.w,player.h,ball.x,ball.y,BALL_SIZE) == true) {
        ball.y = player.y - BALL_SIZE;
        ball.yvel *=-1;
        
        ball.xvel += player.speed;

        if(ball.xvel > 8)
            ball.xvel = 8;
        if(ball.xvel < -8)
            ball.xvel = -8;
    }

    // Handle power-ups
    if (power.alive == true) {
        // Expire power-up if it falls off the screen
        if (power.y-POWER_SIZE >= SCREEN_HEIGHT) {
            power.alive = false;
        }

        // Check power-up collection
        if(sys_collide(player.x,player.y,player.w,player.h,power.x,power.y,POWER_SIZE) == true) {
            power.alive = false;
            if (power.type == POWER_SMALL) player.w = 50;
            else if (power.type == POWER_NORMAL) player.w = 100;
            else if (power.type == POWER_LARGE) player.w = 200;
        }
    }

    // Destroy blocks when they're hit with the ball
    int i,j;

    for(i=0;i<6;i++) {
        for(j=0;j<10;j++) {
            if(blocks[i][j].alive == true && sys_collide(blocks[i][j].x,blocks[i][j].y,BLOCK_WIDTH,BLOCK_HEIGHT,ball.x,ball.y,BALL_SIZE) == true) {
                blocks[i][j].alive = false;
                game_blocktotal -= 1;
                player.score += 100;
                game_powercreate(blocks[i][j].x+BLOCK_WIDTH/2, blocks[i][j].y+BLOCK_HEIGHT/2);

                if(blocks[i][j].x <= ball.x - ball.xvel && blocks[i][j].x+BLOCK_WIDTH >= ball.x - ball.xvel) {
                    ball.yvel *= -1;
                    ball.y += ball.yvel;
                }
                else {
                    ball.xvel *= -1;
                }
            }
        }
    }
}

void game_powercreate(int x, int y) {
    if (power.alive == true) return;

    power.x = x;
    power.y = y;

    if (player.w != 100 && rand() % 4 == 0) {
        power.type = POWER_NORMAL;
        power.alive = true;
    } else if (rand() % 16 == 0) {
        power.type = POWER_LARGE;
        power.alive = true;
    } else if (rand() % 8 == 0) {
        power.type = POWER_SMALL;
        power.alive = true;
    }
}

void game_powermove() {
    if (power.alive == false) return;

    power.y += 2;
}
