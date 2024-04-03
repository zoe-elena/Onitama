#pragma once
#include<stack>

class Player;
class Game;

class Action
{
public:
    virtual void execute() = 0;
    virtual void undo() = 0;

private:
    Player* activePlayer;
};

