#include "ActionStack.h"

void ActionStack::ExecuteAction(Action* action)
{
	stack.push(action);
	action->execute();
}

void ActionStack::UndoLastAction()
{
	if (stack.empty() == false)
	{
		Action* action = stack.top();
		action->undo();
		stack.pop();
		delete action;
	}
}
