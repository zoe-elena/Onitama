#include "MoveAction.h"
#include "Game.h"

MoveAction::MoveAction(Tile _selectedTile, Piece* _piece, Card* _card, Piece* _capturedPiece, Player* _lastActivePlayer) :
	selectedTile(_selectedTile), piece(_piece), card(_card), capturedPiece(_capturedPiece), lastActivePlayer(_lastActivePlayer)
{
}

void MoveAction::execute(Game& _game)
{
	prevTile = piece->GetIndex();
	prevSideCard = _game.GetSideCard();
	_game.MovePiece(selectedTile, piece, card, capturedPiece, lastActivePlayer);
}

void MoveAction::undo(Game& _game)
{
	_game.MovePieceBack(prevTile, piece, card, prevSideCard, capturedPiece, lastActivePlayer);
}
