#include "Player.h"
#include "Piece.h"

Piece::Piece()
{
}

Piece::Piece(Player* _player, E_PIECETYPE _type, Vector2 _index) : player(_player), type(_type), index(_index) { }

E_PLAYERCOLOR Piece::GetColor()
{
	return player->GetColor();
}

bool Piece::isOnBoard() {
	if (index.x == -1 && index.y == -1)
		return false;
	else
		return true;
}