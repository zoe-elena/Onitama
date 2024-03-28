#pragma once
#include "Tile.h"
#include "Defines.h"
#include <vector>
#include <array>

class TileManager
{
private:
	std::array<std::array<Tile, BOARDSIZE>, BOARDSIZE> tiles;

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
	void ClearTile(Vector2 _index);
	void CapturePiece(Vector2 _index);
};

