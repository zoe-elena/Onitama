#pragma once
#include "Vector2.h"
#include<vector>
#include "Defines.h"
#include "SDL.h"

class Player;

class Card
{
private:
	E_CARDTYPE cardType;
	std::vector<Vector2> moves;
	Player* player;

public:
	inline std::vector<Vector2> GetMoves() const { return moves; }
	inline E_CARDTYPE GetCardType() const { return cardType; }
	inline Player* GetOwner() const { return player; }
	inline void SetOwner(Player* _player) { player = _player; }

	Card(E_CARDTYPE _cardType, const std::vector<Vector2> _moves);
};
