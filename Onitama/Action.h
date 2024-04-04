#pragma once
#include<stack>
#include "Player.h"

class Game;

class Action
{
public:
    virtual void execute(Game& game) = 0;
    virtual void undo(Game& game) = 0;
};

