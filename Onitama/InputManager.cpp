#include "InputManager.h"

void InputManager::PollEvents() {
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_MOUSEMOTION:
			mousePosition = Vector2(event.motion.x, event.motion.y);
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT) {
				leftButtonDown = true;
			}
			break;
		case SDL_MOUSEBUTTONUP:
			if (event.button.button == SDL_BUTTON_LEFT) {
				leftButtonDown = false;
			}
			break;
		}
	}
}
