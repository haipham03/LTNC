#pragma once

#include<bits/stdc++.h>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>

using namespace std;


class Image
{
public:
    SDL_Texture* Tex;
	SDL_Rect Frame;

	Image()
	{
	    Tex = NULL;
        Frame.w = 0;
        Frame.h = 0;
        Frame.x = 0;
        Frame.y = 0;
	}
	bool Load_Image(const char* file_path,SDL_Renderer* G_Renderer)
	{
        SDL_Surface* image = NULL;
        image = IMG_Load(file_path);
        if (image == NULL)
        {
            cout << "Failed to load Image: " << file_path << " - " << IMG_GetError() << endl;
            return false;
        }
        else
        {
            Tex = SDL_CreateTextureFromSurface(G_Renderer, image);
            if (Tex == NULL)
            {
                cout << "Failed to create Texture: " << file_path << " - " << IMG_GetError() << endl;
                return false;
            }
        }
        Frame.w = image->w;
        Frame.h = image->h;
        SDL_FreeSurface(image);
        image = NULL;
        return true;
	}
	void Render(SDL_Renderer* G_Renderer)
	{
	    SDL_RenderCopy(G_Renderer, Tex, NULL, &Frame);
	}
	SDL_Rect Get_Rect()
	{
		return Frame;
	}
	int get_X()
	{
		return Frame.x;
	}
	int get_Y()
	{
		return Frame.y;
	}
	void set_X(int _x)
	{
		Frame.x = _x;
	}
	void set_Y(int _y)
	{
		Frame.y = _y;
	}
	void Free()
	{
        if (Tex != NULL)
        {
            SDL_DestroyTexture(Tex);
            Tex = NULL;
        }
	}
};
