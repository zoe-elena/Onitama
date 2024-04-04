#pragma once
#include "Action.h"

class SelectPieceAction : public Action
{
public:
	SelectPieceAction(Piece* _piece, Player* _activePlayer);
	void execute(Game& _game) override;
	void undo(Game& _game) override;

private:
	Piece* piece;
	Player* activePlayer;
};
