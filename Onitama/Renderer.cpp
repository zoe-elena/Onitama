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
	InitPlayerPieces(game->GetPlayerRed());
	InitPlayerPieces(game->GetPlayerBlue());
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

			if (IsTempleTile(i, j))
			{
				DrawTemple(i, j);
			}
		}
	}
}

void Renderer::DrawMoveTiles(Color _color) const
{
	std::vector<Vector2> possibleMoveTiles = game->GetPossibleMoveTiles();

	for (size_t i = 0; i < possibleMoveTiles.size(); i++)
	{
		SDL_SetRenderDrawColor(SDLRenderer, _color.r, _color.g, _color.b, _color.a);

		SDL_Rect Tile;
		Vector2 possibleMoveTile = possibleMoveTiles[i];
		Tile.x = SIDEPANELWIDTH + TILEPADDING + possibleMoveTile.x * TILESIZE + possibleMoveTile.x * TILEPADDING;
		Tile.y = CARDPANELHEIGHT + TILEPADDING + possibleMoveTile.y * TILESIZE + possibleMoveTile.y * TILEPADDING;
		Tile.w = TILESIZE;
		Tile.h = TILESIZE;
		SDL_RenderFillRect(SDLRenderer, &Tile);
	}
}

bool Renderer::IsTempleTile(const int _xIndex, const int _yIndex) const
{
	return game->GetTile(_xIndex, _yIndex)->HasTemple();
}

void Renderer::DrawTemple(const int _xIndex, const int _yIndex) const
{
	SDL_SetRenderDrawColor(SDLRenderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_Rect Tile;
	Tile.x = SIDEPANELWIDTH + TILEPADDING + _xIndex * TILESIZE + _xIndex * TILEPADDING;
	Tile.y = CARDPANELHEIGHT + TILEPADDING + _yIndex * TILESIZE + _yIndex * TILEPADDING;
	Tile.w = TILESIZE;
	Tile.h = TILESIZE;

	E_PLAYERCOLOR playerTempleColor = game->GetTile(_xIndex, _yIndex)->GetTemple()->GetColor();
	Color color = GetColorByPlayerColor(playerTempleColor, redTempleColor, blueTempleColor);

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
}

Color Renderer::GetPieceColor(Piece* _piece)
{
	E_PLAYERCOLOR playerColor = _piece->GetOwnerPlayer()->GetColor();
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
