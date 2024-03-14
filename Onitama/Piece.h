#pragma once
#include "Vector2.h"

class Piece
{
private:
	Vector2 position;
	bool isAlive = true;

public:
	Piece();
	Piece(Vector2 _position);

	inline void SetPosition(int _xPosition, int _yPosition) { position = Vector2(_xPosition, _yPosition); }
	inline void SetPosition(Vector2 _position) { position = _position; }

	inline Vector2 GetPosition() const { return position; }
	inline int GetXPos() const { return position.xPos; }
	inline int GetYPos() const { return position.yPos; }

	bool isOnBoard();
};

