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

typedef struct player{
    int x,y,w,h;
    int speed;
    int score;
    int lives;
}player;

typedef struct block{
    int x,y;
    bool alive;
    int color;
}block;

typedef struct ball{
    int x,y;
    int xvel,yvel;
}ball;

extern player obj_p;
extern block obj_b[6][10];
extern ball obj_l;

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
void game_ballcollide();
