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

vector<Asteroid*> Big_Asteroids;
vector<Asteroid*> Medium_Asteroids;
vector<Asteroid*> Small_Asteroids;

Spaceship Player_Spaceship;
Image Playing_Background;
Image Arrow_Selected;
Image Background_logo;
Image Background_menu;
Image Instructions;


TTF_Font* font_32;
TTF_Font* font_24;

SDL_Color White = {255,255,255};
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Event event;

bool game_Running = true;
bool intro = true;
bool main_menu = false;
bool start_game = false;
bool Death_menu = false;
bool Playing = false;
int menu = PLAY;
bool menu_selected = false;

void logSDLError(ostream& os, const string &msg, bool fatal)
{
    os << msg << " Error: " << SDL_GetError() << endl;
    if (fatal)
    {
        SDL_Quit();
        exit(0);
    }
}

bool Check_Collision(const SDL_Rect& object1, const SDL_Rect& object2)
{
	int left_a = object1.x;
	int right_a = object1.x + object1.w;
	int top_a = object1.y;
	int bottom_a = object1.y + object1.h;

	int left_b = object2.x;
	int right_b = object2.x + object2.w;
	int top_b = object2.y;
	int bottom_b = object2.y + object2.h;

	if (left_a > left_b && left_a < right_b)
	{
		if (top_a > top_b && top_a < bottom_b) return true;
		if (bottom_a > top_b && bottom_a < bottom_b) return true;
	}

	if (right_a > left_b && right_a < right_b)
	{
		if (top_a > top_b && top_a < bottom_b) return true;
		if (bottom_a > top_b && bottom_a < bottom_b) return true;
	}

	if (top_a == top_b && right_a == right_b && bottom_a == bottom_b) return true;
	return false;
}

void Render_Message(SDL_Renderer* Renderer, float p_x, float p_y, const char* p_Text, TTF_Font* font, SDL_Color textColor)
{
	SDL_Surface* Surface_Message = TTF_RenderText_Blended(font, p_Text, textColor);
	SDL_Texture* Message = SDL_CreateTextureFromSurface(Renderer, Surface_Message);

	SDL_Rect src;
	src.x = 0;
	src.y = 0;
	src.w = Surface_Message->w;
	src.h = Surface_Message->h;

	SDL_Rect dst;
	dst.x = p_x;
	dst.y = p_y;
	dst.w = src.w;
	dst.h = src.h;


	SDL_RenderCopy(Renderer, Message, &src, &dst);
	SDL_FreeSurface(Surface_Message);
	SDL_DestroyTexture(Message);
}

void Render_Center(SDL_Renderer* Renderer, float p_x, float p_y, const char* p_Text, TTF_Font* font, SDL_Color textColor)
{
	SDL_Surface* Surface_Message = TTF_RenderText_Blended(font, p_Text, textColor);
	SDL_Texture* Message = SDL_CreateTextureFromSurface(Renderer, Surface_Message);

	SDL_Rect src;
	src.x = 0;
	src.y = 0;
	src.w = Surface_Message->w;
	src.h = Surface_Message->h;

	SDL_Rect dst;
	dst.x = (SCREEN_WIDTH - src.w) / 2 + p_x;
	dst.y = (SCREEN_HEIGHT - src.h) / 2 + p_y;
	dst.w = src.w;
	dst.h = src.h;

	SDL_RenderCopy(Renderer, Message, &src, &dst);
	SDL_FreeSurface(Surface_Message);
	SDL_DestroyTexture(Message);
}
