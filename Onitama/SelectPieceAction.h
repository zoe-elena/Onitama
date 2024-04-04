#pragma once
#include "Action.h"
#include "SelectActionState.h"

class SelectPieceAction : public Action
{
public:
	SelectPieceAction(SelectActionState* _state, Player* _activePlayer);
	~SelectPieceAction();
	void execute(Game& _game) override;
	void undo(Game& _game) override;

private:
	SelectActionState* state;
	Player* activePlayer;
};
