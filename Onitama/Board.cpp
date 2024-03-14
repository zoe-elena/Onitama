#include "Board.h"
#include "Defines.h"

void Board::InitBoard(SDL_Renderer* _renderer)
{
	DrawBackground(_renderer, Color(244, 219, 213));
	DrawTiles(_renderer, Color(180, 145, 145));
	SDL_RenderPresent(_renderer);
}

void Board::DrawBackground(SDL_Renderer* _renderer, Color _color)
{
	SDL_SetRenderDrawColor(_renderer, _color.r, _color.g, _color.b, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(_renderer);
}

void Board::DrawTiles(SDL_Renderer* _renderer, Color _color)
{
	SDL_SetRenderDrawColor(_renderer, _color.r, _color.g, _color.b, _color.a);

	for (size_t i = 0; i < BOARDSIZE; i++)
	{
		for (size_t j = 0; j < BOARDSIZE; j++)
		{
			SDL_Rect Tile;
			Tile.x = SIDEPANELWIDTH + TILEPADDING + i * TILESIZE + i * TILEPADDING;
			Tile.y = CARDPANELHEIGHT + TILEPADDING + j * TILESIZE + j * TILEPADDING;
			Tile.w = TILESIZE;
			Tile.h = TILESIZE;
			SDL_RenderFillRect(_renderer, &Tile);
		}
	}
}