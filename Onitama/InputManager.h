#pragma once
#include <SDL.h>
#include "Vector2.h"

class InputManager
{
public:
	InputManager();
	~InputManager();

	void PollEvents();

	Vector2 GetMousePosition() const { return mousePosition; }
	bool IsMouseButtonDown() const { return leftButtonDown; }
	bool IsRButtonDown() const { return rButtonDown; }
	bool IsArrowLeftButtonDown() const { return arrowLeftButtonDown; }
	bool IsEscButtonDown() const { return escButtonDown; }

private:
	Vector2 mousePosition;
	SDL_Event event;
	bool leftButtonDown = false;
	bool rButtonDown = false;
	bool arrowLeftButtonDown = false;
	bool escButtonDown = false;
};
