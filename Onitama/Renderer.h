#pragma once
#include <array>
#include <map>
#include "SDL.h" 
#include "Vector2.h"
#include "Color.h"
#include "Defines.h"
#include "Game.h"

class Renderer
{
public:
	Renderer(SDL_Renderer* _sdlRenderer);
	~Renderer();

	void DrawGame(Game& _game);

private:
	SDL_Renderer* SDLRenderer = nullptr;
	SDL_Texture* textureButtonLegend = nullptr;
	SDL_Texture* textureRedWin = nullptr;
	SDL_Texture* textureBlueWin = nullptr;
	SDL_Texture* textureStudent = nullptr;
	SDL_Texture* textureMaster = nullptr;
	SDL_Texture* textureTemple = nullptr;
	SDL_Texture* textureCardDragon = nullptr;
	SDL_Texture* textureCardHorse = nullptr;
	SDL_Texture* textureCardMantis = nullptr;
	SDL_Texture* textureCardOx = nullptr;
	SDL_Texture* textureCardRabbit = nullptr;

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

	void MapCardTextures();
	void LoadTextures();
	void DrawBackground(const Color _color) const;
	void DrawButtonLegend();
	void DrawWinScreen(const E_PLAYERCOLOR _playerColor);
	void DrawTiles(const Color _color) const;
	void DrawMoveTiles(const Game& _game, const Color _color) const;
	void DrawTemple(const Player* _player)  const;
	void DrawPieces(const Game& _game, const Player* _player);
	void DrawSinglePiece(const Game& _game, const Piece* _piece);
	void DrawCards(const Game& _game);
	const Color GetPieceColor(const Game& _game, const Piece* _piece);
	const Color GetColorByPlayerColor(const E_PLAYERCOLOR _playerColor, const Color _redColor, const Color _blueColor) const;
};

