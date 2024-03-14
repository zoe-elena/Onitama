#include "Player.h"

Player::Player(E_PLAYERCOLOR _color)
{
	color = _color;
	SetInitStudentPositions();
}

void Player::SetInitStudentPositions()
{
	switch (color)
	{
	case red:
		InitStudentPositions.push_back(Vector2(0, 0));
		InitStudentPositions.push_back(Vector2(1, 0));
		InitMasterPosition = Vector2(2, 0);
		InitStudentPositions.push_back(Vector2(3, 0));
		InitStudentPositions.push_back(Vector2(4, 0));
		break;
	case blue:
		InitStudentPositions.push_back(Vector2(0, 4));
		InitStudentPositions.push_back(Vector2(1, 4));
		InitMasterPosition = Vector2(2, 4);
		InitStudentPositions.push_back(Vector2(3, 4));
		InitStudentPositions.push_back(Vector2(4, 4));
		break;
	default:
		InitStudentPositions.push_back(Vector2(-1, -1));
		InitStudentPositions.push_back(Vector2(-1, -1));
		InitMasterPosition = Vector2(-1, -1);
		InitStudentPositions.push_back(Vector2(-1, -1));
		InitStudentPositions.push_back(Vector2(-1, -1));
		break;
	}
}

