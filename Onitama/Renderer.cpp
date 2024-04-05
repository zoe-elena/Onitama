#include "SDL.h"
#include "Renderer.h"
#include "Game.h"

Renderer::Renderer(SDL_Renderer* _SDLRenderer) : SDLRenderer(_SDLRenderer)
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
	SDL_DestroyTexture(textureButtonLegend);
	SDL_DestroyTexture(textureStudent);
	SDL_DestroyTexture(textureMaster);
	SDL_DestroyTexture(textureTemple);
	SDL_DestroyTexture(textureCardDragon);
	SDL_DestroyTexture(textureCardHorse);
	SDL_DestroyTexture(textureCardMantis);
	SDL_DestroyTexture(textureCardOx);
	SDL_DestroyTexture(textureCardRabbit);
}

void Renderer::DrawGame(Game& _game)
{
	DrawBackground(backgroundColor);
	DrawButtonLegend();
	DrawTiles(tileColor);
	DrawMoveTiles(_game, moveTileColor);
	DrawTemple(_game.GetPlayerRed());
	DrawTemple(_game.GetPlayerBlue());
	DrawPieces(_game, _game.GetPlayerRed());
	DrawPieces(_game, _game.GetPlayerBlue());
	if(_game.IsWin() == false)
	{
		DrawCards(_game);
	}

	SDL_RenderPresent(SDLRenderer);
}

void Renderer::LoadTextures()
{
	SDL_Surface* surfaceButtonLegend = SDL_LoadBMP("Extern/Images/ButtonLegend.bmp");
	SDL_Surface* surfaceStudent = SDL_LoadBMP("Extern/Images/Student.bmp");
	SDL_Surface* surfaceMaster = SDL_LoadBMP("Extern/Images/Master.bmp");
	SDL_Surface* surfaceTemple = SDL_LoadBMP("Extern/Images/Temple.bmp");
	SDL_Surface* surfaceCardDragon = SDL_LoadBMP("Extern/Images/CardDragon.bmp");
	SDL_Surface* surfaceCardHorse = SDL_LoadBMP("Extern/Images/CardHorse.bmp");
	SDL_Surface* surfaceCardMantis = SDL_LoadBMP("Extern/Images/CardMantis.bmp");
	SDL_Surface* surfaceCardOx = SDL_LoadBMP("Extern/Images/CardOx.bmp");
	SDL_Surface* surfaceCardRabbit = SDL_LoadBMP("Extern/Images/CardRabbit.bmp");

	textureButtonLegend = SDL_CreateTextureFromSurface(SDLRenderer, surfaceButtonLegend);
	textureStudent = SDL_CreateTextureFromSurface(SDLRenderer, surfaceStudent);
	textureMaster = SDL_CreateTextureFromSurface(SDLRenderer, surfaceMaster);
	textureTemple = SDL_CreateTextureFromSurface(SDLRenderer, surfaceTemple);
	textureCardDragon = SDL_CreateTextureFromSurface(SDLRenderer, surfaceCardDragon);
	textureCardHorse = SDL_CreateTextureFromSurface(SDLRenderer, surfaceCardHorse);
	textureCardMantis = SDL_CreateTextureFromSurface(SDLRenderer, surfaceCardMantis);
	textureCardOx = SDL_CreateTextureFromSurface(SDLRenderer, surfaceCardOx);
	textureCardRabbit = SDL_CreateTextureFromSurface(SDLRenderer, surfaceCardRabbit);

	SDL_FreeSurface(surfaceButtonLegend);
	SDL_FreeSurface(surfaceStudent);
	SDL_FreeSurface(surfaceMaster);
	SDL_FreeSurface(surfaceTemple);
	SDL_FreeSurface(surfaceCardDragon);
	SDL_FreeSurface(surfaceCardHorse);
	SDL_FreeSurface(surfaceCardMantis);
	SDL_FreeSurface(surfaceCardOx);
	SDL_FreeSurface(surfaceCardRabbit);
}

void Renderer::DrawButtonLegend()
{
	Color color = Color::White();
	SDL_SetRenderDrawColor(SDLRenderer, color.r, color.g, color.b, color.a);

	SDL_Rect Tile;
	Tile.x = TILEPADDING;
	Tile.y = TILEPADDING * 4 + CARDHEIGHT + BOARDSIZE * TILESIZE + BOARDSIZE * TILEPADDING;
	Tile.w = CARDHEIGHT;
	Tile.h = CARDHEIGHT;
	SDL_RenderCopy(SDLRenderer, textureButtonLegend, nullptr, &Tile);
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

void Renderer::DrawMoveTiles(Game& _game, Color _color) const
{
	std::vector<Vector2> moveTiles = _game.GetValidMoves();

	if (moveTiles.empty() || _game.IsPieceSelected() == false)
	{
		return;
	}

	for (auto& moveTile : moveTiles)
	{
		SDL_SetRenderDrawColor(SDLRenderer, _color.r, _color.g, _color.b, _color.a);

		SDL_Rect Tile;
		Tile.x = SIDEPANELWIDTH + TILEPADDING + moveTile.x * TILESIZE + moveTile.x * TILEPADDING;
		Tile.y = CARDPANELHEIGHT + TILEPADDING + moveTile.y * TILESIZE + moveTile.y * TILEPADDING;
		Tile.w = TILESIZE;
		Tile.h = TILESIZE;
		SDL_RenderFillRect(SDLRenderer, &Tile);
	}
}

void Renderer::DrawTemple(const Player* _player) const
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

void Renderer::DrawPieces(Game& _game, const Player* _player)
{
	for (int u = 0; u < PIECECOUNT; u++)
	{
		if (_player->GetPlayerPiece(u)->IsCaptured() == false)
		{
			DrawSinglePiece(_game, _player->GetPlayerPiece(u));
		}
	}
}

void Renderer::DrawSinglePiece(Game& _game, Piece* _piece)
{
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

	Color color = GetPieceColor(_game, _piece);
	SDL_SetTextureColorMod(texture, color.r, color.g, color.b);
	SDL_RenderCopy(SDLRenderer, texture, nullptr, &Tile);
}

void Renderer::DrawCards(Game& _game)
{
	SDL_Rect Tile;

	std::array<Card*, CARDS> cards = _game.GetAllCards();
	Color color;

	for (auto& card : cards)
	{
		int cardRotation = card->GetOwnerColor() == E_PLAYERCOLOR::red ? 180 : 0;

		if (card == _game.GetSelectedCard())
		{
			color = cardColorSelected;
		}
		else
		{
			color = _game.IsActivePlayer(card->GetOwner()) ? cardColorInteractable : cardColor;
		}
		Vector2 tempCardPosition = _game.GetCardPositionMap().find(card->GetPositionType())->second;
		Tile.x = tempCardPosition.x;
		Tile.y = tempCardPosition.y;
		Tile.w = CARDWIDTH;
		Tile.h = CARDHEIGHT;

		SDL_Texture* tempCardTexture = cardTypeMap.find(card->GetCardType())->second;
		SDL_SetTextureColorMod(tempCardTexture, color.r, color.g, color.b);
		SDL_RenderCopyEx(SDLRenderer, tempCardTexture, nullptr, &Tile, cardRotation, nullptr, SDL_FLIP_NONE);
	}
}

Color Renderer::GetPieceColor(Game& _game, Piece* _piece)
{
	E_PLAYERCOLOR playerColor = _piece->GetOwner()->GetColor();
	bool isHovered = _game.IsHoveredPiece(_piece) && _game.IsPieceSelected() == false;
	bool isSelected = _game.IsSelectedPiece(_piece);

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

	return Color::White();
}
