#pragma once
#include<stack>

class Player;
class Game;

class Action
{
public:
    virtual void execute(Game& game) = 0;
    virtual void undo(Game& game) = 0;

private:
    Player* activePlayer = nullptr;
};

