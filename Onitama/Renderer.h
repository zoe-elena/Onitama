#pragma once
#include "SDL.h" 
#include "Color.h"

// Forward Declaration to avoid circular include and assure the classes stil exist
class Game;
class Player;
class Piece;

class Renderer
{
private:
	Game* game;
	SDL_Renderer* SDLRenderer;
	SDL_Texture* textureStudentRed;
	SDL_Texture* textureMasterRed;
	SDL_Texture* textureStudentBlue;
	SDL_Texture* textureMasterBlue;

	
	void LoadTextures();
	void DrawBackground(Color _color);
	void DrawTiles(Color _color);
	void InitPlayerPieces(Player* _player);
	void DrawSinglePiece(Piece _piece);

public:
	Renderer(SDL_Renderer* _SDLRenderer, Game* _game);
	~Renderer();
	void RenderGame();
};
	
