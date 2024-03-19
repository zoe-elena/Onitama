#pragma once
#include "Tile.h"
#include "Defines.h"

class Tilemanager
{
private:
	Tile tiles[BOARDSIZE][BOARDSIZE];

public:
	Tilemanager();

	void InitializeTiles();
	Tile* GetTile(const int _xIndex, const int _yIndex);
	bool IsInBounds(const int _xIndex, const int _yIndex) const;
	bool HasTemple(const int _xIndex, const int _yIndex) const;
	E_PLAYERCOLOR GetTempleColor(const int _xIndex, const int _yIndex) const;
};

