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

	void InitPlayer();

	std::array<Piece*, PIECECOUNT> GetPlayerPieces() { return playerPieces; }
	Piece* GetPlayerPiece(int _index) const { return playerPieces[_index]; }
	const E_PLAYERCOLOR GetColor() const { return color; }
	const Vector2 GetTemplePosition() const { return templePosition; }

private:
	std::array<Piece*, PIECECOUNT> playerPieces;
	const E_PLAYERCOLOR color;
	std::array<Vector2, STUDENTS> initStudentPositions;
	Vector2 initMasterPosition;
	Vector2 templePosition;
	Vector2 leftCardSlotPosition;
	Vector2 rightCardSlotPosition;

	void SetInitPiecePositions(int _row);
	void SetInitTemplePositions(int _row);
};

