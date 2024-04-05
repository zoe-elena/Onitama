#pragma once
#include <array>
#include "Vector2.h"
#include "Defines.h"

class Piece;
class Card;

class Player
{
public:
	Player(E_PLAYERCOLOR _color);
	~Player();

	const std::array<Piece*, PIECECOUNT> GetPlayerPieces() const { return playerPieces; }
	Piece* GetPlayerPiece(const int _index) const { return playerPieces[_index]; }
	const E_PLAYERCOLOR GetColor() const { return color; }
	const Vector2 GetTemplePosition() const { return templePosition; }

private:
	std::array<Piece*, PIECECOUNT> playerPieces;
	const E_PLAYERCOLOR color;
	std::array<Vector2, STUDENTS> initStudentPositions;
	Vector2 initMasterPosition;
	Vector2 templePosition;

	void InitPlayer();
	void SetInitPiecePositions(const int _row);
	void SetInitTemplePositions(const int _row);
};

