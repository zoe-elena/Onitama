#include "Tile.h"

Tile::Tile()
{
	Tile(Vector2(0, 0), nullptr);
}

Tile::Tile(Vector2 _index, Temple* _temple) : index(_index), temple(_temple)
{
}
