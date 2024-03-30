#include "SDL.h"
#include "Renderer.h"
#include "Game.h"
#include "array"

Renderer::Renderer(SDL_Renderer* _SDLRenderer, Game* _game) : SDLRenderer(_SDLRenderer), game(_game)
{
	cardTypeMap.emplace(E_CARDTYPE::dragon, textureCardDragon);
	cardTypeMap.emplace(E_CARDTYPE::horse, textureCardHorse);
	cardTypeMap.emplace(E_CARDTYPE::mantis, textureCardMantis);
	cardTypeMap.emplace(E_CARDTYPE::ox, textureCardOx);
	cardTypeMap.emplace(E_CARDTYPE::rabbit, textureCardRabbit);
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
	DrawPieces(game->GetPlayerRed());
	DrawPieces(game->GetPlayerBlue());
	DrawCards();
}

void Renderer::RenderGame()
{
	SDL_RenderPresent(SDLRenderer);
}

void Renderer::LoadTextures()
{
	SDL_Surface* surfaceStudent = SDL_LoadBMP("Extern/Images/Student.bmp");
	SDL_Surface* surfaceMaster = SDL_LoadBMP("Extern/Images/Master.bmp");
	SDL_Surface* surfaceTemple = SDL_LoadBMP("Extern/Images/Temple.bmp");
	SDL_Surface* surfaceCardDragon = SDL_LoadBMP("Extern/Images/CardDragon.bmp");
	SDL_Surface* surfaceCardHorse = SDL_LoadBMP("Extern/Images/CardHorse.bmp");
	SDL_Surface* surfaceCardMantis = SDL_LoadBMP("Extern/Images/CardMantis.bmp");
	SDL_Surface* surfaceCardOx = SDL_LoadBMP("Extern/Images/CardOx.bmp");
	SDL_Surface* surfaceCardRabbit = SDL_LoadBMP("Extern/Images/CardRabbit.bmp");

	textureStudent = SDL_CreateTextureFromSurface(SDLRenderer, surfaceStudent);
	textureMaster = SDL_CreateTextureFromSurface(SDLRenderer, surfaceMaster);
	textureTemple = SDL_CreateTextureFromSurface(SDLRenderer, surfaceTemple);
	textureCardDragon = SDL_CreateTextureFromSurface(SDLRenderer, surfaceCardDragon);
	textureCardHorse = SDL_CreateTextureFromSurface(SDLRenderer, surfaceCardHorse);
	textureCardMantis = SDL_CreateTextureFromSurface(SDLRenderer, surfaceCardMantis);
	textureCardOx = SDL_CreateTextureFromSurface(SDLRenderer, surfaceCardOx);
	textureCardRabbit = SDL_CreateTextureFromSurface(SDLRenderer, surfaceCardRabbit);

	SDL_FreeSurface(surfaceStudent);
	SDL_FreeSurface(surfaceMaster);
	SDL_FreeSurface(surfaceTemple);
	SDL_FreeSurface(surfaceCardDragon);
	SDL_FreeSurface(surfaceCardHorse);
	SDL_FreeSurface(surfaceCardMantis);
	SDL_FreeSurface(surfaceCardOx);
	SDL_FreeSurface(surfaceCardRabbit);
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

void Renderer::DrawPieces(Player* _player)
{
	for (int u = 0; u < _player->PlayerPieces.size(); u++)
	{
		if (_player->PlayerPieces[u]->isCaptured == false)
		{
			DrawSinglePiece(_player->PlayerPieces[u]);
		}
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

void Renderer::DrawCards()
{
	SDL_Rect Tile;

	std::array<Card*, CARDS> cards = game->GetAllCards();
	std::array<Vector2, CARDSLOTS> cardPositions = game->GetAllCardPositions();
	Color color;

	for (size_t i = 0; i < cards.size(); i++)
	{
		int cardRotation = cards[i]->player->GetColor() == E_PLAYERCOLOR::red ? 180 : 0;

		if (cards[i] == game->GetSelectedCard())
		{
			color = cardColorSelected;
		}
		else
		{
			color = game->IsActivePlayer(cards[i]->player) ? cardColorInteractable : cardColor;
		}
		Vector2 tempCardPosition = game->GetCardPositionMap().find(cards[i]->cardPositionType)->second;
		Tile.x = tempCardPosition.x;
		Tile.y = tempCardPosition.y;
		Tile.w = CARDWIDTH;
		Tile.h = CARDHEIGHT;

		SDL_Texture* tempCardTexture = cardTypeMap.find(cards[i]->GetCardType())->second;
		SDL_SetTextureColorMod(tempCardTexture, color.r, color.g, color.b);
		SDL_RenderCopyEx(SDLRenderer, tempCardTexture, nullptr, &Tile, cardRotation, nullptr, SDL_FLIP_NONE);
	}
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
