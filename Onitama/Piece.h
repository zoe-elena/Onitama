#pragma once
#include "Vector2.h"
#include "Defines.h"

class Player;
class Tile;

class Piece
{
private:
	Player* player;
	E_PIECETYPE type;
	Vector2 index;
	bool isCaptured = false;

public:
	Piece();
	Piece(Player* _player, E_PIECETYPE _type, Vector2 _index);

	inline void SetIndex(int _xIndex, int _yIndex) { index = Vector2(_xIndex, _yIndex); }
	inline Player* GetOwner() const { return player; }
	inline Vector2 GetIndex() const { return index; }
	inline int GetXIndex() const { return index.x; }
	inline int GetYIndex() const { return index.y; }
	inline E_PIECETYPE GetType() const { return type; }

	E_PLAYERCOLOR GetColor();
	bool isOnBoard();
	void Move(Tile* _tile);
};

