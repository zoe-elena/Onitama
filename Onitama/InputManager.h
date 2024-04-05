#pragma once
#include <SDL.h>
#include "Vector2.h"

class InputManager
{
public:
	void PollEvents();

	Vector2 GetMousePosition() const { return mousePosition; }
	bool IsLeftMouseButtonPressed() const { return leftButtonDown; }
	bool IsRestartButtonPressed() const { return rButtonDown; }
	bool IsLeftArrowButtonPressed() const { return arrowLeftButtonDown; }
	bool IsQuitButtonPressed() const { return escButtonDown; }

private:
	Vector2 mousePosition;
	SDL_Event event;
	bool leftButtonDown = false;
	bool rButtonDown = false;
	bool arrowLeftButtonDown = false;
	bool escButtonDown = false;
};
