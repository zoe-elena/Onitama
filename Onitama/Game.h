#pragma once
#include "Player.h"
#include "Renderer.h"
#include "TileManager.h"
#include "InputManager.h"
#include "CardManager.h"
#include "SDL.h"
#include <iostream>
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
	std::vector<Vector2> validMoves;

	SDL_bool hasQuit = SDL_FALSE;

	bool TrySetMoveTiles(Piece* _piece);

public:
	Game(SDL_Renderer* _SDLRenderer);

	void InitGame(SDL_Renderer* _SDLRenderer);

	inline Player* GetPlayerRed() const { return playerRed; }
	inline Player* GetPlayerBlue() const { return playerBlue; }
	inline Tile* GetTile(const int _xIndex, const int _yIndex) const { return tileManager->GetTile(_xIndex, _yIndex); }
	inline SDL_bool HasQuit() const { return hasQuit; }
	inline Piece* GetHoveredPiece() const { return hoveredPiece; }
	inline Piece* GetSelectedPiece() const { return selectedPiece; }
	inline std::vector<Vector2> GetMoveTiles() const { return validMoves; }
	inline Card* GetSelectedCard() const { return selectedCard; }
	inline bool IsActivePlayer(Player* _player) const { return activePlayer == _player; }
	inline bool IsSelectedCard(Card* _card) const { return selectedCard == _card; }
	inline void UnselectAll() { selectedCard = nullptr; selectedPiece = nullptr; }


	Vector2 GetMoveTile(Piece* _piece, Vector2 _move) const;

	void UpdateAllTiles();
	void DoTurn();
	void ResolveLeftMouseDown(Vector2 _mousePos);
	void TryHoverPiece(Vector2 _mousePos);
	bool TryMovePiece(Tile* _tile);
	bool TrySelectPiece(Tile* _tile);
	void SelectPiece(Piece* _piece);
	bool IsValidMove(Vector2 _move);
	void Update();
};
