#pragma once
#include "Action.h"

class SelectCardAction : public Action
{
public:
	SelectCardAction(Card* _card, Player* _activePlayer);
	void execute(Game& _game) override;
	void undo(Game& _game) override;

private:
	Card* card;
	Player* activePlayer;
};
