#include "TileManager.h"
#include "Player.h"

TileManager::TileManager()
{
	InitializeTiles();
}

void TileManager::InitializeTiles()
{
	for (int y = 0; y < BOARDSIZE; y++)
	{
		for (int x = 0; x < BOARDSIZE; x++)
		{
			tiles[x][y] = Tile(Vector2(x, y));
		}
	}
}

Tile* TileManager::GetTile(const Vector2 _index)
{
	if (IsInBounds(_index))
	{
		return &tiles[_index.x][_index.y];
	}
	else {
		return nullptr;
	}
}

bool TileManager::IsInBounds(const Vector2 _index) const {
	if ((_index.x < BOARDSIZE) && (_index.x >= 0) && (_index.y < BOARDSIZE) && (_index.y >= 0))
	{
		return true;
	}
	else
	{
		return false;
	}
}

Vector2 TileManager::GetClosestTile(const Vector2 _position) const
{
	float xTilePosition = (_position.x - SIDEPANELWIDTH - TILEPADDING / 2.0f) / (float)(TILESIZE + TILEPADDING);
	float yTilePosition = (_position.y - CARDPANELHEIGHT - TILEPADDING / 2.0f) / (float)(TILESIZE + TILEPADDING);

	int xIndex = xTilePosition < 0 ? xTilePosition - 1 : xTilePosition;
	int yIndex = yTilePosition < 0 ? yTilePosition - 1 : yTilePosition;

	if (!IsInBounds(Vector2(xIndex, yIndex)))
	{
		xIndex = yIndex = -1;
	}

	return Vector2(xIndex, yIndex);
}

void TileManager::SetTilePiece(const Vector2 _index, Piece* piece)
{
	tiles[_index.x][_index.y].OccupyingPiece = piece;
}

std::vector<Vector2> TileManager::GetValidMoveTileIndices(std::vector<Vector2> _moves, Vector2 _pieceIndex, Player* _activePlayer)
{
	std::vector<Vector2> validMoves;
	int playerSideModifier = _activePlayer->GetColor() == E_PLAYERCOLOR::blue ? 1 : -1;

	for (size_t i = 0; i < _moves.size(); i++)
	{
		Tile* possibleTile = GetMoveTile(_pieceIndex, _moves[i], playerSideModifier);
		if (possibleTile)
		{
			if (possibleTile->IsOccupied() == false || IsEnemyPlayerOnTile(possibleTile, _activePlayer))
			{
				validMoves.push_back(possibleTile->GetIndex());
			}
		}
	}

	return validMoves;
}

Tile* TileManager::GetMoveTile(Vector2 _pieceIndex, Vector2 _move, int _playerSideModifier)
{
	Vector2 moveTileIndex = _pieceIndex + (_move * _playerSideModifier);
	return GetTile(moveTileIndex);
}

bool TileManager::IsEnemyPlayerOnTile(Tile* _tile, Player* _activePlayer)
{
	if (_tile->IsOccupied() == false)
	{
		return false;
	}

	if (_tile->GetOccupyingPlayer() != _activePlayer)
	{
		return true;
	}

	return false;
}

void TileManager::ClearTile(Vector2 _index)
{
	tiles[_index.x][_index.y].OccupyingPiece = nullptr;
}

void TileManager::CapturePiece(Vector2 _index)
{
	tiles[_index.x][_index.y].OccupyingPiece->isCaptured = true;
}
