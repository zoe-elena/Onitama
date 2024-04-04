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
	for (size_t i = 0; i < playerPieces.size(); i++)
	{
		delete(playerPieces[i]);
	}
}

void Player::SetInitPiecePositions(int _row)
{
	initStudentPositions[0] = Vector2(0, _row);
	initStudentPositions[1] = Vector2(1, _row);
	initMasterPosition = Vector2(2, _row);
	initStudentPositions[2] = Vector2(3, _row);
	initStudentPositions[3] = Vector2(4, _row);
}

void Player::SetInitTemplePositions(int _row)
{
	templePosition = Vector2(2, _row);
}

void Player::InitPlayer()
{
	leftCard = nullptr;
	rightCard = nullptr;

	for (size_t u = 0; u < initStudentPositions.size(); u++) {
		playerPieces[u] = new Piece(this, E_PIECETYPE::student, initStudentPositions[u]);
	}
	playerPieces[playerPieces.size() - 1] = new Piece(this, E_PIECETYPE::master, initMasterPosition);
}
