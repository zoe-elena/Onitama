#pragma once
#include <SDL.h>
#include "Vector2.h"

class InputManager
{
public:
	void PollEvents();
	const Vector2 GetMousePosition() const { return mousePosition; }
	const bool IsLeftMouseButtonPressed() const { return leftButtonDown; }
	const bool IsRestartButtonPressed() const { return rButtonDown; }
	const bool IsLeftArrowButtonPressed() const { return arrowLeftButtonDown; }
	const bool IsQuitButtonPressed() const { return escButtonDown; }

private:
	SDL_Event event;
	Vector2 mousePosition;
	bool leftButtonDown = false;
	bool rButtonDown = false;
	bool arrowLeftButtonDown = false;
	bool escButtonDown = false;
};
