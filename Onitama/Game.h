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
	void MovePiece(Tile _selectedTile, Piece* _selectedPiece, Card* _selectedCard, Piece* _capturedPiece, Player* _activePlayer);
	void MovePieceBack(Tile _prevTile, Piece* _piece, Card* _selectedCard, Card* _prevSideCard, Piece* _capturedPiece, Player* _activePlayer);
	Card* GetSideCard() { return cardManager.GetSideCard(); }
	void UnselectCard() { selectedCard = nullptr; hoveredPiece = nullptr; }
	void UnselectPiece() { selectedPiece = nullptr; validMovesTileIndices.clear(); }

	const Player* GetPlayerRed() const { return &playerRed; }
	const Player* GetPlayerBlue() const { return &playerBlue; }
	Tile GetTile(const Vector2 _index) const { return tileManager.GetTile(_index); }
	bool HasQuit() const { return hasQuit; }
	bool DoRestart() const { return hasRestart; }
	std::vector<Vector2> GetValidMoves() const { return validMovesTileIndices; }
	Card* GetSelectedCard() const { return selectedCard; }
	bool IsActivePlayer(Player* _player) const { return activePlayer == _player; }
	Piece* GetHoveredPiece() const { return hoveredPiece; }
	Piece* GetSelectedPiece() const { return selectedPiece; }
	bool IsSelectedCard(Card* _card) const { return selectedCard == _card; }
	bool IsSelectedPiece(Piece* _piece) const { return selectedPiece == _piece; }
	bool IsHoveredPiece(Piece* _piece) const { return hoveredPiece == _piece; }
	bool IsPieceSelected() const { return selectedPiece != nullptr; }
	std::array<Card*, CARDS> GetAllCards() const { return cardManager.GetCards(); }
	std::array<Vector2, CARDSLOTS> GetAllCardPositions() const { return cardManager.GetCardPositions(); }
	std::map<E_CARDPOSITIONTYPE, Vector2> GetCardPositionMap() { return cardManager.GetCardPositionMap(); }

private:
	bool isWin = false;
	bool hasQuit = false;
	bool hasRestart = false;
	ActionStack actionStack;

	Player playerRed;
	Player playerBlue;
	Player* activePlayer = nullptr;
	Renderer renderer;
	TileManager tileManager;
	InputManager inputManager;
	CardManager cardManager;

	Piece* hoveredPiece = nullptr;
	Piece* selectedPiece = nullptr;
	Card* selectedCard = nullptr;
	std::vector<Vector2> validMovesTileIndices;

	void UpdateTilePointer();
	void DoTurn();
	void CheckForWin(Piece* _capturedPiece);
	void UnselectAll();
	void ResolveLeftMouseDown(Vector2 _mousePos);
	void TryHoverPiece(Vector2 _mousePos);
	bool TryMovePiece(Tile _tile);
	bool TrySelectPiece(Piece* _piece);
	bool IsValidMove(Vector2 _move);
	void NextPlayer(Player* _activePlayer);
};
