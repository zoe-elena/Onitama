#include <vector>
#include "CardManager.h"
#include "Player.h"

CardManager::CardManager()
{
	// TODO: Put this here to supress warning for missing initialization
	cards = {};
	sideCard = nullptr;
}

void CardManager::InitCards(Player* _playerRed, Player* _playerBlue)
{
	std::vector<Vector2> movesMantis{ Vector2(-1, -1), Vector2(1, -1), Vector2(0, 1) };
	std::vector<Vector2> movesDragon{ Vector2(-2, -1), Vector2(-1, 1), Vector2(1, 1), Vector2(2, -1) };
	std::vector<Vector2> movesOx{ Vector2(0, -1), Vector2(0, 1), Vector2(1, 0) };
	std::vector<Vector2> movesHorse{ Vector2(-1, 0), Vector2(0, -1), Vector2(0, 1) };
	std::vector<Vector2> movesRabbit{ Vector2(-1, 1), Vector2(1, -1), Vector2(2, 0) };


	cards[0] = new Card(E_CARDTYPE::ox, E_CARDPOSITIONTYPE::topLeft, movesOx);
	cards[1] = new Card(E_CARDTYPE::horse, E_CARDPOSITIONTYPE::topRight, movesHorse);
	cards[2] = new Card(E_CARDTYPE::mantis, E_CARDPOSITIONTYPE::bottomRight, movesMantis);
	cards[3] = new Card(E_CARDTYPE::dragon, E_CARDPOSITIONTYPE::bottomLeft, movesDragon);
	cards[4] = new Card(E_CARDTYPE::rabbit, E_CARDPOSITIONTYPE::sideLeft, movesRabbit);

	_playerRed->SetLeftCard(cards[0]);
	_playerRed->SetRightCard(cards[1]);
	_playerBlue->SetLeftCard(cards[2]);
	_playerBlue->SetRightCard(cards[3]);
	sideCard = cards[4];
	sideCard->Player = _playerRed;

	cardPositionMap.emplace(E_CARDPOSITIONTYPE::topLeft, Vector2(leftCardsX, topCardsY));
	cardPositionMap.emplace(E_CARDPOSITIONTYPE::topRight, Vector2(rightCardsX, topCardsY));
	cardPositionMap.emplace(E_CARDPOSITIONTYPE::sideRight, Vector2(sideCardRightX, sideCardY));
	cardPositionMap.emplace(E_CARDPOSITIONTYPE::bottomRight, Vector2(rightCardsX, bottomCardsY));
	cardPositionMap.emplace(E_CARDPOSITIONTYPE::bottomLeft, Vector2(leftCardsX, bottomCardsY));
	cardPositionMap.emplace(E_CARDPOSITIONTYPE::sideLeft, Vector2(sideCardLeftX, sideCardY));
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

	return nullptr;
}

Card* CardManager::GetCard(E_CARDPOSITIONTYPE _cardPositionType)
{
	for (size_t i = 0; i < sizeof(cards); i++)
	{
		if (cards[i]->GetCardPositionType() == _cardPositionType)
		{
			return cards[i];
		}
	}

	return nullptr;
}

E_CARDPOSITIONTYPE CardManager::CheckCardHover(E_PLAYERCOLOR _activePlayerColor, Vector2 _mousePos)
{
	if (_activePlayerColor == E_PLAYERCOLOR::red)
	{
		if (IsMouseHoveringOverCard(leftCardsX, topCardsY, _mousePos.x, _mousePos.y))
		{
			return E_CARDPOSITIONTYPE::topLeft;
		}
		else if (IsMouseHoveringOverCard(rightCardsX, topCardsY, _mousePos.x, _mousePos.y))
		{
			return E_CARDPOSITIONTYPE::topRight;
		}
	}
	else
	{
		if (IsMouseHoveringOverCard(leftCardsX, bottomCardsY, _mousePos.x, _mousePos.y))
		{
			return E_CARDPOSITIONTYPE::bottomLeft;
		}
		else if (IsMouseHoveringOverCard(rightCardsX, bottomCardsY, _mousePos.x, _mousePos.y))
		{
			return E_CARDPOSITIONTYPE::bottomRight;
		}
	}

	return E_CARDPOSITIONTYPE::none;
}

bool CardManager::IsMouseHoveringOverCard(int x, int y, int mouseX, int mouseY)
{
	return mouseX > x && mouseX < x + CARDWIDTH &&
		mouseY > y && mouseY < y + CARDHEIGHT;
}