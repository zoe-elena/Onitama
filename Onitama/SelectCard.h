#pragma once
#include "Action.h"

class SelectCard : public Action 
{
public:
    void execute(std::stack<Action*>& actionStack) override;
    void undo() override;
};

