#pragma once
#include<stack>

class Action
{
public:
    virtual void execute(std::stack<Action*>& actionStack) = 0;
    virtual void undo() = 0;
};

