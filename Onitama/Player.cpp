#include "Player.h"
#include "Piece.h"
#include "Card.h" 

Player::Player(E_PLAYERCOLOR _color) : color(_color)
{
	if (color == E_PLAYERCOLOR::red)
	{
		SetInitPiecePositions(0);
		SetInitTemplePositions(0);
	}
	else if (color == E_PLAYERCOLOR::blue)
	{
		SetInitPiecePositions(4);
		SetInitTemplePositions(4);
	}

	InitPlayer();
}

Player::~Player()
{
	for (auto& playerPiece : playerPieces)
	{
		delete(playerPiece);
	}
}

void Player::InitPlayer()
{
	for (size_t i = 0; i < STUDENTS; i++)
	{
		playerPieces[i] = new Piece(this, E_PIECETYPE::student, initStudentPositions[i]);
	}
	playerPieces.back() = new Piece(this, E_PIECETYPE::master, initMasterPosition);
}

void Player::SetInitPiecePositions(const int _row)
{
	initStudentPositions[0] = Vector2(0, _row);
	initStudentPositions[1] = Vector2(1, _row);
	initMasterPosition = Vector2(2, _row);
	initStudentPositions[2] = Vector2(3, _row);
	initStudentPositions[3] = Vector2(4, _row);
}

void Player::SetInitTemplePositions(const int _row)
{
	templePosition = Vector2(2, _row);
}
