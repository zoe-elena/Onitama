#include "CardManager.h"
#include "Player.h"

CardManager::CardManager()
{
	for (size_t i = 0; i < sizeof(cards); i++)
	{
		cards[i] = nullptr;
	}
	sideCard = nullptr;
}

void CardManager::InitCards(Player* _playerRed, Player* _playerBlue)
{
	std::vector<Vector2> movesMantis{ Vector2(-1, -1), Vector2(1, -1), Vector2(-1, 0) };
	std::vector<Vector2> movesDragon{ Vector2(-2, -1), Vector2(-1, 1), Vector2(-1, 1), Vector2(2, -1) };
	std::vector<Vector2> movesOx{ Vector2(0, -1), Vector2(0, 1), Vector2(1, 0) };
	std::vector<Vector2> movesHorse{ Vector2(-1, 0), Vector2(0, -1), Vector2(0, 1) };
	std::vector<Vector2> movesRabbit{ Vector2(-1, 1), Vector2(1, -1), Vector2(2, 0) };

	cards[2] = new Card(E_CARDTYPE::mantis, E_CARDPOSITIONS::lowLeft, movesMantis);
	cards[3] = new Card(E_CARDTYPE::dragon, E_CARDPOSITIONS::lowRight, movesDragon);
	cards[0] = new Card(E_CARDTYPE::ox, E_CARDPOSITIONS::topLeft, movesOx);
	cards[1] = new Card(E_CARDTYPE::horse, E_CARDPOSITIONS::topRight, movesHorse);

	_playerRed->SetLeftCard(cards[0]);
	_playerRed->SetRightCard(cards[1]);
	_playerBlue->SetLeftCard(cards[2]); 
	_playerBlue->SetRightCard(cards[3]);

	// Side Card
	cards[4] = new Card(E_CARDTYPE::rabbit, E_CARDPOSITIONS::sideLeft, movesRabbit);
	sideCard = cards[4];
}

Card* CardManager::GetCard(E_CARDTYPE _cardType)
{
	for (size_t i = 0; i < sizeof(cards); i++)
	{
		if (cards[i]->GetCardType() == _cardType)
		{
			return cards[i];
		}
	}
}