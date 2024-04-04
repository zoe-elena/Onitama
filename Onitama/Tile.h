#pragma once
#include "Vector2.h"
#include "Defines.h"
#include "Piece.h"

class Tile
{
public:
	Tile();
	Tile(Vector2 _index);

	Piece* GetOccupyingPiece() const { return occupyingPiece; }
	void SetOccupyingPiece(Piece* _occupyingPiece) { occupyingPiece = _occupyingPiece; }
	bool IsOccupied() const { return occupyingPiece != nullptr; }
	const Player* GetOccupyingPlayer() const { return occupyingPiece->GetOwner(); }
	int GetXIndex() const { return index.x; }
	int GetYIndex() const { return index.y; }
	Vector2 GetIndex() const { return index; }

private:
	Vector2 index;
	Piece* occupyingPiece = nullptr;
};

