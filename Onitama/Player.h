#pragma once
#include "Piece.h" 
#include "Card.h" 

class Player
{
private:
	E_PLAYERCOLOR color;
	std::vector<Vector2> initStudentPositions;
	Vector2 initMasterPosition;

public:
	Player(E_PLAYERCOLOR _color);

	void SetInitPiecePositions();
	void InitPlayerPieces();

	inline E_PLAYERCOLOR GetColor() { return color; }

	std::vector<Piece*> PlayerPieces;
};

