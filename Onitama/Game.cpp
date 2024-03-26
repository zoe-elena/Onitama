#include "Game.h"
#include <functional>

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
	playerRed->InitPieces();
	playerBlue->InitPieces();
	activePlayer = playerRed;
	UpdateAllTiles();

	cardManager = new CardManager();
	cardManager->InitCards(playerRed, playerBlue);

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

void Game::ResolveLeftMouseDown(Vector2 _mousePos)
{
	Vector2 mouseIndex = tileManager->GetClosestTile(_mousePos.x, _mousePos.y);
	Tile* tile = tileManager->GetTile(mouseIndex.x, mouseIndex.y);

	if (tile)
	{
		if (tile->IsOccupied())
		{
			Piece* tempPiece = tile->GetPiece();
			if (selectedPiece == tempPiece)
			{
				selectedPiece = nullptr;
			}
			else
			{
				TrySelectPiece(tempPiece);
			}
		}
		else if(selectedPiece)
		{
			TryMovePiece(tile);
		}
	}
	else if (activePlayer->IsOnLeftCard(_mousePos))
	{
		selectedCard = activePlayer->GetLeftCard();
	}
	else if (activePlayer->IsOnRightCard(_mousePos))
	{
		selectedCard = activePlayer->GetRightCard();
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

	if (_tile->IsOccupied() == false)
	{
		Vector2 lastIndex = selectedPiece->GetIndex();
		tileManager->GetTile(lastIndex.x, lastIndex.y)->SetPiece(nullptr);
		selectedPiece->Move(_tile);
		validMovesTileIndices.clear();
		UnselectAll();
		return true;
	}
	else if (_tile->GetOccupyingPlayer() != activePlayer)
	{
		// Capture Enemy Piece
	}

	return false;
}

bool Game::TrySelectPiece(Piece* _piece)
{
	if (_piece->GetOwner() == activePlayer)
	{
		if (TrySetMoveTiles(_piece))
		{
			SelectPiece(_piece);
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
	Vector2 mouseIndex = tileManager->GetClosestTile(_mousePos.x, _mousePos.y);
	Tile* tile = tileManager->GetTile(mouseIndex.x, mouseIndex.y);

	// Check for Piece on mouse position
	if (tile && tile->IsOccupied())
	{
		Piece* currentHoveredPiece = tile->GetPiece();

		// Check if Piece is from the active player and 
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
	if (selectedCard == nullptr)
	{
		return false;
	}

	std::vector<Vector2> selectedCardMoves = selectedCard->GetMoves();
	std::vector<Vector2> tempValidMovesTileIndices = tileManager->GetValidMoveTileIndices(selectedCardMoves, _piece->GetIndex(), activePlayer);

	if (tempValidMovesTileIndices.size() != 0)
	{
		validMovesTileIndices = tempValidMovesTileIndices;
		return true;
	}
	else
	{
		return false;
	}
}

void Game::SelectPiece(Piece* _piece)
{
	selectedPiece = _piece;
	hoveredPiece = nullptr;
}
