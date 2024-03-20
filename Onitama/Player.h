#pragma once
#include<vector>
#include "Piece.h" 
#include "Defines.h" 

class Player
{
private:
	E_PLAYERCOLOR color;
	Piece* hoveredPiece;
	std::vector<Vector2> InitStudentPositions;

public:
	Player(E_PLAYERCOLOR _color);

	void SetInitPiecePositions();
	void InitPlayerPieces();

	inline E_PLAYERCOLOR GetColor() { return color; }
	inline Piece* GetHoveredPiece() { return hoveredPiece; }
	inline void SetHoveredPiece(Piece* _hoveredPiece) {  hoveredPiece = _hoveredPiece; }

	std::vector<Piece*> PlayerPieces;
	Vector2 InitMasterPosition;
};

