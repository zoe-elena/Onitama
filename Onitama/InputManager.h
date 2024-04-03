#pragma once
#include <SDL.h>
#include "Vector2.h"

class InputManager
{
public:
	InputManager();
	~InputManager();

	void PollEvents();

	inline Vector2 GetMousePosition() const { return mousePosition; }
	inline bool IsMouseButtonDown() const { return leftButtonDown; }
	inline bool IsRButtonDown() const { return rButtonDown; }
	inline bool IsArrowLeftButtonDown() const { return arrowLeftButtonDown; }

private:
	Vector2 mousePosition;
	SDL_Event event;
	bool leftButtonDown = false;
	bool rButtonDown = false;
	bool arrowLeftButtonDown = false;
};
