#pragma once
#include "Vector2.h"
#include "Defines.h"

class Piece
{
public:
	Piece();
	Piece(E_PLAYERCOLOR _playerColor, E_PIECETYPE _type, Vector2 _index);

	const bool isOnBoard() const;
	const Vector2 GetIndex() const { return index; }
	void SetIndex(const Vector2 _index) { index = _index; }
	const bool IsCaptured() const { return isCaptured; }
	void SetCaptured(const bool _isCaptured) { isCaptured = _isCaptured; }
	const E_PLAYERCOLOR GetOwnerColor() const { return playerColor; }
	const int GetXIndex() const { return index.x; }
	const int GetYIndex() const { return index.y; }
	const E_PIECETYPE GetType() const { return type; }
	const bool IsMaster() const { return type == E_PIECETYPE::master; }

private:
	Vector2 index;
	bool isCaptured = false;
	E_PLAYERCOLOR playerColor;
	E_PIECETYPE type;
};

