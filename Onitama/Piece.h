#pragma once
#include "Vector2.h"
#include "Defines.h"

class Player;

class Piece
{
public:
	Piece();
	Piece(Player* _player, E_PIECETYPE _type, Vector2 _index);

	E_PLAYERCOLOR GetColor();
	bool isOnBoard();

	inline Vector2 GetIndex() const { return index; }
	inline void SetIndex(Vector2 _index) { index = _index; }
	inline bool IsCaptured() const { return isCaptured; }
	inline void SetCaptured(bool _isCaptured) { isCaptured = _isCaptured; }
	inline Player* GetOwner() const { return player; }
	inline int GetXIndex() const { return index.x; }
	inline int GetYIndex() const { return index.y; }
	inline E_PIECETYPE GetType() const { return type; }
	inline bool IsMaster() const { return type == E_PIECETYPE::master; }

private:
	Vector2 index;
	bool isCaptured = false;
	Player* player;
	E_PIECETYPE type;
};

