#pragma once
#include <SDL.h>
#include "Vector2.h"

class InputManager
{
private:
	Vector2 mousePosition;
	SDL_Event event;
	bool leftButtonDown = false;

public:
	void PollEvents();
	inline Vector2 GetMousePosition() { return mousePosition; }
	inline bool GetMouseButtonDown() { return leftButtonDown; }
};
