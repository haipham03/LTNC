#pragma once
#include "Image.h"

class Bullet:public Image
{
public:
    int x_speed;
	int y_speed;
	int velocity;
	double angle;

	Bullet()
	{
	    Frame.x = 0;
        Frame.y = 0;

        x_speed = 1;
        y_speed = 1;
        velocity = 0;
        angle = 0;
	}
	void Render(SDL_Renderer* G_Renderer)
	{
	    SDL_RenderCopy(G_Renderer, Tex, NULL, &Frame);
	}
	int get_speed_x()
	{
		return x_speed;
	}
	int get_speed_y()
	{
		return y_speed;
	}
	int get_velocity()
	{
		return velocity;
	}
	void set_velocity(int _velocity)
	{
		velocity = _velocity;
	}
	double get_angle()
	{
		return angle;
	}
	void set_angle(double _angle)
	{
		angle = _angle;
	}
	void Fire()
	{
        x_speed = velocity * sin(angle * (2 * 3.14) / 360);
        y_speed = velocity * -cos(angle * (2 * 3.14) / 360);

        Frame.x += x_speed;
        Frame.y += y_speed;
	}
};
