#include "Player.h"
#include "Piece.h"
#include "Tile.h"

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

void Piece::Move(Tile* _tile)
{
	index = _tile->GetIndex();
	_tile->SetPiece(this);
}
