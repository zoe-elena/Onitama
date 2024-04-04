#pragma once
class Card;
class Piece;

struct SelectActionState
{
public:
	Piece* prevPiece;
	Piece* nextPiece;
	Card* prevCard;
	Card* nextCard;

	SelectActionState(Piece* _prevPiece, Piece* _nextPiece, Card* _prevCard, Card* _nextCard) :
		prevPiece(_prevPiece), nextPiece(_nextPiece), prevCard(_prevCard), nextCard(_nextCard) {}
};