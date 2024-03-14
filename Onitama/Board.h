#pragma once
#include "SDL.h" 
#include "Color.h"

class Board
{
public:
	void InitBoard(SDL_Renderer* _renderer);
	void DrawBackground(SDL_Renderer* _renderer, Color _color);
	void DrawTiles(SDL_Renderer* _renderer, Color _color);
};

