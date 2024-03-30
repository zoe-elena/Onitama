#pragma once
#include <array>
#include <map>
#include "Defines.h"
#include "Card.h"

class Player;

class CardManager
{
private:
	std::array<Card*, CARDS> cards;
	Card* sideCard;
	std::array<Vector2, CARDSLOTS> cardPositions;
	std::map<E_CARDPOSITIONTYPE, Vector2> cardPositionMap;

	int leftCardsX = SIDEPANELWIDTH + TILEPADDING;
	int rightCardsX = leftCardsX + CARDWIDTH + TILEPADDING * 2;
	int sideCardY = (WINDOWLENGTHSIZE - CARDHEIGHT) / 2;
	int sideCardRightX = rightCardsX + CARDWIDTH + TILEPADDING;
	int topCardsY = TILEPADDING;
	int bottomCardsY = TILEPADDING * 4 + CARDHEIGHT + BOARDSIZE * TILESIZE + BOARDSIZE * TILEPADDING;
	int sideCardLeftX = TILEPADDING;

public:
	CardManager();

	inline std::array<Card*, CARDS> GetCards() { return cards; }
	inline std::array<Vector2, CARDSLOTS> GetCardPositions() { return cardPositions; }
	inline std::map<E_CARDPOSITIONTYPE, Vector2> GetCardPositionMap() { return cardPositionMap; }

	void InitCards(Player* _playerRed, Player* _playerBlue);
	Card* GetCard(E_CARDTYPE _cardType);
	Card* GetCard(E_CARDPOSITIONTYPE _cardPositionType);
	E_CARDPOSITIONTYPE CheckCardHover(E_PLAYERCOLOR _activePlayerColor, Vector2 _mousePos);
	bool IsMouseHoveringOverCard(int x, int y, int mouseX, int mouseY);
};
