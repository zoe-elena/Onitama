#pragma once
#include "Vector2.h"
#include "Defines.h"
#include "Piece.h"

class Tile
{
public:
	Tile() = default;
	Tile(Vector2 _index);

	Piece* GetOccupyingPiece() const { return occupyingPiece; }
	void SetOccupyingPiece(Piece* _occupyingPiece) { occupyingPiece = _occupyingPiece; }
	const bool IsOccupied() const { return occupyingPiece != nullptr; }
	const E_PLAYERCOLOR GetOwnerColor() const { return occupyingPiece->GetOwnerColor(); }
	const int GetXIndex() const { return index.x; }
	const int GetYIndex() const { return index.y; }
	const Vector2 GetIndex() const { return index; }

private:
	Vector2 index;
	Piece* occupyingPiece = nullptr;
};

