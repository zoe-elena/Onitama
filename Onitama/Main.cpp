#include <chrono>
#include <thread>
#include "SDL.h"
#include "Game.h"

int main(int argc, char* argv[])
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		return 1;
	}

	SDL_Window* SDLWindow = nullptr;
	SDL_Renderer* SDLRenderer = nullptr;

	if (SDL_CreateWindowAndRenderer(WINDOWWIDTHSIZE, WINDOWLENGTHSIZE, 0, &SDLWindow, &SDLRenderer) == -1)
	{
		return 1;
	}


	bool restart = false;
	do
	{
		Game game(SDLRenderer);
		while (game.HasQuit() == false && game.DoRestart() == false)
		{
			game.Update();

			// Significantly reduces CPU load
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}
		restart = game.DoRestart();
	} while (restart);

	if (SDLRenderer)
	{
		SDL_DestroyRenderer(SDLRenderer);
	}
	if (SDLWindow)
	{
		SDL_DestroyWindow(SDLWindow);
	}

	return 0;
}
