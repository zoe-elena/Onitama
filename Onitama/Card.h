#pragma once
#include <vector>
#include "SDL.h"
#include "Vector2.h"
#include "Defines.h"

class Player;

class Card
{
public:
	Card(Player* _player, E_CARDTYPE _cardType, E_CARDPOSITIONTYPE _cardPosition, const std::vector<Vector2> _moves);

	E_PLAYERCOLOR GetOwnerColor() const;

	inline Player* GetOwner() const { return owner; }
	inline void SetOwner(Player* _player) { owner = _player; }
	inline E_CARDPOSITIONTYPE GetPositionType() const { return cardPositionType; }
	inline void SetPositionType(E_CARDPOSITIONTYPE _cardPositionType) { cardPositionType = _cardPositionType; }
	inline std::vector<Vector2> GetMoves() const { return moves; }
	inline E_CARDTYPE GetCardType() const { return cardType; }

private:
	Player* owner;
	E_CARDPOSITIONTYPE cardPositionType;
	E_CARDTYPE cardType;
	std::vector<Vector2> moves;
};
