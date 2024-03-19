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

void Renderer::RenderGame()
{
	DrawBackground(backgroundColor);
	DrawTiles(tileColor);
	InitPlayerPieces(game->GetPlayerRed());
	InitPlayerPieces(game->GetPlayerBlue());
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

void Renderer::DrawBackground(Color _color)
{
	SDL_SetRenderDrawColor(SDLRenderer, _color.r, _color.g, _color.b, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(SDLRenderer);
}

void Renderer::DrawTiles(Color _color)
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

bool Renderer::IsTempleTile(const int _xIndex, const int _yIndex)
{
	return game->GetTile(_xIndex, _yIndex)->HasTemple();
}

void Renderer::DrawTemple(const int _xIndex, const int _yIndex)
{
	SDL_SetRenderDrawColor(SDLRenderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_Rect Tile;
	Tile.x = SIDEPANELWIDTH + TILEPADDING + _xIndex * TILESIZE + _xIndex * TILEPADDING;
	Tile.y = CARDPANELHEIGHT + TILEPADDING + _yIndex * TILESIZE + _yIndex * TILEPADDING;
	Tile.w = TILESIZE;
	Tile.h = TILESIZE;

	Color color = GetPlayerColor(game->GetTile(_xIndex, _yIndex)->GetTemple()->GetColor());
	SDL_SetTextureColorMod(textureTemple, color.r, color.g, color.b);
	SDL_RenderCopy(SDLRenderer, textureTemple, nullptr, &Tile);
}


void Renderer::InitPlayerPieces(Player* _player)
{
	for (int u = 0; u < _player->PlayerPieces.size(); u++) {
		DrawSinglePiece(_player->PlayerPieces[u]);
	}
}


void Renderer::DrawSinglePiece(Piece _piece)
{
	SDL_SetRenderDrawColor(SDLRenderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_Rect Tile;
	Tile.x = SIDEPANELWIDTH + TILEPADDING + _piece.GetXIndex() * TILESIZE + _piece.GetXIndex() * TILEPADDING;
	Tile.y = CARDPANELHEIGHT + TILEPADDING + _piece.GetYIndex() * TILESIZE + _piece.GetYIndex() * TILEPADDING;
	Tile.w = TILESIZE;
	Tile.h = TILESIZE;

	SDL_Texture* texture;
	if (_piece.GetType() == master)
	{
		texture = textureMaster;
	}
	else
	{
		texture = textureStudent;
	}

	Color color = GetPlayerColor(_piece.GetOwnerPlayer()->GetColor());
	SDL_SetTextureColorMod(texture, color.r, color.g, color.b);
	SDL_RenderCopy(SDLRenderer, texture, nullptr, &Tile);
}

Color Renderer::GetPlayerColor(E_PLAYERCOLOR _playerColor)
{
	if (_playerColor == red)
	{
		return redPlayerColor;
	}
	else if (_playerColor == blue)
	{
		return bluePlayerColor;
	}
	else {
		return Color::White();
	}
}
