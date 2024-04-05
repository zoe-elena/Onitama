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

const Vector2 TileManager::GetClosestTile(const Vector2 _position) const
{
	float xTilePosition = (_position.x - SIDEPANELWIDTH - TILEPADDING / 2.0f) / (float)(TILESIZE + TILEPADDING);
	float yTilePosition = (_position.y - CARDPANELHEIGHT - TILEPADDING / 2.0f) / (float)(TILESIZE + TILEPADDING);

	int xIndex = xTilePosition < 0 ? static_cast<int>(xTilePosition - 1) : static_cast<int>(xTilePosition);
	int yIndex = yTilePosition < 0 ? static_cast<int>(yTilePosition - 1) : static_cast<int>(yTilePosition);

	if (IsInBounds(Vector2(xIndex, yIndex)) == false)
	{
		xIndex = yIndex = -1;
	}

	return Vector2(xIndex, yIndex);
}

std::vector<Vector2> TileManager::GetValidMoveTileIndices(std::vector<Vector2> _moves, Vector2 _pieceIndex, const Player* _activePlayer)
{
	std::vector<Vector2> validMoves;
	int playerSideModifier = _activePlayer->GetColor() == E_PLAYERCOLOR::blue ? 1 : -1;

	for (auto& move : _moves)
	{
		Tile possibleTile = GetMoveTile(_pieceIndex, move, playerSideModifier);
		if (IsInBounds(Vector2(possibleTile.GetXIndex(), (possibleTile.GetYIndex()))))
		{
			if (possibleTile.IsOccupied() == false || IsEnemyPlayerOnTile(possibleTile, _activePlayer))
			{
				validMoves.push_back(possibleTile.GetIndex());
			}
		}
	}

	return validMoves;
}

const Tile TileManager::GetMoveTile(Vector2 _pieceIndex, Vector2 _move, int _playerSideModifier)
{
	Vector2 moveTileIndex = _pieceIndex + (_move * _playerSideModifier);
	return GetTile(moveTileIndex);
}

const bool TileManager::IsEnemyPlayerOnTile(const Tile _tile, const Player* _activePlayer) const
{
	if (_tile.IsOccupied() == false)
	{
		return false;
	}

	if (_tile.GetOccupyingPlayer() != _activePlayer)
	{
		return true;
	}

	return false;
}

void TileManager::ClearTile(const Vector2 _index)
{
	tiles[_index.x][_index.y].SetOccupyingPiece(nullptr);
}

Piece* TileManager::TryCapturePiece(const Tile _tile)
{
	if (_tile.IsOccupied())
	{
		_tile.GetOccupyingPiece()->SetCaptured(true);
		return _tile.GetOccupyingPiece();
	}

	return nullptr;
}

const bool TileManager::IsInBounds(const Vector2 _index) const {
	if ((_index.x < BOARDSIZE)
		&& (_index.x >= 0)
		&& (_index.y < BOARDSIZE)
		&& (_index.y >= 0))
	{
		return true;
	}
	else
	{
		return false;
	}
}

const bool TileManager::IsInBounds(const Tile _tile) const
{
	return (_tile.GetXIndex() < BOARDSIZE)
		&& (_tile.GetXIndex() >= 0)
		&& (_tile.GetYIndex() < BOARDSIZE)
		&& (_tile.GetYIndex() >= 0);
}

const Tile TileManager::GetTile(const Vector2 _index) const
{
	if (IsInBounds(_index))
	{
		return tiles[_index.x][_index.y];
	}
	else {
		return Tile(Vector2(-1, -1));
	}
}

void TileManager::SetTilePiece(Piece* _piece)
{
	tiles[_piece->GetXIndex()][_piece->GetYIndex()].SetOccupyingPiece(_piece);
}
