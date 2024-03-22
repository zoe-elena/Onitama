#pragma once
#include "Player.h"
#include "Renderer.h"
#include "TileManager.h"
#include "InputManager.h"
#include "CardManager.h"
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
	CardManager* cardManager;

	Piece* hoveredPiece;
	Piece* selectedPiece;
	Card* selectedCard;

	SDL_bool hasQuit = SDL_FALSE;

public:
	Game(SDL_Renderer* _SDLRenderer);

	void InitGame(SDL_Renderer* _SDLRenderer);

	inline Player* GetPlayerRed() const { return playerRed; }
	inline Player* GetPlayerBlue() const { return playerBlue; }
	inline Tile* GetTile(const int _xIndex, const int _yIndex) const { return tileManager->GetTile(_xIndex, _yIndex); }
	inline SDL_bool HasQuit() const { return hasQuit; }
	inline Piece* GetHoveredPiece() const { return hoveredPiece; }
	inline Piece* GetSelectedPiece() const { return selectedPiece; }
	inline Card* GetSelectedCard() const { return selectedCard; }

	std::vector<Vector2> GetPossibleMoveTiles() const;
	Vector2 GetTileFromMove(Vector2 _move) const;

	void UpdateAllTiles();
	void DoTurn();
	void CheckHoverSelectPiece(Vector2 _mouseIndex, bool _leftMouseButtonDown);
	void Update();
};
