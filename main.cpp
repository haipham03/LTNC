#include "Image.h"
#include "Use.h"

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

bool Load_Asteroids(const char* file_path)
{
    Asteroid* cur_Asteroid = new Asteroid;
    if (!cur_Asteroid->Load_Image(file_path, renderer))
    {
        cout << "Image Error: " << endl;
        return false;
    }
	return true;
}

bool Load()
{
	font_32 = TTF_OpenFont("Game_BG/Font.ttf", 32);
	font_24 = TTF_OpenFont("Game_BG/Font.ttf", 24);
	if (!Background_logo.Load_Image("Game_BG/Background_logo.png", renderer))
	{
		cout << "Background Logo error!" << endl;
		return false;
	}
	if (!Background_menu.Load_Image("Game_BG/Background_menu.png", renderer))
	{
		cout << "Background menu error!" << endl;
		return false;
	}
	if (!Instructions.Load_Image("Game_BG/Instructions.png", renderer))
	{
		cout << "Instruction background error!" << endl;
		return false;
	}
	if (!Arrow_Selected.Load_Image("Game_BG/Arrow.png", renderer))
	{
		cout << "Arrow selected error!" << endl;
		return false;
	}
	if (!Playing_Background.Load_Image("Game_BG/Background_main.png", renderer))
	{
		cout << "Background Error!" << endl;
		return false;
	}
	if (!Player_Spaceship.Load_Image("Game_BG/Spaceship.png", renderer))
	{
		cout << "Image Error: " << endl;
		return false;
	}
	if (!Load_Asteroids("Game_BG/Big_Asteroid.png")) return false;
	if (!Load_Asteroids("Game_BG/Medium_Asteroid.png")) return false;
	if (!Load_Asteroids("Game_BG/Small_Asteroid.png")) return false;
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
	int open_game_time = SDL_GetTicks();

    SDL_RenderClear(renderer);
    Background_logo.Render(renderer);

    while (intro)
	{
		int current_opengame_time = SDL_GetTicks();
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				intro = false;
				game_Running = false;
			}
		}
		if (current_opengame_time - open_game_time > 2500)
		{
			intro = false;
			game_Running = true;
			main_menu = true;
		}
		SDL_RenderPresent(renderer);
	}
	while (game_Running)
	{
		while (main_menu)
		{
			SDL_RenderClear(renderer);
			while (SDL_PollEvent(&event))
			{
				switch (event.type)
				{
				case SDL_QUIT:
					main_menu = false;
					start_game = false;
					game_Running = false;
				case SDL_KEYDOWN:
					switch (event.key.keysym.sym)
					{
					case SDLK_UP:
						if (!menu_selected) menu--;
						break;
					case SDLK_DOWN:
						if (!menu_selected) menu++;
						break;
					case SDLK_s:
						menu_selected = true;
						break;
					case SDLK_y:
						menu_selected = false;
						break;
					default:
						break;
					}
				}
			}
			if (menu > EXIT) menu = PLAY;
			if (menu < PLAY) menu = EXIT;
			if (menu_selected == false)
			{
				Background_menu.Render(renderer);
				Arrow_Selected.set_Y(240 + menu * 100);
				Arrow_Selected.Render(renderer);
			}
			else
			{
				switch (menu)
				{
				case PLAY:
					main_menu = false;
					start_game = true;
					menu_selected = false;
					break;
				case INSTRUCTION:
					Instructions.Render(renderer);
					break;
				case EXIT:
					main_menu = false;
					start_game = false;
					game_Running = false;
					break;
				}
			}
			SDL_RenderPresent(renderer);
		}

		//load start game renderer
		while (start_game)
		{
			while (SDL_PollEvent(&event))
			{
				if (event.type == SDL_QUIT)
				{
					start_game = false;
					game_Running = false;
				}
				if (event.type == SDL_MOUSEBUTTONDOWN)
				{
					if (event.button.button == SDL_BUTTON_LEFT)
					{
						Playing = true;
						start_game = false;
					}
				}
			}
			SDL_RenderClear(renderer);
			Render_Center(renderer, 0, sin(SDL_GetTicks() / 100), "CLICK TO START", font_24, White);
			SDL_RenderPresent(renderer);
		}

		int start_game_time = SDL_GetTicks();

		int time_new_asteroid = SDL_GetTicks();

		int current_time = SDL_GetTicks();

		int player_score = 0;


		//load playing renderer
		while (Playing)
		{
			SDL_RenderClear(renderer);
			Playing_Background.Render(renderer);
			while (SDL_PollEvent(&event))
			{
				if (event.type == SDL_QUIT)
				{
					Playing = false;
					game_Running = false;
				}
				Player_Spaceship.Handle_Event(event);
			}

			Player_Spaceship.Move(renderer);

			//Collision between bullets and asteroids
			for (int i = 0; i < Player_Spaceship.get_Bullets().size(); i++)
			{
				if(CheckBullet(BIG,Big_Asteroids,i,player_score)) continue;
				if(CheckBullet(MEDIUM,Medium_Asteroids,i,player_score)) continue;
				if(CheckBullet(SMALL,Small_Asteroids,i,player_score)) continue;
			}

			//Collision between spaceship and asteroids
			bool ck_Big = checkSpaceship(BIG,Big_Asteroids,player_score);
			bool ck_Med = checkSpaceship(MEDIUM,Medium_Asteroids,player_score);
			bool ck_Small = checkSpaceship(SMALL,Small_Asteroids,player_score);
			if(!ck_Big||!ck_Med||!ck_Small)
            {
                Playing = false;
                Death_menu = true;
            }


			//Add new asteroid
			current_time = SDL_GetTicks();
			if (current_time - time_new_asteroid > SPAWN_ASTEROID_TIME)
			{
				player_score += SURVIVAL_SCORE;
				time_new_asteroid = SDL_GetTicks();
				int i = rand() % 3;
				Playing = Add_Asteroid(i);
            }

			const string current_hp = to_string(Player_Spaceship.get_current_HP());

			//render hp number
			Render_Message(renderer, 1210, 50, current_hp.c_str(), font_24, White);

			//render HP
			SDL_Rect fillRect = { 900, 50, 300 * Player_Spaceship.get_current_HP() / Player_Spaceship.get_max_HP(), 20 };
			SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
			SDL_RenderFillRect(renderer, &fillRect);

			//render HP border
			SDL_Rect outlineRect = { 900, 50, 300, 20 };
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			SDL_RenderDrawRect(renderer, &outlineRect);

			//black raw renderer
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

			string currentScore = "SCORE: " + to_string(player_score);
			Render_Message(renderer, 900, 100, currentScore.c_str(), font_24, White);

			Render_Asteroid(Big_Asteroids);
			Render_Asteroid(Medium_Asteroids);
			Render_Asteroid(Small_Asteroids);
			Player_Spaceship.Render(renderer);
			SDL_RenderPresent(renderer);
		}
		int death_start_time = SDL_GetTicks();
		string player_total_score = "YOUR SCORE: " + to_string(player_score);
		while (Death_menu)
		{
			while (SDL_PollEvent(&event))
			{
				if (event.type == SDL_QUIT)
				{
					Death_menu = false;
					game_Running = false;
				}
			}
			int death_current_time = SDL_GetTicks();
			if (death_current_time - death_start_time < 3000)
			{
				SDL_RenderClear(renderer);
				//render score string
				Render_Message(renderer, 527, 400 + sin(SDL_GetTicks() / 100), player_total_score.c_str(), font_24, White);
				//render dead message
				Render_Center(renderer, 0, sin(SDL_GetTicks() / 100), "GAME OVER!", font_32, White);
				SDL_RenderPresent(renderer);
			}
			else
			{
                Death_menu = false;
                main_menu = true;
                Reset_Game();
			}
		}

	}
	close();
	return 0;
}
