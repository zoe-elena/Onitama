#pragma once
#include "Action.h"
#include "Tile.h"
#include "Piece.h"
#include "Card.h"

class MoveAction : public Action
{
public:
	MoveAction(Tile _selectedTile, Piece* _piece, Card* _card, Piece* _capturedPiece, Player* _lastActivePlayer);
	void execute(Game& _game) override;
	void undo(Game& _game) override;

private:
	Tile selectedTile;
	Piece* piece = nullptr;
	Card* card = nullptr;
	Piece* capturedPiece = nullptr;
	Player* lastActivePlayer = nullptr;

	Tile prevTile;
	Card* prevSideCard = nullptr;
};
