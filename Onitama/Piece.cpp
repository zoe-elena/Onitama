#include "Player.h"
#include "Piece.h"

Piece::Piece(Player* _player, E_PIECETYPE _type, Vector2 _position) : player(_player), type(_type), position(_position) { }

E_PLAYERCOLOR Piece::GetColor()
{
	return player->GetColor();
}

bool Piece::isOnBoard() {
	if (position.xPos == -1 && position.yPos == -1)
		return false;
	else
		return true;
}