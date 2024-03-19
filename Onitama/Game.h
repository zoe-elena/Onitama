#pragma once
#include "Player.h"
#include "Renderer.h"
#include "Tilemanager.h"
#include "SDL.h"

class Game
{
private:
	Player* playerRed;
	Player* playerBlue;
	SDL_Renderer* SDLRenderer;
	Renderer* renderer;
	Tilemanager* tilemanager;
	SDL_bool hasQuit = SDL_FALSE;

public:
	Game(SDL_Renderer* _SDLRenderer);

	void InitGame(SDL_Renderer* _SDLRenderer);

	inline Player* GetPlayerRed() const { return playerRed; }
	inline Player* GetPlayerBlue() const { return playerBlue; }
	inline Tile* GetTile(const int _xIndex, const int _yIndex) const { return tilemanager->GetTile(_xIndex, _yIndex); }
	inline SDL_bool HasQuit() const { return hasQuit; }

	void Update();
};
