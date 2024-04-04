#pragma once
#include <vector>
#include "SDL.h"
#include "Vector2.h"
#include "Defines.h"
#include "Player.h"

class Card
{
public:
	Card(Player* _player, E_CARDTYPE _cardType, E_CARDPOSITIONTYPE _cardPosition, const std::vector<Vector2> _moves);

	E_PLAYERCOLOR GetOwnerColor() const;

	Player* GetOwner() const { return owner; }
	void SetOwner(Player* _player) { owner = _player; }
	E_CARDPOSITIONTYPE GetPositionType() const { return cardPositionType; }
	void SetPositionType(E_CARDPOSITIONTYPE _cardPositionType) { cardPositionType = _cardPositionType; }
	std::vector<Vector2> GetMoves() const { return moves; }
	E_CARDTYPE GetCardType() const { return cardType; }

private:
	Player* owner;
	E_CARDPOSITIONTYPE cardPositionType;
	E_CARDTYPE cardType;
	std::vector<Vector2> moves;
};
