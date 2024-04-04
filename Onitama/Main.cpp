#include <chrono>
#include <thread>
#include "SDL.h"
#include "Game.h"
#include "Renderer.h"

void PrintFPS(int& _startTime, int& _fpsCounter);

int main(int argc, char* argv[])
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		return 1;
	}

	SDL_Window* SDLWindow = nullptr;
	SDL_Renderer* sdlRenderer = nullptr;
	if (SDL_CreateWindowAndRenderer(WINDOWWIDTHSIZE, WINDOWLENGTHSIZE, 0, &SDLWindow, &sdlRenderer) == -1)
	{
		return 1;
	}

	bool restart = false;
	int frameStartTime = SDL_GetTicks();
	int fpsCounter = 0;
	do	{
		Game game(sdlRenderer);
		Renderer renderer(sdlRenderer);
		while (game.HasQuit() == false && game.DoRestart() == false)
		{
			game.Update();
			renderer.DrawGame(game);

			PrintFPS(frameStartTime, fpsCounter);
			std::this_thread::sleep_for(std::chrono::milliseconds(50));
		}
		restart = game.DoRestart();
	} while (restart);

	if (sdlRenderer)
	{
		SDL_DestroyRenderer(sdlRenderer);
	}
	if (SDLWindow)
	{
		SDL_DestroyWindow(SDLWindow);
	}

	return 0;
}

// Prints FPS every Second
void PrintFPS(int& _startTime, int& _fpsCounter)
{
	_fpsCounter++;

	if (SDL_GetTicks() - _startTime >= 1000)
	{
		_startTime = SDL_GetTicks();
		std::cout << "fps:" << _fpsCounter << std::endl;
		_fpsCounter = 0;
	}
}
