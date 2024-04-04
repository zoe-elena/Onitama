#include "ActionStack.h"

void ActionStack::ExecuteAction(Action* action, Game& _game)
{
	stack.push(action);
	action->execute(_game);
}

void ActionStack::UndoLastAction(Game& _game)
{
	if (stack.empty() == false)
	{
		Action* action = stack.top();
		action->undo(_game);
		stack.pop();
		delete action;
	}
}
