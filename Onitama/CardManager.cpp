#include <vector>
#include <random>
#include "CardManager.h"

CardManager::CardManager(Player* _playerRed, Player* _playerBlue)
{
	playerRed = _playerRed;
	playerBlue = _playerBlue;
	MapCardPositions();
	MapPlayerCards();
}

CardManager::~CardManager()
{
	for (auto& card : cards)
	{
		delete(card);
	}
}

void CardManager::InitCards(const Player* _activeplayer)
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

	for (auto& card : cards)
	{
		if (card->GetPositionType() == E_CARDPOSITIONTYPE::sideLeft ||
			card->GetPositionType() == E_CARDPOSITIONTYPE::sideRight)
		{
			sideCard = card;
		}
	}

	sideCard->SetOwner(playerCardMap.find(sideCard->GetPositionType())->second);
}

void CardManager::MapCardPositions()
{
	cardPositionMap.emplace(E_CARDPOSITIONTYPE::topLeft, Vector2(LEFTCARDX, TOPCARDSY));
	cardPositionMap.emplace(E_CARDPOSITIONTYPE::topRight, Vector2(RIGHTCARDX, TOPCARDSY));
	cardPositionMap.emplace(E_CARDPOSITIONTYPE::sideRight, Vector2(SIDECARDRIGHTX, SIDECARDY));
	cardPositionMap.emplace(E_CARDPOSITIONTYPE::bottomRight, Vector2(RIGHTCARDX, BOTTOMCARDSY));
	cardPositionMap.emplace(E_CARDPOSITIONTYPE::bottomLeft, Vector2(LEFTCARDX, BOTTOMCARDSY));
	cardPositionMap.emplace(E_CARDPOSITIONTYPE::sideLeft, Vector2(SIDECARDLEFTX, SIDECARDY));
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

const E_CARDPOSITIONTYPE CardManager::CheckCardHover(const E_PLAYERCOLOR _activePlayerColor, const Vector2 _mousePos) const
{
	if (_activePlayerColor == E_PLAYERCOLOR::red)
	{
		if (IsMouseHoveringOverCard(LEFTCARDX, TOPCARDSY, _mousePos.x, _mousePos.y))
		{
			return E_CARDPOSITIONTYPE::topLeft;
		}
		else if (IsMouseHoveringOverCard(RIGHTCARDX, TOPCARDSY, _mousePos.x, _mousePos.y))
		{
			return E_CARDPOSITIONTYPE::topRight;
		}
	}
	else
	{
		if (IsMouseHoveringOverCard(LEFTCARDX, BOTTOMCARDSY, _mousePos.x, _mousePos.y))
		{
			return E_CARDPOSITIONTYPE::bottomLeft;
		}
		else if (IsMouseHoveringOverCard(RIGHTCARDX, BOTTOMCARDSY, _mousePos.x, _mousePos.y))
		{
			return E_CARDPOSITIONTYPE::bottomRight;
		}
	}

	return E_CARDPOSITIONTYPE::none;
}

void CardManager::MoveCardsAlong(const Player* _activePlayer, Card* _selectedCard)
{
	sideCard->SetPositionType(_selectedCard->GetPositionType());

	if (_activePlayer->GetColor() == E_PLAYERCOLOR::red)
	{
		_selectedCard->SetPositionType(E_CARDPOSITIONTYPE::sideRight);
		_selectedCard->SetOwner(playerBlue);
	}
	else if (_activePlayer->GetColor() == E_PLAYERCOLOR::blue)
	{
		_selectedCard->SetPositionType(E_CARDPOSITIONTYPE::sideLeft);
		_selectedCard->SetOwner(playerRed);
	}

	sideCard = _selectedCard;
}

void CardManager::MoveCardsBack(const Player* _activePlayer, Card* _prevSideCard)
{
	sideCard->SetPositionType(_prevSideCard->GetPositionType());

	if (_activePlayer->GetColor() == E_PLAYERCOLOR::red)
	{
		_prevSideCard->SetPositionType(E_CARDPOSITIONTYPE::sideLeft);
		_prevSideCard->SetOwner(playerRed);
		sideCard->SetOwner(playerRed);
	}
	else if (_activePlayer->GetColor() == E_PLAYERCOLOR::blue)
	{
		_prevSideCard->SetPositionType(E_CARDPOSITIONTYPE::sideRight);
		_prevSideCard->SetOwner(playerBlue);
		sideCard->SetOwner(playerBlue);
	}

	sideCard = _prevSideCard;
}

Card* CardManager::GetCard(const E_CARDPOSITIONTYPE _cardPositionType) const
{
	for (auto& card : cards)
	{
		if (card->GetPositionType() == _cardPositionType)
		{
			return card;
		}
	}

	return nullptr;
}

const bool CardManager::IsMouseHoveringOverCard(const int x, const int y, const int mouseX, const int mouseY) const
{
	return mouseX > x && mouseX < x + CARDWIDTH &&
		mouseY > y && mouseY < y + CARDHEIGHT;
}
