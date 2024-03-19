#include "Tilemanager.h"
#include "Player.h"

Tilemanager::Tilemanager()
{
	InitializeTiles();
}

void Tilemanager::InitializeTiles()
{
	for (int y = 0; y < BOARDSIZE; y++) {
		for (int x = 0; x < BOARDSIZE; x++) {
			Temple* tempel = nullptr;
			if (x == TEMPLEREDX && y == TEMPLEREDY)
			{
				tempel = new Temple(red);
			}
			else if (x == TEMPLEBLUEX && y == TEMPLEBLUEY)
			{
				tempel = new Temple(blue);
			}
			tiles[x][y] = Tile(Vector2(x, y), tempel);
		}
	}
}

Tile* Tilemanager::GetTile(const int _xIndex, const int _yIndex)
{
	if (IsInBounds(_xIndex, _yIndex))
	{
		return &tiles[_xIndex][_yIndex];
	}
	else {
		return nullptr;
	}
}

bool Tilemanager::IsInBounds(const int _xIndex, const int _yIndex) const {
	if (_xIndex < BOARDSIZE)
		return true;
	if (_xIndex >= 0)
		return true;
	if (_yIndex < BOARDSIZE)
		return true;
	if (_yIndex >= 0)
		return true;

	return false;
}

bool Tilemanager::HasTemple(const int _xIndex, const int _yIndex) const
{
	return tiles[_xIndex][_yIndex].HasTemple();
}

E_PLAYERCOLOR Tilemanager::GetTempleColor(const int _xIndex, const int _yIndex) const
{
	return tiles[_xIndex][_yIndex].GetOccupyingPlayer()->GetColor();
}
