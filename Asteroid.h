#include "Image.h"

class Asteroid :public Image
{
public:
    int x_speed;
	int y_speed;
	double angle;
	int max_HP;
	int current_HP;

	Asteroid()
	{
	    x_speed = 1;
        y_speed = 1;
        angle = 0;
	}
	~Asteroid()
	{
	    Image::Free();
	}
	int get_speed_x()
	{
		return x_speed;
	}
	int get_speed_y()
	{
		return y_speed;
	}
	double get_angle()
	{
		angle += 0.5;
		if (angle == 360) angle = 0;
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
	void Attacked(const int& Damage)
	{
		current_HP -= Damage;
	}
	void Render(SDL_Renderer* G_Renderer)
	{
        Frame.x += x_speed;
        Frame.y += y_speed;

        if (Frame.x + Frame.w < 0)
        {
            Frame.x += 1280 + Frame.w;
        }
        if (Frame.x > 1280)
        {
            Frame.x -= 1280 + Frame.w;
        }
        if (Frame.y + Frame.h < 0)
        {
            Frame.y += 720 + Frame.h;
        }
        if (Frame.y > 720)
        {
            Frame.y -= 720 + Frame.h;
        }
        SDL_RenderCopyEx(G_Renderer, Tex, NULL, &Frame, get_angle(), NULL, SDL_FLIP_NONE);
	}
};
