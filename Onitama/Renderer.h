#pragma once
#include "SDL.h" 
#include "Color.h"
#include "Defines.h"

// Forward Declaration to avoid circular include and assure the classes stil exist
class Game;
class Player;
class Piece;

class Renderer
{
private:
	Game* game;
	SDL_Renderer* SDLRenderer;
	SDL_Texture* textureStudent;
	SDL_Texture* textureMaster;
	SDL_Texture* textureTemple;

	Color backgroundColor = Color(89, 53, 46);
	Color tileColor = Color(115, 86, 78);
	Color redPlayerColor = Color(255, 100, 100);
	Color bluePlayerColor = Color(170, 160, 255);

	void LoadTextures();
	void DrawBackground(Color _color);
	void DrawTiles(Color _color);
	void DrawTemple(const int _xIndex, const int _yIndex);
	void InitPlayerPieces(Player* _player);
	void DrawSinglePiece(Piece _piece);

	bool IsTempleTile(const int _xIndex, const int _yIndex);
	Color GetPlayerColor(E_PLAYERCOLOR _playerColor);

public:
	Renderer(SDL_Renderer* _SDLRenderer, Game* _game);
	~Renderer();
	void RenderGame();
};
	
