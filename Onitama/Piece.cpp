#include "Player.h"
#include "Piece.h"

Piece::Piece()
{
	player = nullptr;
	type = E_PIECETYPE::none;
}

Piece::Piece(Player* _player, E_PIECETYPE _type, Vector2 _index) : player(_player), type(_type), Index(_index) { }

E_PLAYERCOLOR Piece::GetColor()
{
	return player->GetColor();
}

bool Piece::isOnBoard() {
	if (Index.x == -1 && Index.y == -1)
		return false;
	else
		return true;
}
