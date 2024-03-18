#pragma once
#include "Player.h"
#include "Renderer.h"
#include "SDL.h"

class Game
{
private:
	Renderer* renderer;
	Player* playerRed;
	Player* playerBlue;
	SDL_Renderer* SDLRenderer;
	SDL_bool hasQuit = SDL_FALSE;

public:
	Game();

	void InitGame(SDL_Renderer* _SDLRenderer);

	inline Player* GetPlayerRed() const { return playerRed; }
	inline Player* GetPlayerBlue() const { return playerBlue; }
	inline SDL_bool HasQuit() const { return hasQuit; }

	void Update();
};
