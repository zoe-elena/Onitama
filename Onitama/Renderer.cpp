#include "SDL.h"
#include "Renderer.h"
#include "Game.h"

Renderer::Renderer(SDL_Renderer* _SDLRenderer, Game* _game) : SDLRenderer(_SDLRenderer), game(_game)
{
	LoadTextures();
}

Renderer::~Renderer()
{
	SDL_DestroyTexture(textureStudent);
	SDL_DestroyTexture(textureMaster);
}

void Renderer::DrawGame()
{
	DrawBackground(backgroundColor);
	DrawTiles(tileColor);
	DrawMoveTiles(moveTileColor);
	DrawTemple(game->GetPlayerRed());
	DrawTemple(game->GetPlayerBlue());
	InitPlayerPieces(game->GetPlayerRed());
	InitPlayerPieces(game->GetPlayerBlue());
	DrawCards(game->GetPlayerRed());
	DrawCards(game->GetPlayerBlue());
}

void Renderer::RenderGame()
{
	SDL_RenderPresent(SDLRenderer);
}

void Renderer::LoadTextures()
{
	SDL_Surface* surfaceStudent = SDL_LoadBMP("Extern/Pieces/Student.bmp");
	SDL_Surface* surfaceMaster = SDL_LoadBMP("Extern/Pieces/Master.bmp");
	SDL_Surface* surfaceTemple = SDL_LoadBMP("Extern/Pieces/Temple.bmp");

	textureStudent = SDL_CreateTextureFromSurface(SDLRenderer, surfaceStudent);
	textureMaster = SDL_CreateTextureFromSurface(SDLRenderer, surfaceMaster);
	textureTemple = SDL_CreateTextureFromSurface(SDLRenderer, surfaceTemple);

	SDL_FreeSurface(surfaceStudent);
	SDL_FreeSurface(surfaceMaster);
	SDL_FreeSurface(surfaceTemple);
}

