#include "SelectCardAction.h"
#include "Game.h"

SelectCardAction::SelectCardAction(Card* _card, Player* _activePlayer) :
	card(_card), activePlayer(_activePlayer)
{
}

void SelectCardAction::execute(Game& _game)
{
	_game.SelectCard(card);
}

void SelectCardAction::undo(Game& _game)
{
	_game.UnselectCard();
}
