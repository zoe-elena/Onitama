#pragma once
#include <stack>
#include "Action.h"

class Game;

class ActionStack
{
public:
	void ExecuteAction(Action* action, Game& _game);
	void UndoLastAction(Game& _game);

private:
	std::stack<Action*> stack;
};

