#include <iostream>
#include "SDL.h"
#include "Game.h"

using namespace std;

int main(int argc, char* argv[])
{
	if (SDL_Init(SDL_INIT_VIDEO) == 0)
	{
		SDL_Window* SDLWindow = nullptr;
		SDL_Renderer* SDLRenderer = nullptr;

		if (SDL_CreateWindowAndRenderer(WINDOWWIDTHSIZE, WINDOWLENGTHSIZE, 0, &SDLWindow, &SDLRenderer) == 0)
		{
			Game* game = new Game();
			game->InitGame(SDLRenderer);

			while (game->HasQuit() == SDL_FALSE)
			{
				game->Update();
			}
		}

		if (SDLRenderer)
		{
			SDL_DestroyRenderer(SDLRenderer);
		}
		if (SDLWindow)
		{
			SDL_DestroyWindow(SDLWindow);
		}
	}

	return 0;
}
