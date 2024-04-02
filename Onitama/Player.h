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

	inline std::array<Piece*, PIECECOUNT> GetPlayerPieces() { return playerPieces; }
	inline Piece* GetPlayerPiece(int _index) { return playerPieces[_index]; }
	inline E_PLAYERCOLOR GetColor() { return color; }
	inline Vector2 GetTemplePosition() { return templePosition; }

private:
	std::array<Piece*, PIECECOUNT> playerPieces;
	E_PLAYERCOLOR color;
	std::array<Vector2, STUDENTS> initStudentPositions;
	Vector2 initMasterPosition;
	Vector2 templePosition;
	Card* leftCard;
	Card* rightCard;
	Vector2 leftCardSlotPosition;
	Vector2 rightCardSlotPosition;

	void SetInitPiecePositions(int _row);
	void SetInitTemplePositions(int _row);
	void SetInitCardPositions(int _pixelHeight);
};

