#pragma once
#include "Action.h"
#include "SelectActionState.h"

class SelectAction : public Action
{
public:
	SelectAction(Game* _game, SelectActionState* _state, Player* _activePlayer);
	~SelectAction();
	void execute() override;
	void undo() override;
	inline void SetGame(Game* _game) { game = _game; }
	inline Game* GetGame() { return game; }

private:
	Game* game;
	SelectActionState* state;
	Player* activePlayer;
};
