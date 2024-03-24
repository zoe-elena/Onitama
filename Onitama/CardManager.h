#pragma once
#include <vector>
#include "Card.h"
#include "Defines.h"

class Player;

class CardManager
{
private:
	Card* cards[CARDS];

public:
	void InitCards();

	Card* GetCard(E_CARDTYPE _cardType);
	Card* GetCard(Vector2 _mousePos);
	std::vector<Vector2> GetCardMovement(E_CARDTYPE _cardType);
	Player* GetCardOwner(E_CARDTYPE _cardType);
};
