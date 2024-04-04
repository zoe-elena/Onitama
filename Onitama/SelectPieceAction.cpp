#include "SelectPieceAction.h"
#include "Game.h"

SelectPieceAction::SelectPieceAction(SelectActionState* _state, Player* _activePlayer) :
	state(_state), activePlayer(_activePlayer)
{
}

SelectPieceAction::~SelectPieceAction()
{
	delete(state);
}

void SelectPieceAction::execute(Game& _game)
{
	_game.SelectPiece(state->nextPiece);
}

void SelectPieceAction::undo(Game& _game)
{
	_game.UnselectPiece();
}
