#pragma once
#include <vector>
#include <array>
#include "Defines.h"
#include "Tile.h"

class TileManager
{
public:
	TileManager();

	void InitializeTiles();
	const Vector2 GetClosestTile(const Vector2 _position) const;
	std::vector<Vector2> GetValidMoveTileIndices(const std::vector<Vector2> _moves, Vector2 _pieceIndex, const Player* _activePlayer);
	const Tile GetMoveTile(Vector2 _pieceIndex, Vector2 _move, int _playerSideModifier);
	const bool IsEnemyPlayerOnTile(const Tile _tile, const Player* _activePlayer) const;
	void ClearTile(const Vector2 _index);
	Piece* TryCapturePiece(const Tile _tile); 
	const bool IsInBounds(const Vector2 _index) const;
	const bool IsInBounds(const Tile _tile) const;
	const Tile GetTile(const Vector2 _index) const;
	void SetTilePiece(Piece* _piece);

private:
	std::array<std::array<Tile, BOARDSIZE>, BOARDSIZE> tiles;
};

