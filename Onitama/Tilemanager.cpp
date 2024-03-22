#include "TileManager.h"
#include "Player.h"

TileManager::TileManager()
{
	InitializeTiles();
}

void TileManager::InitializeTiles()
{
	for (int y = 0; y < BOARDSIZE; y++) {
		for (int x = 0; x < BOARDSIZE; x++) {
			Temple* temple = nullptr;
			if (x == TEMPLEREDX && y == TEMPLEREDY)
			{
				temple = new Temple(E_PLAYERCOLOR::red);
			}
			else if (x == TEMPLEBLUEX && y == TEMPLEBLUEY)
			{
				temple = new Temple(E_PLAYERCOLOR::blue);
			}
			tiles[x][y] = Tile(Vector2(x, y), temple);
		}
	}
}

Tile* TileManager::GetTile(const int _xIndex, const int _yIndex)
{
	if (IsInBounds(_xIndex, _yIndex))
	{
		return &tiles[_xIndex][_yIndex];
	}
	else {
		return nullptr;
	}
}

bool TileManager::IsInBounds(const int _xIndex, const int _yIndex) const {
	if ((_xIndex < BOARDSIZE) && (_xIndex >= 0) && (_yIndex < BOARDSIZE) && (_yIndex >= 0))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool TileManager::HasTemple(const int _xIndex, const int _yIndex) const
{
	return tiles[_xIndex][_yIndex].HasTemple();
}

E_PLAYERCOLOR TileManager::GetTempleColor(const int _xIndex, const int _yIndex) const
{
	return tiles[_xIndex][_yIndex].GetOccupyingPlayer()->GetColor();
}

Vector2 TileManager::GetClosestTile(const int _xPosition, const int _yPosition) const
{
	float xTilePosition = (_xPosition - SIDEPANELWIDTH - TILEPADDING / 2.0f) / (float)(TILESIZE + TILEPADDING);
	float yTilePosition = (_yPosition - CARDPANELHEIGHT - TILEPADDING / 2.0f) / (float)(TILESIZE + TILEPADDING);

	int xIndex = xTilePosition < 0 ? xTilePosition - 1 : xTilePosition;
	int yIndex = yTilePosition < 0 ? yTilePosition - 1 : yTilePosition;

	if (!IsInBounds(xIndex, yIndex))
	{
		xIndex = yIndex = -1;
	}

	return Vector2(xIndex, yIndex);
}

void TileManager::SetTilePiece(const int _xIndex, const int _yIndex, Piece* piece)
{
	tiles[_xIndex][_yIndex].SetPiece(piece);
}
