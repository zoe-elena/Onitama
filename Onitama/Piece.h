#pragma once
#include "Vector2.h"
#include "Defines.h"

class Player;

class Piece
{
private:
	Player* player;
	E_PIECETYPE type;
	Vector2 index;
	bool isCaptured = false;
	bool isHovered = false;

public:
	Piece();
	Piece(Player* _player, E_PIECETYPE _type, Vector2 _index);

	inline void SetIndex(int _xIndex, int _yIndex) { index = Vector2(_xIndex, _yIndex); }
	inline void SetIndex(Vector2 _index) { index = _index; }

	inline bool GetIsHovered() { return isHovered; }
	inline void SetIsHovered(bool _isHovered) { isHovered = _isHovered; }

	inline Player* GetOwnerPlayer() const { return player; }
	inline Vector2 GetIndex() const { return index; }
	inline int GetXIndex() const { return index.x; }
	inline int GetYIndex() const { return index.y; }
	inline E_PIECETYPE GetType() const { return type; }

	E_PLAYERCOLOR GetColor();
	bool isOnBoard();
};

