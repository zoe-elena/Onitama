#pragma once
#include "Vector2.h"
#include "Defines.h"

class Player;

class Piece
{
private:
	Player* player;
	E_PIECETYPE type;
	Vector2 position;
	bool isCaptured = false;

public:
	Piece(Player* _player, E_PIECETYPE _type, Vector2 _position);

	inline void SetPosition(int _xPosition, int _yPosition) { position = Vector2(_xPosition, _yPosition); }
	inline void SetPosition(Vector2 _position) { position = _position; }

	inline Vector2 GetPosition() const { return position; }
	inline int GetXPos() const { return position.xPos; }
	inline int GetYPos() const { return position.yPos; }
	inline E_PIECETYPE GetType() const { return type; }

	E_PLAYERCOLOR GetColor();
	bool isOnBoard();
};

