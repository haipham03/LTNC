#include<bits/stdc++.h>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>

using namespace std;

bool Init_All()
{
	int img_flags = IMG_INIT_PNG;
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		cout << "Failed to initiate SDL: " << SDL_GetError() << endl;
		return false;
	}
	if (TTF_Init() < 0)
	{
		cout << "Failed to load SDL_ttf: " << TTF_GetError() << endl;
		return false;
	}
	if ((IMG_Init(img_flags)& img_flags) != img_flags)
	{
		cout << "Failed to load SDL_image: " << IMG_GetError() << endl;
		return false;
	}
	window = SDL_CreateWindow("Astro", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == nullptr)
    {
        logSDLError(cout, "CreateWindow", true);
        return false;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL)
    {
        cout << "Failed to create window: " << SDL_GetError() << endl;
        return false;
    }
	return true;
}

void close()
{
	SDL_DestroyRenderer(renderer);
	renderer = NULL;

	SDL_DestroyWindow(window);
	window = NULL;

	SDL_Quit();
	IMG_Quit();
	TTF_Quit();
}

int main(int argc, char* argv[])
{
	srand(time(NULL));
	if (!Init_All())
	{
		cout << "ERROR!!" << endl;
		close();
		return 0;
	}
}
