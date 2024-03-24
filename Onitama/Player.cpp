#include "Player.h"
#include "Piece.h"
#include "Card.h" 

Player::Player(E_PLAYERCOLOR _color) : color(_color)
{
	if (color == E_PLAYERCOLOR::red)
	{
		SetInitPiecePositions(0);
		SetInitTemplePositions(0);
		SetInitCardPositions(TILEPADDING);
	}
	else if (color == E_PLAYERCOLOR::blue)
	{
		SetInitPiecePositions(4);
		SetInitTemplePositions(4);
		SetInitCardPositions(TILEPADDING * 4 + CARDHEIGHT + BOARDSIZE * TILESIZE + BOARDSIZE * TILEPADDING);
	}
}

void Player::SetInitPiecePositions(int _row)
{
	initStudentPositions.push_back(Vector2(0, _row));
	initStudentPositions.push_back(Vector2(1, _row));
	initMasterPosition = Vector2(2, _row);
	initStudentPositions.push_back(Vector2(3, _row));
	initStudentPositions.push_back(Vector2(4, _row));
}

void Player::SetInitTemplePositions(int _row)
{
	templePosition = Vector2(2, _row);
}

void Player::SetInitCardPositions(int _pixelHeight)
{
	leftCardSlotPosition = Vector2(SIDEPANELWIDTH + TILEPADDING, _pixelHeight);
	rightCardSlotPosition = Vector2(SIDEPANELWIDTH + CARDWIDTH + TILEPADDING * 3, _pixelHeight);
}

void Player::InitPieces()
{
	for (int u = 0; u < initStudentPositions.size(); u++) {
		PlayerPieces.push_back(new Piece(this, E_PIECETYPE::student, initStudentPositions[u]));
	}
	PlayerPieces.push_back(new Piece(this, E_PIECETYPE::master, initMasterPosition));
}

void Player::InitCards()
{

}
