#pragma once
#include "Vector2.h"
#include "Defines.h"
#include "Piece.h"

class Player;

class Tile
{
private:
	Vector2 index;

public:
	Piece* OccupyingPiece = nullptr;
	Tile();
	Tile(Vector2 _index);

	inline bool IsOccupied() const { return OccupyingPiece; }
	inline Player* GetOccupyingPlayer() const { return OccupyingPiece->GetOwner(); }

	inline int GetXIndex() const { return index.x; }
	inline int GetYIndex() const { return index.y; }
	inline Vector2 GetIndex() const { return index; }
};

