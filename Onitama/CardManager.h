#pragma once
#include <vector>
#include "Card.h"
#include "Defines.h"

class Player;

class CardManager
{
private:
	Card* cards[CARDS];
	Card* sideCard;

public:
	CardManager();

	void InitCards(Player* _playerRed, Player* _playerBlue);

	Card* GetCard(E_CARDTYPE _cardType);
};
