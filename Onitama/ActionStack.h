#pragma once
#include <stack>
#include "Action.h"

class Game;

class ActionStack
{
public:
	void ExecuteAction(Action* action);
	void UndoLastAction();

private:
	std::stack<Action*> stack;
};

