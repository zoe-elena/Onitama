#include "Game.h"
#include "Defines.h"

Game::Game(SDL_Renderer* _SDLRenderer)
{
	InitGame(_SDLRenderer);
}

void Game::InitGame(SDL_Renderer* _SDLRenderer)
{
	playerRed = new Player(E_PLAYERCOLOR::red);
	playerBlue = new Player(E_PLAYERCOLOR::blue);
	tileManager = new TileManager();
	inputManager = new InputManager();
	playerRed->InitPlayerPieces();
	playerBlue->InitPlayerPieces();
	activePlayer = playerBlue;
	UpdateAllTiles();

	cardManager = new CardManager();
	cardManager->InitCards();
	cardManager->GetCard(E_CARDTYPE::debug)->SetOwner(playerRed);

	SDLRenderer = _SDLRenderer;
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
	bool leftMouseButtonDown = inputManager->GetMouseButtonDown();

	CheckHoverSelectPiece(currentMouseIndex, leftMouseButtonDown);
}

void Game::CheckHoverSelectPiece(Vector2 _mouseIndex, bool _leftMouseButtonDown)
{
	Tile* tile = tileManager->GetTile(_mouseIndex.x, _mouseIndex.y);
	Piece* lastHoveredPiece = hoveredPiece;

	if (tile != nullptr)
	{
		if (tile->GetIsOccupied())
		{
			Piece* currentHoveredPiece = tile->GetPiece();

			if (selectedPiece != currentHoveredPiece && _leftMouseButtonDown)
			{
				selectedPiece = currentHoveredPiece;
			}

			if (currentHoveredPiece == lastHoveredPiece || currentHoveredPiece->GetOwnerPlayer() != activePlayer)
			{
				return;
			}

			hoveredPiece = currentHoveredPiece;
			return;
		}
	}

	if (lastHoveredPiece != nullptr)
	{
		hoveredPiece = nullptr;
	}
}
