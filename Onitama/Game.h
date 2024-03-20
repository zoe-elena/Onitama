#pragma once
#include "Player.h"
#include "Renderer.h"
#include "TileManager.h"
#include "InputManager.h"
#include "SDL.h"

class Game
{
private:
	Player* playerRed;
	Player* playerBlue;
	Player* activePlayer;
	SDL_Renderer* SDLRenderer;
	Renderer* renderer;
	TileManager* tileManager;
	InputManager* inputManager;
	SDL_bool hasQuit = SDL_FALSE;

public:
	Game(SDL_Renderer* _SDLRenderer);

	void InitGame(SDL_Renderer* _SDLRenderer);

	inline Player* GetPlayerRed() const { return playerRed; }
	inline Player* GetPlayerBlue() const { return playerBlue; }
	inline Tile* GetTile(const int _xIndex, const int _yIndex) const { return tileManager->GetTile(_xIndex, _yIndex); }
	inline SDL_bool HasQuit() const { return hasQuit; }

	void UpdateAllTiles();
	void DoTurn();
	void CheckHoverPiece(Vector2 _mouseIndex);

	void Update();
};
