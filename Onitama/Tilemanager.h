#pragma once
#include "Tile.h"
#include "Defines.h"
#include <vector>

class TileManager
{
private:
	Tile tiles[BOARDSIZE][BOARDSIZE];

public:
	TileManager();

	void InitializeTiles();
	Tile* GetTile(const int _xIndex, const int _yIndex);
	bool IsInBounds(const int _xIndex, const int _yIndex) const;
	Vector2 GetClosestTile(const int _xPosition, const int _yPosition) const;
	void SetTilePiece(const int _xIndex, const int _yIndex, Piece* piece);
	std::vector<Vector2> GetValidMoveTileIndices(std::vector<Vector2> _moves, Vector2 _pieceIndex, Player* _activePlayer);
	Tile* GetMoveTile(Vector2 _pieceIndex, Vector2 _move, int _playerSideModifier);
	bool IsEnemyPlayerOnTile(Tile* _tile, Player* _activePlayer);
};

