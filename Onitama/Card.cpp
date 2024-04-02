#include "Card.h"
#include "Player.h"

Card::Card(Player* _player, E_CARDTYPE _cardType, E_CARDPOSITIONTYPE _cardPosition, const std::vector<Vector2> _moves)
{
	owner = _player;
	cardType = _cardType;
	cardPositionType = _cardPosition;

	for (size_t x = 0; x < _moves.size(); x++)
	{
		moves.push_back(_moves[x]);
	}
}

E_PLAYERCOLOR Card::GetOwnerColor() const
{
	return owner->GetColor();
}
