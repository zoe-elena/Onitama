#include "SDL.h"
#include "Renderer.h"
#include "Defines.h"
#include "Game.h"

Renderer::Renderer(SDL_Renderer* _SDLRenderer, Game* _game) : SDLRenderer(_SDLRenderer), game(_game)
{ 
	LoadTextures();
}

Renderer::~Renderer()
{
	SDL_DestroyTexture(textureStudentRed);
	SDL_DestroyTexture(textureMasterRed);
	SDL_DestroyTexture(textureStudentBlue);
	SDL_DestroyTexture(textureMasterBlue);
}

void Renderer::RenderGame()
{
	DrawBackground(Color(89, 53, 46));
	DrawTiles(Color(115, 86, 78));
	InitPlayerPieces(game->GetPlayerRed());
	InitPlayerPieces(game->GetPlayerBlue());
	SDL_RenderPresent(SDLRenderer);
}

void Renderer::LoadTextures()
{
	SDL_Surface* surfaceStudentRed = SDL_LoadBMP("Extern/Pieces/RedStudent.bmp");
	SDL_Surface* surfaceMasterRed = SDL_LoadBMP("Extern/Pieces/RedMaster.bmp");
	SDL_Surface* surfaceStudentBlue = SDL_LoadBMP("Extern/Pieces/BlueStudent.bmp");
	SDL_Surface* surfaceMasterBlue = SDL_LoadBMP("Extern/Pieces/BlueMaster.bmp");

	textureStudentRed = SDL_CreateTextureFromSurface(SDLRenderer, surfaceStudentRed);
	textureMasterRed = SDL_CreateTextureFromSurface(SDLRenderer, surfaceMasterRed);
	textureStudentBlue = SDL_CreateTextureFromSurface(SDLRenderer, surfaceStudentBlue);
	textureMasterBlue = SDL_CreateTextureFromSurface(SDLRenderer, surfaceMasterBlue);

	SDL_FreeSurface(surfaceStudentRed);
	SDL_FreeSurface(surfaceMasterRed);
	SDL_FreeSurface(surfaceStudentBlue);
	SDL_FreeSurface(surfaceMasterBlue);
}

void Renderer::DrawBackground(Color _color)
{
	SDL_SetRenderDrawColor(SDLRenderer, _color.r, _color.g, _color.b, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(SDLRenderer);
}

void Renderer::DrawTiles(Color _color)
{
	SDL_SetRenderDrawColor(SDLRenderer, _color.r, _color.g, _color.b, _color.a);

	for (size_t i = 0; i < BOARDSIZE; i++)
	{
		for (size_t j = 0; j < BOARDSIZE; j++)
		{
			SDL_Rect Tile;
			Tile.x = SIDEPANELWIDTH + TILEPADDING + i * TILESIZE + i * TILEPADDING;
			Tile.y = CARDPANELHEIGHT + TILEPADDING + j * TILESIZE + j * TILEPADDING;
			Tile.w = TILESIZE;
			Tile.h = TILESIZE;
			SDL_RenderFillRect(SDLRenderer, &Tile);
		}
	}
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
	Tile.x = SIDEPANELWIDTH + TILEPADDING + _piece.GetXPos() * TILESIZE + _piece.GetXPos() * TILEPADDING;
	Tile.y = CARDPANELHEIGHT + TILEPADDING + _piece.GetYPos() * TILESIZE + _piece.GetYPos() * TILEPADDING;
	Tile.w = TILESIZE;
	Tile.h = TILESIZE;

	SDL_Texture* texture;
	if (_piece.GetType() == master)
	{
		if (_piece.GetColor() == red)
		{
			texture = textureMasterRed;
		}
		else
		{
			texture = textureMasterBlue;
		}
	}
	else
	{
		if (_piece.GetColor() == red)
		{
			texture = textureStudentRed;
		}
		else
		{
			texture = textureStudentBlue;
		}
	}
	
	SDL_RenderCopy(SDLRenderer, texture, nullptr, &Tile);
}