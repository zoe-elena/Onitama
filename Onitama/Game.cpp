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
	selectedCard = cardManager->GetCard(E_CARDTYPE::debug);

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

std::vector<Vector2> Game::GetPossibleMoveTiles() const
{
	if (selectedPiece == nullptr || selectedCard == nullptr)
	{
		return std::vector<Vector2>();
	}

	std::vector<Vector2> possibleMoves = cardManager->GetCard(E_CARDTYPE::debug)->GetMoves();

	std::vector<Vector2> possibleMoveTiles;
	for (size_t i = 0; i < possibleMoves.size(); i++)
	{
		Vector2 possibleTile = GetTileFromMove(possibleMoves[i]);

		if (tileManager->IsInBounds(possibleTile.x, possibleTile.y))
		{
			possibleMoveTiles.push_back(possibleTile);
		}
	}

	return possibleMoveTiles;
}

Vector2 Game::GetTileFromMove(Vector2 _move) const
{
	Vector2 pieceIndex = selectedPiece->GetIndex();
	return Vector2(pieceIndex.x - _move.x, pieceIndex.y - _move.y);
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

	// Check for Piece on mouse position
	if (tile != nullptr)
	{
		if (tile->GetIsOccupied())
		{
			Piece* currentHoveredPiece = tile->GetPiece();

			// Check if Piece is from the active player
			if (currentHoveredPiece->GetOwnerPlayer() == activePlayer)
			{
				if (selectedPiece != currentHoveredPiece && _leftMouseButtonDown)
				{
					selectedPiece = currentHoveredPiece;
				}

				if (currentHoveredPiece == lastHoveredPiece)
				{
					return;
				}

				hoveredPiece = currentHoveredPiece;
				return;
			}
		}
	}

	// Unselect if clicking anywhere else
	if (_leftMouseButtonDown)
	{
		selectedPiece = nullptr;
	}

	// Unhover last hovered piece if not hovered anymore
	if (lastHoveredPiece != nullptr)
	{
		hoveredPiece = nullptr;
	}
}
