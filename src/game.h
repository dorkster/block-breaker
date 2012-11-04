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

#define BLOCK_WIDTH 64
#define BLOCK_HEIGHT 32
#define BALL_SIZE 4
#define POWER_SIZE 8

typedef struct Player{
    int x,y,w,h;
    int speed;
    int score;
    int lives;
}Player;

typedef struct Block{
    int x,y;
    bool alive;
    int color;
}Block;

typedef struct Ball{
    int x,y;
    int xvel,yvel;
}Ball;

typedef struct Power{
    int x,y;
    bool alive;
    int type;
}Power;

extern Player player;
extern Block blocks[6][10];
extern Ball ball;
extern Power power;

extern bool action_moveleft;
extern bool action_moveright;

bool game_holdingball;
int game_blocktotal;

void game_init();
void game_logic();

void game_playerinit();
void game_playermove();

void game_blockscreate();

void game_ballcreate();
void game_balllaunch();
void game_ballmove();

void game_collide();

void game_powercreate(int x, int y);
void game_powermove();