void Renderer::DrawBackground(Color _color) const
{
	SDL_SetRenderDrawColor(SDLRenderer, _color.r, _color.g, _color.b, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(SDLRenderer);
}

void Renderer::DrawTiles(Color _color) const
{
	for (size_t i = 0; i < BOARDSIZE; i++)
	{
		for (size_t j = 0; j < BOARDSIZE; j++)
		{
			SDL_SetRenderDrawColor(SDLRenderer, _color.r, _color.g, _color.b, _color.a);

			SDL_Rect Tile;
			Tile.x = SIDEPANELWIDTH + TILEPADDING + i * TILESIZE + i * TILEPADDING;
			Tile.y = CARDPANELHEIGHT + TILEPADDING + j * TILESIZE + j * TILEPADDING;
			Tile.w = TILESIZE;
			Tile.h = TILESIZE;
			SDL_RenderFillRect(SDLRenderer, &Tile);
		}
	}
}

void Renderer::DrawMoveTiles(Color _color) const
{
	std::vector<Vector2> moveTiles = game->GetValidMoves();

	if (moveTiles.size() == 0 || game->IsPieceSelected() == false)
	{
		return;
	}

	for (size_t i = 0; i < moveTiles.size(); i++)
	{
		SDL_SetRenderDrawColor(SDLRenderer, _color.r, _color.g, _color.b, _color.a);

		SDL_Rect Tile;
		Tile.x = SIDEPANELWIDTH + TILEPADDING + moveTiles[i].x * TILESIZE + moveTiles[i].x * TILEPADDING;
		Tile.y = CARDPANELHEIGHT + TILEPADDING + moveTiles[i].y * TILESIZE + moveTiles[i].y * TILEPADDING;
		Tile.w = TILESIZE;
		Tile.h = TILESIZE;
		SDL_RenderFillRect(SDLRenderer, &Tile);
	}
}

void Renderer::DrawTemple(Player* _player) const
{
	Vector2 templePosition = _player->GetTemplePosition();

	SDL_SetRenderDrawColor(SDLRenderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_Rect Tile;
	Tile.x = SIDEPANELWIDTH + TILEPADDING + templePosition.x * TILESIZE + templePosition.x * TILEPADDING;
	Tile.y = CARDPANELHEIGHT + TILEPADDING + templePosition.y * TILESIZE + templePosition.y * TILEPADDING;
	Tile.w = TILESIZE;
	Tile.h = TILESIZE;

	E_PLAYERCOLOR playerColor = _player->GetColor();
	Color color = GetColorByPlayerColor(playerColor, redTempleColor, blueTempleColor);

	SDL_SetTextureColorMod(textureTemple, color.r, color.g, color.b);
	SDL_RenderCopy(SDLRenderer, textureTemple, nullptr, &Tile);
}

void Renderer::InitPlayerPieces(Player* _player)
{
	for (int u = 0; u < _player->PlayerPieces.size(); u++)
	{
		DrawSinglePiece(_player->PlayerPieces[u]);
	}
}


void Renderer::DrawSinglePiece(Piece* _piece)
{
	SDL_SetRenderDrawColor(SDLRenderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_Rect Tile;
	Tile.x = SIDEPANELWIDTH + TILEPADDING + _piece->GetXIndex() * TILESIZE + _piece->GetXIndex() * TILEPADDING;
	Tile.y = CARDPANELHEIGHT + TILEPADDING + _piece->GetYIndex() * TILESIZE + _piece->GetYIndex() * TILEPADDING;
	Tile.w = TILESIZE;
	Tile.h = TILESIZE;

	SDL_Texture* texture;
	if (_piece->GetType() == E_PIECETYPE::master)
	{
		texture = textureMaster;
	}
	else
	{
		texture = textureStudent;
	}

	Color color = GetPieceColor(_piece);
	SDL_SetTextureColorMod(texture, color.r, color.g, color.b);
	SDL_RenderCopy(SDLRenderer, texture, nullptr, &Tile);
	// Use for cards flip: SDL_RenderCopyEx(SDLRenderer, texture, nullptr, &Tile, 0, nullptr, SDL_FLIP_VERTICAL);
}

void Renderer::DrawCards(Player* _player)
{
	SDL_Rect Tile;
	Color colorLeftCard = Color(0, 0, 0, 255);
	Color colorRightCard = Color(0, 0, 0, 255);
	Card* selectedCard = game->GetSelectedCard();

	if (selectedCard != nullptr && game->IsActivePlayer(_player))
	{
		if (selectedCard->GetCardPosition() == E_CARDPOSITIONS::topLeft
			|| selectedCard->GetCardPosition() == E_CARDPOSITIONS::lowLeft)
		{
			colorLeftCard = Color(100, 100, 100, 255);
		}

		if (selectedCard->GetCardPosition() == E_CARDPOSITIONS::topRight
			|| selectedCard->GetCardPosition() == E_CARDPOSITIONS::lowRight)
		{
			colorRightCard = Color(100, 100, 100, 255);
		}
	}

	Tile.x = _player->GetLeftCardSlotPosition().x;
	Tile.y = _player->GetLeftCardSlotPosition().y;
	Tile.w = CARDWIDTH;
	Tile.h = CARDHEIGHT;
	SDL_SetRenderDrawColor(SDLRenderer, colorLeftCard.r, colorLeftCard.g, colorLeftCard.b, colorLeftCard.a);
	SDL_RenderFillRect(SDLRenderer, &Tile);

	Tile.x = _player->GetRightCardSlotPosition().x;
	Tile.y = _player->GetRightCardSlotPosition().y;
	Tile.w = CARDWIDTH;
	Tile.h = CARDHEIGHT;
	SDL_SetRenderDrawColor(SDLRenderer, colorRightCard.r, colorRightCard.g, colorRightCard.b, colorRightCard.a);
	SDL_RenderFillRect(SDLRenderer, &Tile);
}

Color Renderer::GetPieceColor(Piece* _piece)
{
	E_PLAYERCOLOR playerColor = _piece->GetOwner()->GetColor();
	bool isHovered = game->GetHoveredPiece() == _piece;
	bool isSelected = game->GetSelectedPiece() == _piece;

	if (isSelected)
	{
		return GetColorByPlayerColor(playerColor, redPieceColorSelected, bluePieceColorSelected);
	}
	else if (isHovered)
	{
		return GetColorByPlayerColor(playerColor, redPieceColorHovered, bluePieceColorHovered);
	}

	return GetColorByPlayerColor(playerColor, redPieceColor, bluePieceColor);
}

Color Renderer::GetColorByPlayerColor(E_PLAYERCOLOR _playerColor, Color _redColor, Color _blueColor) const
{
	if (_playerColor == E_PLAYERCOLOR::red)
	{
		return _redColor;
	}
	else if (_playerColor == E_PLAYERCOLOR::blue)
	{
		return _blueColor;
	}
	else
	{
		return Color::White();
	}
}
