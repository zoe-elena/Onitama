#pragma once
#include <array>
#include <map>
#include "Defines.h"
#include "Card.h"
#include "Player.h"

class CardManager
{
public:
	CardManager(Player* _playerRed, Player* _playerBlue);
	~CardManager();

	void InitCards(const Player* _activePlayer);
	const E_CARDPOSITIONTYPE CheckCardHover(const E_PLAYERCOLOR _activePlayerColor, const Vector2 _mousePos) const;
	void MoveCardsAlong(const Player* _activePlayer, Card* _selectedCard);
	void MoveCardsBack(const Player* _activePlayer, Card* _prevSideCard);

	Card* GetCard(const E_CARDPOSITIONTYPE _cardPositionType) const;
	Card* GetSideCard() { return sideCard; }
	const std::array<Card*, CARDS>& GetCards() const { return cards; }
	const std::map<E_CARDPOSITIONTYPE, Vector2>& GetCardPositionMap() const { return cardPositionMap; }

private:
	std::array<Card*, CARDS> cards = { nullptr };
	Card* sideCard = nullptr;
	std::map<E_CARDPOSITIONTYPE, Vector2> cardPositionMap;
	std::map<E_CARDPOSITIONTYPE, Player*> playerCardMap;
	Player* playerBlue;
	Player* playerRed;

	const std::vector<Vector2> movesMantis{ Vector2(-1, -1), Vector2(1, -1), Vector2(0, 1) };
	const std::vector<Vector2> movesDragon{ Vector2(-2, -1), Vector2(-1, 1), Vector2(1, 1), Vector2(2, -1) };
	const std::vector<Vector2> movesOx{ Vector2(0, -1), Vector2(0, 1), Vector2(1, 0) };
	const std::vector<Vector2> movesHorse{ Vector2(-1, 0), Vector2(0, -1), Vector2(0, 1) };
	const std::vector<Vector2> movesRabbit{ Vector2(-1, 1), Vector2(1, -1), Vector2(2, 0) };

	const bool IsMouseHoveringOverCard(const int x, const int y, const int mouseX, const int mouseY) const;
	void MapCardPositions();
	void MapPlayerCards();
};
