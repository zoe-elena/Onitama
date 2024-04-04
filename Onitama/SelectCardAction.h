#pragma once
#include "Action.h"

class SelectCardAction : public Action
{
public:
	SelectCardAction(Card* _card, Piece* _piece, Player* _activePlayer);
	void execute(Game& _game) override;
	void undo(Game& _game) override;

private:
	Card* card;
	Piece* piece;
	Player* activePlayer;
};
