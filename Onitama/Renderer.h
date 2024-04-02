#pragma once
#include <array>
#include <map>
#include "SDL.h" 
#include "Vector2.h"
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
	SDL_Texture* textureButtonLegend;
	SDL_Texture* textureStudent;
	SDL_Texture* textureMaster;
	SDL_Texture* textureTemple;
	SDL_Texture* textureCardDragon;
	SDL_Texture* textureCardHorse;
	SDL_Texture* textureCardMantis;
	SDL_Texture* textureCardOx;
	SDL_Texture* textureCardRabbit;

	std::map<E_CARDTYPE, SDL_Texture*&> cardTypeMap;

	const Color backgroundColor = Color(89, 53, 46);
	const Color tileColor = Color(115, 86, 78);
	const Color moveTileColor = Color(150, 120, 115);

	const Color redPieceColor = Color(255, 100, 100);
	const Color redPieceColorHovered = Color(255, 150, 150);
	const Color redPieceColorSelected = Color(255, 255, 255);
	const Color redTempleColor = Color(130, 50, 50);

	const Color bluePieceColor = Color(170, 160, 255);
	const Color bluePieceColorHovered = Color(200, 200, 255);
	const Color bluePieceColorSelected = Color(255, 255, 255);
	const Color blueTempleColor = Color(100, 90, 150);

	const Color cardColor = Color(115, 86, 78);
	const Color cardColorInteractable = Color(150, 120, 115);
	const Color cardColorSelected = Color(170, 140, 135);

	void LoadTextures();
	void DrawBackground(Color _color) const;
	void DrawTiles(Color _color) const;
	void DrawMoveTiles(Color _color) const;
	void DrawTemple(Player* _player)  const;
	void DrawPieces(Player* _player);
	void DrawSinglePiece(Piece* _piece);
	void DrawCards();
	void DrawButtonLegend();

	Color GetPieceColor(Piece* _piece);
	Color GetColorByPlayerColor(E_PLAYERCOLOR _playerColor, Color _redColor, Color _blueColor) const;

public:
	Renderer(SDL_Renderer* _SDLRenderer, Game* _game);
	~Renderer();
	void DrawGame();
	void RenderGame();
};

