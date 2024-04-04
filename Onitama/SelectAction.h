#pragma once
#include "Action.h"
#include "SelectActionState.h"

class SelectAction : public Action
{
public:
	SelectAction(SelectActionState* _state, Player* _activePlayer);
	~SelectAction();
	void execute(Game& _game) override;
	void undo(Game& _game) override;

private:
	SelectActionState* state;
	Player* activePlayer;
};
