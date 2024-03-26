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
	InputManager();

	void PollEvents();
	inline Vector2 GetMousePosition() const { return mousePosition; }
	inline bool GetMouseButtonDown() const { return leftButtonDown; }
};
