#pragma once
#include <vector>
#include "SDL.h"
#include "Vector2.h"
#include "Defines.h"

class Player;

class Card
{
private:
	E_CARDTYPE cardType;
	E_CARDPOSITIONTYPE cardPosition;
	std::vector<Vector2> moves;

public:
	Player* Player;
	Card(E_CARDTYPE _cardType, E_CARDPOSITIONTYPE _cardPosition, const std::vector<Vector2> _moves);
	
	inline std::vector<Vector2> GetMoves() const { return moves; }
	inline E_CARDTYPE GetCardType() const { return cardType; }
	inline E_CARDPOSITIONTYPE GetCardPositionType() const { return cardPosition; }
};
