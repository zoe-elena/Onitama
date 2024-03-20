#include "Game.h"
#include "Defines.h"

Game::Game(SDL_Renderer* _SDLRenderer)
{
	InitGame(_SDLRenderer);
}

void Game::InitGame(SDL_Renderer* _SDLRenderer)
{
	SDLRenderer = _SDLRenderer;
	playerRed = new Player(red);
	playerBlue = new Player(blue);
	tileManager = new TileManager();
	inputManager = new InputManager();
	playerRed->InitPlayerPieces();
	playerBlue->InitPlayerPieces();
	activePlayer = playerRed;
	UpdateAllTiles();
	renderer = new Renderer(_SDLRenderer, this);
}

void Game::Update()
{
	inputManager->PollEvents();

	DoTurn();

	renderer->DrawGame();
	renderer->RenderGame();
}

void Game::UpdateAllTiles()
{
	for (size_t i = 0; i < playerRed->PlayerPieces.size(); i++)
	{
		Piece* currentPiece = playerRed->PlayerPieces[i];
		Vector2 currentPieceIndex = currentPiece->GetIndex();
		tileManager->SetTilePiece(currentPieceIndex.x, currentPieceIndex.y, currentPiece);
	}

	for (size_t i = 0; i < playerBlue->PlayerPieces.size(); i++)
	{
		Piece* currentPiece = playerBlue->PlayerPieces[i];
		Vector2 currentPieceIndex = currentPiece->GetIndex();
		tileManager->SetTilePiece(currentPieceIndex.x, currentPieceIndex.y, currentPiece);
	}
}

void Game::DoTurn()
{
	Vector2 currentMousePos = inputManager->GetMousePosition();
	Vector2 currentMouseIndex = tileManager->GetClosestTile(currentMousePos.x, currentMousePos.y);

	CheckHoverPiece(currentMouseIndex);
}

void Game::CheckHoverPiece(Vector2 _mouseIndex)
{
	Tile* tile = tileManager->GetTile(_mouseIndex.x, _mouseIndex.y);

	Piece* lastHoveredPiece = activePlayer->GetHoveredPiece();

	if (tile != nullptr) {
		if (tile->GetIsOccupied())
		{
			Piece* currentHoveredPiece = tile->GetPiece();

			if (currentHoveredPiece == lastHoveredPiece)
			{
				return;
			}
			else
			{
				currentHoveredPiece->SetIsHovered(true);
				activePlayer->SetHoveredPiece(currentHoveredPiece);

				if (lastHoveredPiece != nullptr)
				{
					lastHoveredPiece->SetIsHovered(false);
				}

				return;
			}
		}
	}

	if (lastHoveredPiece != nullptr)
	{
		activePlayer->SetHoveredPiece(nullptr);
		lastHoveredPiece->SetIsHovered(false);
	}
}

