#include "Card.h"

Card::Card(E_CARDTYPE _cardType, E_CARDPOSITIONTYPE _cardPosition, const std::vector<Vector2> _moves)
{
	Player = nullptr;
	cardType = _cardType;
	cardPosition = _cardPosition;

	for (size_t x = 0; x < _moves.size(); x++)
	{
		moves.push_back(_moves[x]);
	}
}
