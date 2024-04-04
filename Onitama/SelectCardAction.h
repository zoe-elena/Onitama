#pragma once
#include "Action.h"
#include "SelectActionState.h"

class SelectCardAction : public Action
{
public:
	SelectCardAction(SelectActionState* _state, Player* _activePlayer);
	~SelectCardAction();
	void execute(Game& _game) override;
	void undo(Game& _game) override;

private:
	SelectActionState* state;
	Player* activePlayer;
};
