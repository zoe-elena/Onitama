#pragma once
#include <array>
#include <map>
#include "Defines.h"
#include "Card.h"

class Player;

class CardManager
{
public:
	CardManager(Player* _playerRed, Player* _playerBlue);
	~CardManager();

	void InitCards(Player* _activePlayer);
	Card* GetCard(E_CARDPOSITIONTYPE _cardPositionType);
	E_CARDPOSITIONTYPE CheckCardHover(E_PLAYERCOLOR _activePlayerColor, Vector2 _mousePos);
	void MoveCardsAlong(Player* _activePlayer, Card* _selectedCard);
	void MoveCardsBack(Player* _activePlayer, Card* _prevSideCard);

	Card* GetSideCard() { return sideCard; }
	const std::array<Card*, CARDS>& GetCards() const { return cards; }
	const std::array<Vector2, CARDSLOTS>& GetCardPositions() const { return cardPositions; }
	const std::map<E_CARDPOSITIONTYPE, Vector2>& GetCardPositionMap() const { return cardPositionMap; }

private:
	std::array<Card*, CARDS> cards = { nullptr };
	Card* sideCard = nullptr;
	std::array<Vector2, CARDSLOTS> cardPositions;
	std::map<E_CARDPOSITIONTYPE, Vector2> cardPositionMap;
	std::map<E_CARDPOSITIONTYPE, Player*> playerCardMap;

	std::vector<Vector2> movesMantis{ Vector2(-1, -1), Vector2(1, -1), Vector2(0, 1) };
	std::vector<Vector2> movesDragon{ Vector2(-2, -1), Vector2(-1, 1), Vector2(1, 1), Vector2(2, -1) };
	std::vector<Vector2> movesOx{ Vector2(0, -1), Vector2(0, 1), Vector2(1, 0) };
	std::vector<Vector2> movesHorse{ Vector2(-1, 0), Vector2(0, -4), Vector2(0, 1) };
	std::vector<Vector2> movesRabbit{ Vector2(-1, 1), Vector2(1, -1), Vector2(2, 0) };

	Player* playerBlue;
	Player* playerRed;

	int leftCardsX = SIDEPANELWIDTH + TILEPADDING;
	int rightCardsX = leftCardsX + CARDWIDTH + TILEPADDING * 2;
	int sideCardY = (WINDOWLENGTHSIZE - CARDHEIGHT) / 2;
	int sideCardRightX = rightCardsX + CARDWIDTH + TILEPADDING;
	int topCardsY = TILEPADDING;
	int bottomCardsY = TILEPADDING * 4 + CARDHEIGHT + BOARDSIZE * TILESIZE + BOARDSIZE * TILEPADDING;
	int sideCardLeftX = TILEPADDING;

	bool IsMouseHoveringOverCard(int x, int y, int mouseX, int mouseY);
	void MapCardPositions();
	void MapPlayerCards();
};
