#include "Piece.h"

Piece::Piece(Vector2 _position) {
	position = _position;
}

Piece::Piece() {
	position = Vector2(-1, -1);
}

bool Piece::isOnBoard() {
	if (position.xPos == -1 && position.yPos == -1)
		return false;
	else
		return true;
}