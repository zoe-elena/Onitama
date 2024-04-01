#include "Game.h"
#include <functional>
#include <random>

Game::Game(SDL_Renderer* _SDLRenderer)
{
	SDLRenderer = _SDLRenderer;

	InitGame();
}

void Game::InitGame()
{
	tileManager = new TileManager();
	inputManager = new InputManager();
	playerRed = new Player(E_PLAYERCOLOR::red);
	playerBlue = new Player(E_PLAYERCOLOR::blue);

	std::mt19937 rng(std::random_device{}());
	std::uniform_int_distribution<int> dist(0, 99);
	int random = dist(rng);
	activePlayer = random < 50 ? playerRed : playerBlue;
	//activePlayer = playerRed;

	UpdateAllTiles();
	cardManager = new CardManager(playerRed, playerBlue, activePlayer);
	renderer = new Renderer(SDLRenderer, this);
}

void Game::RestartGame()
{
	delete(cardManager);
	delete(tileManager);
	delete(inputManager);
	delete(renderer);
	delete(playerRed);
	delete(playerBlue);

	InitGame();
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
		Vector2 currentPieceIndex = currentPiece->Index;
		tileManager->SetTilePiece(currentPieceIndex, currentPiece);
	}

	for (size_t i = 0; i < playerBlue->PlayerPieces.size(); i++)
	{
		Piece* currentPiece = playerBlue->PlayerPieces[i];
		Vector2 currentPieceIndex = currentPiece->Index;
		tileManager->SetTilePiece(currentPieceIndex, currentPiece);
	}
}

void Game::DoTurn()
{
	Vector2 currentMousePos = inputManager->GetMousePosition();
	bool leftMouseButtonDown = inputManager->GetMouseButtonDown();

	if (leftMouseButtonDown)
	{
		ResolveLeftMouseDown(currentMousePos);
	}
	else if (selectedCard)
	{
		TryHoverPiece(currentMousePos);
	}
}

void Game::NextTurn()
{
	if (activePlayer == playerRed)
	{
		activePlayer = playerBlue;
	}
	else
	{
		activePlayer = playerRed;
	}
}

bool Game::IsWin()
{
	if (activePlayer == playerRed)
	{
		return selectedPiece->Index == playerBlue->GetTemplePosition();
	}
	else if (activePlayer == playerBlue)
	{
		return selectedPiece->Index == playerRed->GetTemplePosition();
	}
}

void Game::UnselectAll()
{
	selectedCard = nullptr;
	selectedPiece = nullptr;
}

void Game::ResolveLeftMouseDown(Vector2 _mousePos)
{
	Vector2 mouseIndex = tileManager->GetClosestTile(_mousePos);
	Tile* tile = tileManager->GetTile(mouseIndex);
	E_CARDPOSITIONTYPE cardPositionType = cardManager->CheckCardHover(activePlayer->GetColor(), _mousePos);

	if (tile)
	{
		Piece* tempSelectedPiece = tile->OccupyingPiece;

		if (selectedPiece && TryMovePiece(tile))
		{
			return;
		}

		TrySelectPiece(tempSelectedPiece);
	}
	else if (cardPositionType != E_CARDPOSITIONTYPE::none)
	{
		selectedCard = cardManager->GetCard(cardPositionType);
		TrySetMoveTiles(selectedPiece);
	}
	else
	{
		UnselectAll();
	}
}

bool Game::TryMovePiece(Tile* _tile)
{
	if (IsValidMove(_tile->GetIndex()) == false)
	{
		return false;
	}

	if (_tile->IsOccupied())
	{
		tileManager->CapturePiece(_tile->GetIndex());
	}

	tileManager->ClearTile(selectedPiece->Index);
	selectedPiece->Move(_tile);
	validMovesTileIndices.clear();
	cardManager->MoveCardsAlong(activePlayer, selectedCard);

	if (IsWin() == false)
	{
		NextTurn();
	}
	else
	{
		RestartGame();
	}

	UnselectAll();
	return true;
}

bool Game::TrySelectPiece(Piece* _piece)
{
	if (_piece == nullptr || selectedPiece == _piece)
	{
		selectedPiece = nullptr;
		return false;
	}

	if (_piece->GetOwner() == activePlayer)
	{
		if (TrySetMoveTiles(_piece))
		{
			return true;
		}
	}

	return false;
}

bool Game::IsValidMove(Vector2 _index)
{
	for (size_t i = 0; i < validMovesTileIndices.size(); i++)
	{
		if (validMovesTileIndices[i] == _index)
		{
			return true;
		}
	}

	return false;
}

void Game::TryHoverPiece(Vector2 _mousePos)
{
	Vector2 mouseIndex = tileManager->GetClosestTile(_mousePos);
	Tile* tile = tileManager->GetTile(mouseIndex);

	// Check for Piece on mouse position
	if (tile && tile->IsOccupied())
	{
		Piece* currentHoveredPiece = tile->OccupyingPiece;

		if (currentHoveredPiece->GetOwner() == activePlayer)
		{
			hoveredPiece = currentHoveredPiece;
			return;
		}
	}

	// Unhover last hovered piece if no new piece gets hovered
	hoveredPiece = nullptr;
}

bool Game::TrySetMoveTiles(Piece* _piece)
{
	if (selectedCard == nullptr || _piece == nullptr)
	{
		return false;
	}

	std::vector<Vector2> selectedCardMoves = selectedCard->GetMoves();
	std::vector<Vector2> tempValidMovesTileIndices = tileManager->GetValidMoveTileIndices(selectedCardMoves, _piece->Index, activePlayer);

	if (tempValidMovesTileIndices.size() != 0)
	{
		validMovesTileIndices = tempValidMovesTileIndices;
		selectedPiece = _piece;
		hoveredPiece = nullptr;
		return true;
	}
	else
	{
		return false;
	}
}
