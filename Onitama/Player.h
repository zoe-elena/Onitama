#pragma once
#include <vector>
#include "Vector2.h"
#include "Defines.h"

class Piece;
class Card;

class Player
{
private:
	E_PLAYERCOLOR color;
	std::vector<Vector2> initStudentPositions;
	Vector2 initMasterPosition;
	Vector2 templePosition;
	Card* leftCard;
	Card* rightCard;
	Vector2 leftCardSlotPosition;
	Vector2 rightCardSlotPosition;

public:
	Player(E_PLAYERCOLOR _color);

	void SetInitPiecePositions(int _row);
	void SetInitTemplePositions(int _row);
	void SetInitCardPositions(int _pixelHeight);
	void InitPieces();
	void InitCards();

	inline E_PLAYERCOLOR GetColor() { return color; }
	inline Vector2 GetTemplePosition() { return templePosition; }
	inline Vector2 GetLeftCardSlotPosition() { return leftCardSlotPosition; }
	inline Vector2 GetRightCardSlotPosition() { return rightCardSlotPosition; }

	std::vector<Piece*> PlayerPieces;
};

