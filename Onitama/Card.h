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
	std::vector<Vector2> moves;

public:
	Player* player;
	E_CARDPOSITIONTYPE cardPositionType;

	Card(Player* _player, E_CARDTYPE _cardType, E_CARDPOSITIONTYPE _cardPosition, const std::vector<Vector2> _moves);
	
	inline std::vector<Vector2> GetMoves() const { return moves; }
	inline E_CARDTYPE GetCardType() const { return cardType; }
};
