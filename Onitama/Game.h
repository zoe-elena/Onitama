#pragma once
#include "Player.h"
#include "SDL.h"

class Game
{
private:
	Player* playerRed;
	Player* playerBlue;
	SDL_Renderer* renderer;
public:
	Game();

	inline Player* GetPlayerRed() const { return playerRed; }
	inline Player* GetPlayerBlue() const { return playerBlue; }

	void InitGame(SDL_Renderer* _renderer, SDL_Window* _window);
};

