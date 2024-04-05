#include "Piece.h"

Piece::Piece()
{
	playerColor = E_PLAYERCOLOR::none;
	type = E_PIECETYPE::none;
}

Piece::Piece(E_PLAYERCOLOR _playerColor, E_PIECETYPE _type, Vector2 _index) :
	playerColor(_playerColor), type(_type), index(_index)
{
}

const bool Piece::isOnBoard() const
{
	if (index.x == -1 && index.y == -1)
		return false;
	else
		return true;
}
