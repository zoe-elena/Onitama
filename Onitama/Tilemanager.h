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
	Tile* GetTile(const Vector2 _index);
	bool IsInBounds(const Vector2 _index) const;
	Vector2 GetClosestTile(const Vector2 _position) const;
	void SetTilePiece(const Vector2 _index, Piece* piece);
	std::vector<Vector2> GetValidMoveTileIndices(std::vector<Vector2> _moves, Vector2 _pieceIndex, Player* _activePlayer);
	Tile* GetMoveTile(Vector2 _pieceIndex, Vector2 _move, int _playerSideModifier);
	bool IsEnemyPlayerOnTile(Tile* _tile, Player* _activePlayer);
};

