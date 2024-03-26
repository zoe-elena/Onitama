#include "Tile.h"

Tile::Tile()
{
	new Tile(Vector2(0, 0));
}

Tile::Tile(Vector2 _index) : index(_index)
{
}
