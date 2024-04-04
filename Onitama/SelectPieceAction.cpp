#include "SelectPieceAction.h"
#include "Game.h"

SelectPieceAction::SelectPieceAction(Piece* _piece, Player* _activePlayer) :
	piece(_piece), activePlayer(_activePlayer)
{
}

void SelectPieceAction::execute(Game& _game)
{
	_game.SelectPiece(piece);
}

void SelectPieceAction::undo(Game& _game)
{
	_game.UnselectPiece();
}
