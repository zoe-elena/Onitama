#include "InputManager.h"

InputManager::InputManager()
{
}

void InputManager::PollEvents()
{
	leftButtonDown = false;

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
		case SDL_MOUSEBUTTONUP:
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				leftButtonDown = false;
			}
			break;
		}
	}
}
