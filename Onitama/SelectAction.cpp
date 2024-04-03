#include "SelectAction.h"
#include "Game.h"

SelectAction::SelectAction(Game* _game, SelectActionState* _state, Player* _activePlayer) :
	game(_game), state(_state), activePlayer(_activePlayer)
{
}

SelectAction::~SelectAction()
{
	delete(state);
}

void SelectAction::execute()
{
	Piece* nextPiece = state->nextPiece;
	Card* nextCard = state->nextCard;
	if (nextPiece)
	{
		game->SelectPiece(nextPiece);
	}
	else if (nextCard)
	{
		game->SelectCard(nextCard);
	}

	game->TrySetMoveTiles(nextCard, nextPiece, activePlayer);
}

void SelectAction::undo()
{

}
