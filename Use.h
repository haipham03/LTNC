#include<bits/stdc++.h>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>

using namespace std;

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

const int SPAWN_ASTEROID_TIME = 3000;

const int DAMAGE_Asteroid[] = {4,2,1};
const int HP_Asteroid[] = {9,4,1};
const int SCORE_Asteroid[] = {9,3,1};

const int SURVIVAL_SCORE = 1;

const int SMALL = 2;
const int MEDIUM = 1;
const int BIG = 0;

const int PLAYER_HP = 20;
const int PLAYER_BULLET_DAMAGE = 1;
const int PLAYER_VELOCITY = 3;

const int PLAY = 0;
const int INSTRUCTION = 1;
const int EXIT = 2;
