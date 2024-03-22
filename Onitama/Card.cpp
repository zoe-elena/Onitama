#include "Card.h"

Card::Card(E_CARDTYPE _cardType, const std::vector<Vector2> _moves)
{
	player = nullptr;
	cardType = _cardType;

	for (size_t x = 0; x < _moves.size(); x++)
	{
			moves.push_back(_moves[x]);
	}
}
