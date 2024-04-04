#include "InputManager.h"

void InputManager::PollEvents()
{
	leftButtonDown = false;
	rButtonDown = false;
	arrowLeftButtonDown = false;
	escButtonDown = false;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_MOUSEMOTION:
			mousePosition = Vector2(event.motion.x, event.motion.y);
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				leftButtonDown = true;
			}
			break;
		case SDL_KEYDOWN:
			if (event.button.button == SDL_SCANCODE_ESCAPE)
			{
				escButtonDown = true;
			}
			if (event.button.button == SDL_SCANCODE_R)
			{
				rButtonDown = true;
			}
			else if (event.button.button == SDL_SCANCODE_LEFT)
			{
				arrowLeftButtonDown = true;
			}
			break;
		}
	}
}
