#pragma once
#include <vector>
#include "SDL.h"
#include "Defines.h"
#include "Vector2.h"
#include "Player.h"

class Card
{
public:
	Card(Player* _player, E_CARDTYPE _cardType, E_CARDPOSITIONTYPE _cardPosition, const std::vector<Vector2> _moves);

	const E_PLAYERCOLOR GetOwnerColor() const;
	const Player* GetOwner() const { return owner; }
	void SetOwner(Player* _player) { owner = _player; }
	const E_CARDPOSITIONTYPE GetPositionType() const { return cardPositionType; }
	void SetPositionType(E_CARDPOSITIONTYPE _cardPositionType) { cardPositionType = _cardPositionType; }
	const std::vector<Vector2> GetMoves() const { return moves; }
	const E_CARDTYPE GetCardType() const { return cardType; }

private:
	Player* owner;
	E_CARDPOSITIONTYPE cardPositionType;
	E_CARDTYPE cardType;
	std::vector<Vector2> moves;
};
