#pragma once

#include "Image.h"
#include "Bullet.h"
class Spaceship :public Image
{
public:
    int velocity;
	int x_velocity;
	int y_velocity;

	double angle;
	double angle_speed;

	vector<Bullet*> Bullets;
	int Shoot;
	bool Lock_shot = false;

	int max_HP;
	int current_HP;
	int Bullet_dmg;

	bool Key_LEFT = false, Key_RIGHT = false, Key_UP = false, Key_DOWN = false, key_S = false;

	Spaceship()
	{
	    Frame.x = 640-Frame.w/2;
        Frame.y = 360-Frame.h/2;

        velocity = 0;
        x_velocity = 1;
        y_velocity = 1;

        angle = 0;
        angle_speed = 1;

        Shoot = 0;
        current_HP = 0;
        max_HP = 0;
        Bullet_dmg = 0;
	}
	void Render(SDL_Renderer* G_Renderer);
	void Handle_Event(SDL_Event& p_Event);
	void Move(SDL_Renderer* G_Renderer);
	void Reset();
	void set_Bullets(const vector<Bullet*>& bullets)
	{
		Bullets = bullets;
	}
	vector<Bullet*> get_Bullets()
	{
		return Bullets;
	}
	void remove_Bullets(int& i);
	int get_velocity()
	{
		return velocity;
	}
	int get_x_velocity()
	{
		return x_velocity;
	}
	int get_y_velocity()
	{
		return y_velocity;
	}
	void set_velocity(int _velocity)
	{
		velocity = _velocity;
	}
	double get_angle()
	{
		return angle;
	}
	void set_HP(int _hp)
	{
		max_HP = _hp;
		current_HP = _hp;
	}
	int get_max_HP()
	{
		return max_HP;
	}
	int get_current_HP()
	{
		return current_HP;
	}
	void Attacked(int& Damage)
	{
		current_HP -= Damage;
	}
	int get_Bullet_dmg()
	{
		return Bullet_dmg;
	}
	void set_Bullet_dmg(int _dmg)
	{
		Bullet_dmg = _dmg;
	}
	void Get_Damage(int _dame)
	{
		current_HP -= _dame;
	}
};

void Spaceship::Render(SDL_Renderer* G_Renderer)
{
	SDL_RenderCopyEx(G_Renderer, Tex, NULL, &Frame, angle, NULL, SDL_FLIP_NONE);
	for (int i = 0; i < Bullets.size(); i++)
	{
		Bullets.at(i)->Render(G_Renderer);
	}
}

void Spaceship::Handle_Event(SDL_Event& p_Event)
{
	if (p_Event.type == SDL_KEYDOWN)
	{
		switch (p_Event.key.keysym.sym)
		{
		case SDLK_UP:
			Key_UP = true;
			break;
		case SDLK_DOWN:
			Key_DOWN = true;
			break;
		case SDLK_LEFT:
			Key_LEFT = true;
			break;
		case SDLK_RIGHT:
			Key_RIGHT = true;
			break;
		case SDLK_s:
			key_S = true;
			break;
		}
	}
	else if (p_Event.type == SDL_KEYUP)
	{
		switch (p_Event.key.keysym.sym)
		{
		case SDLK_UP:
			Key_UP = false;
			break;
		case SDLK_DOWN:
			Key_DOWN = false;
			break;
		case SDLK_LEFT:
			Key_LEFT = false;
			break;
		case SDLK_RIGHT:
			Key_RIGHT = false;
			break;
		case SDLK_s:
			key_S = false;
			break;
		}
	}
}

void Spaceship::remove_Bullets(int& i)
{
	if (i >= Bullets.size())
	{
		return;
	}
	Bullet* Current_Bullet = Bullets.at(i);
	Bullets.erase(Bullets.begin() + i);
	if (Current_Bullet)
	{
		delete Current_Bullet;
		Current_Bullet = NULL;
	}
}
void Spaceship::Move(SDL_Renderer* G_Renderer)
{
	angle += angle_speed;
	if (key_S == true)
	{
		if (Lock_shot == false)
		{
			Shoot++;
			Bullet* Bullets_i = new Bullet();
			Bullets_i->Load_Image("Game_BG/Bullet.png", G_Renderer);
			Bullets_i->set_X(Frame.x + Frame.w / 2  + sin(angle * (2 * 3.14) / 360));
			Bullets_i->set_Y(Frame.y + Frame.w / 2 - cos(angle * (2 * 3.14) / 360));
			Bullets_i->set_angle(angle);
			Bullets_i->set_velocity(velocity * 2);
			Bullets.push_back(Bullets_i);
			Lock_shot = true;
		}
	}
	if (key_S == false) Lock_shot = false;

	for (int i = 0; i < Bullets.size(); i++)
	{
		Bullet* Current_Bullet = Bullets.at(i);
		Current_Bullet->Fire();
		if (Current_Bullet->get_X() < 0 || Current_Bullet->get_X() > 1280 || Current_Bullet->get_Y() < 0 || Current_Bullet->get_Y() > 720)
		{
			Bullets.erase(Bullets.begin() + i);
            delete Current_Bullet;
            Current_Bullet = NULL;
		}
	}
	if (Key_LEFT == true) angle_speed = -1;
	if (Key_RIGHT == true) angle_speed = 1;

	x_velocity = velocity * sin(angle * (2 * 3.14) / 360);
	y_velocity = velocity * -cos(angle * (2 * 3.14) / 360);

	if (Key_UP == true)
	{
		Frame.x += x_velocity;
		Frame.y += y_velocity;
	}
	if (Key_DOWN == true)
	{
		Frame.x -= x_velocity;
		Frame.y -= y_velocity;
	}
	if (angle >= 360) angle -= 360;
	if (angle < 0) angle += 360;
	if (Frame.x + Frame.w < 0) Frame.x += 1280 + Frame.w;
	if (Frame.x > 1280) Frame.x -= 1280 + Frame.w;
	if (Frame.y + Frame.h < 0) Frame.y += 720 + Frame.h;
	if (Frame.y > 720) Frame.y -= 720 + Frame.h;
}

void Spaceship::Reset()
{
	Frame.x = 640 - Frame.w / 2;
	Frame.y = 360 - Frame.h / 2;

	velocity = 0;
	x_velocity = 1;
	y_velocity = 1;

	angle = 0;
	angle_speed = 1;

	Shoot = 0;
	current_HP = 0;
	max_HP = 0;
	Bullet_dmg = 0;
	int i = 0;
	Key_LEFT = false, Key_RIGHT = false, Key_UP = false, Key_DOWN = false, key_S = false;
	while (Bullets.size() > 0) remove_Bullets(i);
}
