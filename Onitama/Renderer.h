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

	const Color backgroundColor = Color(89, 53, 46);
	const Color tileColor = Color(115, 86, 78);

	const Color redPieceColor = Color(255, 100, 100);
	const Color redPieceColorHovered = Color(255, 150, 150);
	const Color redPieceColorSelected = Color(255, 255, 255);
	const Color redTempleColor = Color(130, 50, 50);

	const Color bluePieceColor = Color(170, 160, 255);
	const Color bluePieceColorHovered = Color(200, 200, 255);
	const Color bluePieceColorSelected = Color(255, 255, 255);
	const Color blueTempleColor = Color(100, 90, 150);

	void LoadTextures();
	void DrawBackground(Color _color);
	void DrawTiles(Color _color);
	void DrawTemple(const int _xIndex, const int _yIndex);
	void InitPlayerPieces(Player* _player);
	void DrawSinglePiece(Piece* _piece);

	bool IsTempleTile(const int _xIndex, const int _yIndex);
	Color GetPieceColor(Piece* _piece);
	Color GetColorByPlayerColor(E_PLAYERCOLOR _playerColor, Color _redColor, Color _blueColor);

public:
	Renderer(SDL_Renderer* _SDLRenderer, Game* _game);
	~Renderer();
	void DrawGame();
	void RenderGame();
};
	
