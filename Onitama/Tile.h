#pragma once
#include "Vector2.h"
#include "Defines.h"
#include "Piece.h"

class Player;

class Tile
{
public:
	Tile();
	Tile(Vector2 _index);

	inline Piece* GetOccupyingPiece() const { return occupyingPiece; }
	inline void SetOccupyingPiece(Piece* _occupyingPiece) { occupyingPiece = _occupyingPiece; }
	inline bool IsOccupied() const { return occupyingPiece; }
	inline Player* GetOccupyingPlayer() const { return occupyingPiece->GetOwner(); }
	inline int GetXIndex() const { return index.x; }
	inline int GetYIndex() const { return index.y; }
	inline Vector2 GetIndex() const { return index; }


private:
	Vector2 index;
	Piece* occupyingPiece = nullptr;
};

