#include <iostream>
#include "SDL.h"
#include "Board.h"
#include "Color.h"
#include "Defines.h"

using namespace std;

int main(int argc, char* argv[])
{
	if (SDL_Init(SDL_INIT_VIDEO) == 0)
	{
		SDL_Window* window = NULL;
		SDL_Renderer* renderer = NULL;

		if (SDL_CreateWindowAndRenderer(WINDOWWIDTHSIZE, WINDOWLENGTHSIZE, 0, &window, &renderer) == 0)
		{
			SDL_bool done = SDL_FALSE;
			Board* board = new Board();
			board->InitBoard(renderer);

			while (!done)
			{
				SDL_Event event;

				while (SDL_PollEvent(&event))
				{
					if (event.type == SDL_QUIT)
					{
						done = SDL_TRUE;
					}
				}
			}
		}

		if (renderer)
		{
			SDL_DestroyRenderer(renderer);
		}
		if (window)
		{
			SDL_DestroyWindow(window);
		}
	}

	return 0;
}