#pragma once
#include "SDL.h"
#include "ActionStack.h"
#include "InputManager.h"
#include "TileManager.h"
#include "CardManager.h"
#include "Player.h"

class Game
{
public:
	Game(SDL_Renderer* _SDLRenderer);

	const bool DoQuit() const { return hasQuit; }
	const bool DoRestart() const { return hasRestart; }
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
	const Player* GetWinningPlayer() const { return winningPlayer; }
	const std::vector<Vector2> GetValidMoves() const { return validMovesTileIndices; }
	const Card* GetSelectedCard() const { return selectedCard; }
	const bool IsActivePlayer(const Player* _player) const { return activePlayer == _player; }
	const bool IsSelectedPiece(Piece* _piece) const { return selectedPiece == _piece; }
	const bool IsHoveredPiece(Piece* _piece) const { return hoveredPiece == _piece; }
	const bool IsPieceSelected() const { return selectedPiece != nullptr; }
	const bool IsWin() const { return isWin; }
	const std::array<Card*, CARDS> GetAllCards() const { return cardManager.GetCards(); }
	const std::map<E_CARDPOSITIONTYPE, Vector2> GetCardPositionMap() const { return cardManager.GetCardPositionMap(); }

private:
	bool isWin = false;
	bool hasQuit = false;
	bool hasRestart = false;

	ActionStack actionStack;
	InputManager inputManager;
	TileManager tileManager;
	CardManager cardManager;
	Player playerRed;
	Player playerBlue;

	Player* activePlayer = nullptr;
	Player* winningPlayer = nullptr;
	Piece* hoveredPiece = nullptr;
	Piece* selectedPiece = nullptr;
	Card* selectedCard = nullptr;
	std::vector<Vector2> validMovesTileIndices;

	void InitGame();
	void UpdateTilePointer();
	bool CheckForGameEnd();
	void DoTurn();
	void ResolveLeftMouseButtonPressed(Vector2 _mousePos);
	void TryHoverPiece(Vector2 _mousePos);
	bool TrySelectPiece(Piece* _piece);
	const bool IsValidMove(const Vector2 _move) const;
	const bool TryMovePiece(const Tile _selectedTile) const;
	const bool CheckForWin(const Piece* _capturedPiece) const;
	void DoWin();
	void NextPlayer(const Player* _activePlayer);
	void UnselectAll();
};
