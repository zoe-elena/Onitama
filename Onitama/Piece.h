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
	bool isCaptured = false;

public:
	Vector2 Index;
	Piece();
	Piece(Player* _player, E_PIECETYPE _type, Vector2 _index);

	inline Player* GetOwner() const { return player; }
	inline int GetXIndex() const { return Index.x; }
	inline int GetYIndex() const { return Index.y; }
	inline E_PIECETYPE GetType() const { return type; }

	E_PLAYERCOLOR GetColor();
	bool isOnBoard();
	void Move(Tile* _tile);
};

