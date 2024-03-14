#pragma once
#include "SDL.h" 
#include "Color.h"
#include "Game.h"

class Board
{
private:
	SDL_Texture* textureStudentRed;
	SDL_Texture* textureMasterRed;

	SDL_Texture* textureStudentBlue;
	SDL_Texture* textureMasterBlue;

	void LoadTextures(SDL_Renderer* _renderer);
	void DrawBackground(SDL_Renderer* _renderer, Color _color);
	void DrawTiles(SDL_Renderer* _renderer, Color _color);
	void InitPlayerPieces(Game* game, SDL_Renderer* _renderer, Player* _player);
	void DrawSinglePiece(SDL_Renderer* _renderer, Piece _piece, E_PLAYERCOLOR _color, E_PIECETYPE _piecetype);

public:
	void InitBoard(Game* _game, SDL_Renderer* _renderer);
};
	
