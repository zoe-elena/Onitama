#pragma once
#include<vector>
#include "Card.h"
#include "Player.h"
#include "Defines.h"

class CardManager
{
private:
	Card* cards[CARDS];

public:
	void InitCards();

	Card* GetCard(E_CARDTYPE _cardType);
	std::vector<Vector2> GetCardMovement(E_CARDTYPE _cardType);
	Player* GetCardOwner(E_CARDTYPE _cardType);
};
