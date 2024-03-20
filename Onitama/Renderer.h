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
	Color redPieceColor = Color(255, 100, 100);
	Color redPieceColorHovered = Color(255, 200, 200);
	Color bluePieceColor = Color(170, 160, 255);
	Color bluePieceColorHovered = Color(210, 200, 255);

	void LoadTextures();
	void DrawBackground(Color _color);
	void DrawTiles(Color _color);
	void DrawTemple(const int _xIndex, const int _yIndex);
	void InitPlayerPieces(Player* _player);
	void DrawSinglePiece(Piece* _piece);

	bool IsTempleTile(const int _xIndex, const int _yIndex);
	Color GetPieceColor(Piece* _piece);
	Color GetTempleColor(E_PLAYERCOLOR _templeColor);

public:
	Renderer(SDL_Renderer* _SDLRenderer, Game* _game);
	~Renderer();
	void DrawGame();
	void RenderGame();
};
	
