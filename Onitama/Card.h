#pragma once
#include "Vector2.h"
#include <vector>
#include "Defines.h"
#include "SDL.h"

class Player;

class Card
{
private:
	E_CARDTYPE cardType;
	E_CARDPOSITIONS cardPosition;
	std::vector<Vector2> moves;

public:
	Player* Player;
	Card(E_CARDTYPE _cardType, E_CARDPOSITIONS _cardPosition, const std::vector<Vector2> _moves);
	
	inline std::vector<Vector2> GetMoves() const { return moves; }
	inline E_CARDTYPE GetCardType() const { return cardType; }
	inline E_CARDPOSITIONS GetCardPosition() const { return cardPosition; }
};
