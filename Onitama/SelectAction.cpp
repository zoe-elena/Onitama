#include "SelectAction.h"
#include "Game.h"

SelectAction::SelectAction(SelectActionState* _state, Player* _activePlayer) :
	state(_state), activePlayer(_activePlayer)
{
}

SelectAction::~SelectAction()
{
	delete(state);
}

void SelectAction::execute(Game& _game)
{
	Piece* nextPiece = state->nextPiece;
	Card* nextCard = state->nextCard;
	if (nextPiece)
	{
		_game.SelectPiece(nextPiece);
	}
	else if (nextCard)
	{
		_game.SelectCard(nextCard);
	}

	_game.TrySetMoveTiles(nextCard, nextPiece, activePlayer);
}

void SelectAction::undo(Game& _game)
{

}
