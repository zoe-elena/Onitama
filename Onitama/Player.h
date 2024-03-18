#pragma once
#include<vector>
#include "Piece.h" 
#include "Defines.h" 

class Player
{
private:
	E_PLAYERCOLOR color;
public:
	Player(E_PLAYERCOLOR _color);

	void SetInitPiecePositions();
	void InitPlayerPieces();

	inline E_PLAYERCOLOR GetColor() { return color; }

	std::vector<Piece> PlayerPieces;
	std::vector<Vector2> InitStudentPositions;
	Vector2 InitMasterPosition;
};

