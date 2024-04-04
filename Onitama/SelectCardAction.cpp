#include "SelectCardAction.h"
#include "Game.h"

SelectCardAction::SelectCardAction(SelectActionState* _state, Player* _activePlayer) :
	state(_state), activePlayer(_activePlayer)
{
}

SelectCardAction::~SelectCardAction()
{
	delete(state);
}

void SelectCardAction::execute(Game& _game)
{
	_game.SelectCard(state->nextCard);
	_game.TrySetMoveTiles(state->nextCard, state->prevPiece, activePlayer);
}

void SelectCardAction::undo(Game& _game)
{
	_game.UnselectCard();
}
