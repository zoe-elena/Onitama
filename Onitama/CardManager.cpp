#include <vector>
#include <random>
#include "CardManager.h"
#include "Player.h"

CardManager::CardManager(Player* _playerRed, Player* _playerBlue, Player* _activeplayer)
{
	playerRed = _playerRed;
	playerBlue = _playerBlue;
	MapCardPositions();
	MapPlayerCards();
	InitCards(_activeplayer);
}

CardManager::~CardManager()
{
	for (size_t i = 0; i < cards.size(); i++)
	{
		delete(cards[i]);
	}
}

void CardManager::MapCardPositions()
{
	cardPositionMap.emplace(E_CARDPOSITIONTYPE::topLeft, Vector2(leftCardsX, topCardsY));
	cardPositionMap.emplace(E_CARDPOSITIONTYPE::topRight, Vector2(rightCardsX, topCardsY));
	cardPositionMap.emplace(E_CARDPOSITIONTYPE::sideRight, Vector2(sideCardRightX, sideCardY));
	cardPositionMap.emplace(E_CARDPOSITIONTYPE::bottomRight, Vector2(rightCardsX, bottomCardsY));
	cardPositionMap.emplace(E_CARDPOSITIONTYPE::bottomLeft, Vector2(leftCardsX, bottomCardsY));
	cardPositionMap.emplace(E_CARDPOSITIONTYPE::sideLeft, Vector2(sideCardLeftX, sideCardY));
}

void CardManager::MapPlayerCards()
{
	playerCardMap.emplace(E_CARDPOSITIONTYPE::topLeft, playerRed);
	playerCardMap.emplace(E_CARDPOSITIONTYPE::topRight, playerRed);
	playerCardMap.emplace(E_CARDPOSITIONTYPE::sideRight, playerBlue);
	playerCardMap.emplace(E_CARDPOSITIONTYPE::bottomRight, playerBlue);
	playerCardMap.emplace(E_CARDPOSITIONTYPE::bottomLeft, playerBlue);
	playerCardMap.emplace(E_CARDPOSITIONTYPE::sideLeft, playerRed);
}

void CardManager::InitCards(Player* _activeplayer)
{
	// Shuffle the Cards
	std::array<E_CARDPOSITIONTYPE, CARDS> randomCardPositions =
	{ E_CARDPOSITIONTYPE::topLeft,
	E_CARDPOSITIONTYPE::topRight,
	E_CARDPOSITIONTYPE::bottomRight,
	E_CARDPOSITIONTYPE::bottomLeft };
	randomCardPositions[CARDS - 1] = _activeplayer == playerRed ? E_CARDPOSITIONTYPE::sideLeft : E_CARDPOSITIONTYPE::sideRight;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::shuffle(std::begin(randomCardPositions), std::end(randomCardPositions), gen);

	cards[0] = new Card(playerCardMap.find(randomCardPositions[0])->second, E_CARDTYPE::ox, randomCardPositions[0], movesOx);
	cards[1] = new Card(playerCardMap.find(randomCardPositions[1])->second, E_CARDTYPE::horse, randomCardPositions[1], movesHorse);
	cards[2] = new Card(playerCardMap.find(randomCardPositions[2])->second, E_CARDTYPE::mantis, randomCardPositions[2], movesMantis);
	cards[3] = new Card(playerCardMap.find(randomCardPositions[3])->second, E_CARDTYPE::dragon, randomCardPositions[3], movesDragon);
	cards[4] = new Card(playerCardMap.find(randomCardPositions[4])->second, E_CARDTYPE::rabbit, randomCardPositions[4], movesRabbit);

	for (size_t i = 0; i < cards.size(); i++)
	{
		if (cards[i]->cardPositionType == E_CARDPOSITIONTYPE::sideLeft ||
			cards[i]->cardPositionType == E_CARDPOSITIONTYPE::sideRight)
		{
			sideCard = cards[i];
		}
	}

	sideCard->player = playerCardMap.find(sideCard->cardPositionType)->second;
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
		if (cards[i]->cardPositionType == _cardPositionType)
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

void CardManager::MoveCardsAlong(Player* _activePlayer, Card* _selectedCard)
{
	sideCard->cardPositionType = _selectedCard->cardPositionType;

	if (_activePlayer->GetColor() == E_PLAYERCOLOR::red)
	{
		_selectedCard->cardPositionType = E_CARDPOSITIONTYPE::sideRight;
		_selectedCard->player = playerBlue;
	}
	else if (_activePlayer->GetColor() == E_PLAYERCOLOR::blue)
	{
		_selectedCard->cardPositionType = E_CARDPOSITIONTYPE::sideLeft;
		_selectedCard->player = playerRed;
	}

	sideCard = _selectedCard;
}
