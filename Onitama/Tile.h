#pragma once
#include "Vector2.h"
#include "Defines.h"
#include "Piece.h"
#include "Temple.h"

class Player;

class Tile
{
private:
	Temple* temple;
	Vector2 index;
	Piece* piece = nullptr;

public:
	Tile();
	Tile(Vector2 _index, Temple* _tempel);

	inline bool GetIsOccupied() const { return piece != nullptr; }
	inline Player* GetOccupyingPlayer() const { return piece->GetOwnerPlayer(); }

	inline Piece* GetPiece() const { return piece; }
	inline void SetPiece(Piece* _piece) { piece = _piece; }

	inline bool HasTemple() const { return temple; }
	inline Temple* GetTemple() const { return temple; }

	inline int GetXIndex() const { return index.x; }
	inline int GetYIndex() const { return index.y; }
	inline Vector2 GetIndex() const { return index; }
};

