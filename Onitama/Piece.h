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

	Vector2 GetIndex() const { return index; }
	void SetIndex(Vector2 _index) { index = _index; }
	bool IsCaptured() const { return isCaptured; }
	void SetCaptured(bool _isCaptured) { isCaptured = _isCaptured; }
	const Player* GetOwner() const { return player; }
	int GetXIndex() const { return index.x; }
	int GetYIndex() const { return index.y; }
	E_PIECETYPE GetType() const { return type; }
	bool IsMaster() const { return type == E_PIECETYPE::master; }

private:
	Vector2 index;
	bool isCaptured = false;
	Player* player;
	E_PIECETYPE type;
};

