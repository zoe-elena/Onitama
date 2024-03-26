#pragma once
#include "Vector2.h"
#include "Defines.h"
#include "Piece.h"

class Player;

class Tile
{
private:
	Vector2 index;
	Piece* piece = nullptr;

public:
	Tile();
	Tile(Vector2 _index);

	inline bool GetIsOccupied() const { return piece != nullptr; }
	inline Player* GetOccupyingPlayer() const { return piece->GetOwner(); }

	inline Piece* GetPiece() const { return piece; }
	inline void SetPiece(Piece* _piece) { piece = _piece; }

	inline int GetXIndex() const { return index.x; }
	inline int GetYIndex() const { return index.y; }
	inline Vector2 GetIndex() const { return index; }
};

