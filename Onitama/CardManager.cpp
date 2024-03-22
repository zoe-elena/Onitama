#include "CardManager.h"

void CardManager::InitCards()
{
	std::vector<Vector2> movesDebug{ Vector2(1, 1), Vector2(-1, 1), Vector2(0, -1) };
	cards[0] = new Card(E_CARDTYPE::debug, movesDebug);
}

Card* CardManager::GetCard(E_CARDTYPE _cardType)
{
	for (size_t i = 0; i < CARDS; i++)
	{
		if (cards[i]->GetCardType() == _cardType)
		{
			return cards[i];
		}
	}
}

std::vector<Vector2> CardManager::GetCardMovement(E_CARDTYPE _cardType)
{
	for (size_t i = 0; i < CARDS; i++)
	{
		if (cards[i]->GetCardType() == _cardType)
		{
			return cards[i]->GetMoves();
		}
	}
}

Player* CardManager::GetCardOwner(E_CARDTYPE _cardType)
{
	for (size_t i = 0; i < CARDS; i++)
	{
		if (cards[i]->GetCardType() == _cardType)
		{
			return cards[i]->GetOwner();
		}
	}
}
