#include "CardManager.h"
#include "Player.h"

CardManager::CardManager()
{
}

void CardManager::InitCards(Player* _playerRed, Player* _playerBlue)
{
	std::vector<Vector2> movesDebug{ Vector2(0, 1), Vector2(-2, 1), Vector2(1, -1), Vector2(0, -2) };

	// Player Red Cards
	cards[0] = new Card(E_CARDTYPE::debug, E_CARDPOSITIONS::lowLeft, movesDebug);
	_playerRed->SetLeftCard(cards[0]);
	cards[1] = new Card(E_CARDTYPE::debug, E_CARDPOSITIONS::lowRight, movesDebug);
	_playerRed->SetRightCard(cards[1]);

	// Player Blue Cards
	cards[2] = new Card(E_CARDTYPE::debug, E_CARDPOSITIONS::topLeft, movesDebug);
	_playerBlue->SetLeftCard(cards[2]);
	cards[3] = new Card(E_CARDTYPE::debug, E_CARDPOSITIONS::topRight, movesDebug);
	_playerBlue->SetRightCard(cards[3]);

	// Side Card
	cards[4] = new Card(E_CARDTYPE::debug, E_CARDPOSITIONS::sideLeft, movesDebug);
	sideCard = cards[4];
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