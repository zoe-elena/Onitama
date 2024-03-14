#include "SDL.h"
#include "Board.h"
#include "Defines.h"

void Board::InitBoard(Game* _game, SDL_Renderer* _renderer)
{
	LoadTextures(_renderer);
	DrawBackground(_renderer, Color(89, 53, 46));
	DrawTiles(_renderer, Color(115, 86, 78));
	InitPlayerPieces(_game, _renderer, _game->GetPlayerRed());
	InitPlayerPieces(_game, _renderer, _game->GetPlayerBlue());
	SDL_RenderPresent(_renderer);
}

void Board::LoadTextures(SDL_Renderer* _renderer)
{
	SDL_Surface* surfaceStudentRed = SDL_LoadBMP("Extern/Pieces/RedStudent.bmp");
	SDL_Surface* surfaceMasterRed = SDL_LoadBMP("Extern/Pieces/RedMaster.bmp");
	SDL_Surface* surfaceStudentBlue = SDL_LoadBMP("Extern/Pieces/BlueStudent.bmp");
	SDL_Surface* surfaceMasterBlue = SDL_LoadBMP("Extern/Pieces/BlueMaster.bmp");

	textureStudentRed = SDL_CreateTextureFromSurface(_renderer, surfaceStudentRed);
	textureMasterRed = SDL_CreateTextureFromSurface(_renderer, surfaceMasterRed);
	textureStudentBlue = SDL_CreateTextureFromSurface(_renderer, surfaceStudentBlue);
	textureMasterBlue = SDL_CreateTextureFromSurface(_renderer, surfaceMasterBlue);

	SDL_FreeSurface(surfaceStudentRed);
	SDL_FreeSurface(surfaceMasterRed);
	SDL_FreeSurface(surfaceStudentBlue);
	SDL_FreeSurface(surfaceMasterBlue);
}

void Board::DrawBackground(SDL_Renderer* _renderer, Color _color)
{
	SDL_SetRenderDrawColor(_renderer, _color.r, _color.g, _color.b, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(_renderer);
}

void Board::DrawTiles(SDL_Renderer* _renderer, Color _color)
{
	SDL_SetRenderDrawColor(_renderer, _color.r, _color.g, _color.b, _color.a);

	for (size_t i = 0; i < BOARDSIZE; i++)
	{
		for (size_t j = 0; j < BOARDSIZE; j++)
		{
			SDL_Rect Tile;
			Tile.x = SIDEPANELWIDTH + TILEPADDING + i * TILESIZE + i * TILEPADDING;
			Tile.y = CARDPANELHEIGHT + TILEPADDING + j * TILESIZE + j * TILEPADDING;
			Tile.w = TILESIZE;
			Tile.h = TILESIZE;
			SDL_RenderFillRect(_renderer, &Tile);
		}
	}
}

void Board::InitPlayerPieces(Game* _game, SDL_Renderer* _renderer, Player* _player)
{
	for (int u = 0; u < _player->InitStudentPositions.size(); u++) {
		Piece tempPiece = Piece(_player->InitStudentPositions[u]);
		_player->PlayerPieces.push_back(tempPiece);
		DrawSinglePiece(_renderer, tempPiece, _player->GetColor(), student);
	}
	DrawSinglePiece(_renderer, _player->InitMasterPosition, _player->GetColor(), master);
}

void Board::DrawSinglePiece(SDL_Renderer* _renderer, Piece _piece, E_PLAYERCOLOR _color, E_PIECETYPE _piecetype)
{
	SDL_SetRenderDrawColor(_renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_Rect Tile;
	Tile.x = SIDEPANELWIDTH + TILEPADDING + _piece.GetXPos() * TILESIZE + _piece.GetXPos() * TILEPADDING;
	Tile.y = CARDPANELHEIGHT + TILEPADDING + _piece.GetYPos() * TILESIZE + _piece.GetYPos() * TILEPADDING;
	Tile.w = TILESIZE;
	Tile.h = TILESIZE;

	SDL_Texture* texture;
	if (_piecetype == master)
	{
		if (_color == red)
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
		if (_color == red)
		{
			texture = textureStudentRed;
		}
		else
		{
			texture = textureMasterRed;
		}
	}

	
	SDL_RenderCopy(_renderer, texture, nullptr, &Tile);
}
