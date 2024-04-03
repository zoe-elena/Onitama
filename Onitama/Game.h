#pragma once
#include <iostream>
#include "SDL.h"
#include "ActionStack.h"
#include "Player.h"
#include "Renderer.h"
#include "TileManager.h"
#include "InputManager.h"
#include "CardManager.h"

class Game
{
public:
	Game(SDL_Renderer* _SDLRenderer);

	void InitGame();
	void Update();
	void SelectCard(Card* _card);
	void SelectPiece(Piece* _piece);
	bool TrySetMoveTiles(Card* _card, Piece* _piece, Player* _activePlayer);

	inline Player* GetPlayerRed() const { return playerRed; }
	inline Player* GetPlayerBlue() const { return playerBlue; }
	inline Tile GetTile(const Vector2 _index) const { return tileManager->GetTile(_index); }
	inline SDL_bool HasQuit() const { return hasQuit; }
	inline Piece* GetHoveredPiece() const { return hoveredPiece; }
	inline Piece* GetSelectedPiece() const { return selectedPiece; }
	inline std::vector<Vector2> GetValidMoves() const { return validMovesTileIndices; }
	inline Card* GetSelectedCard() const { return selectedCard; }
	inline bool IsActivePlayer(Player* _player) const { return activePlayer == _player; }
	inline bool IsSelectedCard(Card* _card) const { return selectedCard == _card; }
	inline bool IsPieceSelected() const { return selectedPiece; }
	inline std::array<Card*, CARDS> GetAllCards() const { return cardManager->GetCards(); }
	inline std::array<Vector2, CARDSLOTS> GetAllCardPositions() const { return cardManager->GetCardPositions(); }
	inline std::map<E_CARDPOSITIONTYPE, Vector2> GetCardPositionMap() { return cardManager->GetCardPositionMap(); }

private:
	bool isWin = false;
	SDL_bool hasQuit = SDL_FALSE;
	ActionStack actionStack;

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
	std::vector<Vector2> validMovesTileIndices;

	void RestartGame();
	void UpdateAllTiles();
	void DoTurn();
	void NextTurn();
	void CheckForWin(Piece* _capturedPiece);
	void UnselectAll();
	void ResolveLeftMouseDown(Vector2 _mousePos);
	void TryHoverPiece(Vector2 _mousePos);
	bool TryMovePiece(Tile _tile);
	void MovePiece(Tile _tile, Piece* _capturedPiece);
	bool IsValidMove(Vector2 _move);
	bool TrySelectPiece(Piece* _piece);
};
