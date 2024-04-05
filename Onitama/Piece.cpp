#include "Player.h"
#include "Piece.h"

Piece::Piece()
{
	player = nullptr;
	type = E_PIECETYPE::none;
}

Piece::Piece(Player* _player, E_PIECETYPE _type, Vector2 _index) :
	player(_player), type(_type), index(_index)
{
}

const bool Piece::isOnBoard() const
{
	if (index.x == -1 && index.y == -1)
		return false;
	else
		return true;
}

const E_PLAYERCOLOR Piece::GetColor() const
{
	return player->GetColor();
}
