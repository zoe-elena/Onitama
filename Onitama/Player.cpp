#include "Player.h"

Player::Player(E_PLAYERCOLOR _color) : color(_color)
{
	SetInitPiecePositions();
}

void Player::SetInitPiecePositions()
{
	switch (color)
	{
	case E_PLAYERCOLOR::red:
		initStudentPositions.push_back(Vector2(0, 0));
		initStudentPositions.push_back(Vector2(1, 0));
		initMasterPosition = Vector2(2, 0);
		initStudentPositions.push_back(Vector2(3, 0));
		initStudentPositions.push_back(Vector2(4, 0));
		break;
	case E_PLAYERCOLOR::blue:
		initStudentPositions.push_back(Vector2(0, 4));
		initStudentPositions.push_back(Vector2(1, 4));
		initMasterPosition = Vector2(2, 4);
		initStudentPositions.push_back(Vector2(3, 4));
		initStudentPositions.push_back(Vector2(4, 4));
		break;
	default:
		initStudentPositions.push_back(Vector2(-1, -1));
		initStudentPositions.push_back(Vector2(-1, -1));
		initMasterPosition = Vector2(-1, -1);
		initStudentPositions.push_back(Vector2(-1, -1));
		initStudentPositions.push_back(Vector2(-1, -1));
		break;
	}
}

void Player::InitPlayerPieces()
{
	for (int u = 0; u < initStudentPositions.size(); u++) {
		PlayerPieces.push_back(new Piece(this, E_PIECETYPE::student, initStudentPositions[u]));
	}
	PlayerPieces.push_back(new Piece(this, E_PIECETYPE::master, initMasterPosition));
}
