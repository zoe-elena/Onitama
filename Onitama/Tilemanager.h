#pragma once
#include "Tile.h"
#include "Defines.h"

class TileManager
{
private:
	Tile tiles[BOARDSIZE][BOARDSIZE];

public:
	TileManager();

	void InitializeTiles();
	Tile* GetTile(const int _xIndex, const int _yIndex);
	bool IsInBounds(const int _xIndex, const int _yIndex) const;
	bool HasTemple(const int _xIndex, const int _yIndex) const;
	E_PLAYERCOLOR GetTempleColor(const int _xIndex, const int _yIndex) const;
	Vector2 GetClosestTile(int _xPosition, int _yPosition) const;
	void SetTilePiece(const int _xIndex, const int _yIndex, Piece* piece);
};

