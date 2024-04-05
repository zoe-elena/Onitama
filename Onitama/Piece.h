#pragma once
#include "Vector2.h"
#include "Defines.h"

class Player;

class Piece
{
public:
	Piece();
	Piece(Player* _player, E_PIECETYPE _type, Vector2 _index);

	const bool isOnBoard() const;
	const E_PLAYERCOLOR GetColor() const;
	const Vector2 GetIndex() const { return index; }
	void SetIndex(Vector2 _index) { index = _index; }
	const bool IsCaptured() const { return isCaptured; }
	void SetCaptured(bool _isCaptured) { isCaptured = _isCaptured; }
	const Player* GetOwner() const { return player; }
	const int GetXIndex() const { return index.x; }
	const int GetYIndex() const { return index.y; }
	const E_PIECETYPE GetType() const { return type; }
	const bool IsMaster() const { return type == E_PIECETYPE::master; }

private:
	Vector2 index;
	bool isCaptured = false;
	Player* player;
	E_PIECETYPE type;
};

