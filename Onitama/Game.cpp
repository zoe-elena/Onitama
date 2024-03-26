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

Vector2 Game::GetMoveTile(Piece* _piece, Vector2 _move) const
{
	Vector2 pieceIndex = _piece->GetIndex();
	if (activePlayer == playerRed)
	{
		return Vector2(pieceIndex.x + _move.x, pieceIndex.y + _move.y);
	}
	else if (activePlayer == playerBlue)
	{
		return Vector2(pieceIndex.x - _move.x, pieceIndex.y - _move.y);
	}
	else
	{
		return Vector2(-1, -1);
	}
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
	else if (selectedCard != nullptr)
	{
		TryHoverPiece(currentMousePos);
	}
}

void Game::ResolveLeftMouseDown(Vector2 _mousePos)
{
	Vector2 mouseIndex = tileManager->GetClosestTile(_mousePos.x, _mousePos.y);
	Tile* tile = tileManager->GetTile(mouseIndex.x, mouseIndex.y);

	if (tile != nullptr)
	{
		if (selectedPiece)
		{
			if (selectedPiece == tile->GetPiece())
			{
				selectedPiece = nullptr;
			}
			else
			{
				TryMovePiece(tile);
			}
		}
		else
		{
			TrySelectPiece(tile);
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

	if (_tile->GetIsOccupied())
	{
		Piece* currentSelectedPiece = _tile->GetPiece();

		if (currentSelectedPiece->GetOwner() != activePlayer)
		{
			selectedPiece->Move(_tile);
			validMoves.clear();
			UnselectAll();
			return true;
		}
	}
	else
	{
		selectedPiece->Move(_tile);
		validMoves.clear();
		UnselectAll();
		return true;
	}

	return false;
}

bool Game::TrySelectPiece(Tile* _tile)
{
	if (_tile->GetIsOccupied())
	{
		Piece* tempPiece = _tile->GetPiece();

		if (tempPiece->GetOwner() == activePlayer)
		{
			if (TrySetMoveTiles(tempPiece))
			{
				SelectPiece(tempPiece);
				return true;
			}
		}
	}

	return false;
}

bool Game::IsValidMove(Vector2 _index)
{
	for (size_t i = 0; i < validMoves.size(); i++)
	{
		if (validMoves[i] == _index)
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
	if (tile != nullptr && tile->GetIsOccupied())
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

	std::vector<Vector2> possibleMoveTiles;
	for (size_t i = 0; i < selectedCardMoves.size(); i++)
	{
		Vector2 possibleTile = GetMoveTile(_piece, selectedCardMoves[i]);

		if (tileManager->IsInBounds(possibleTile.x, possibleTile.y) && tileManager->GetTile(possibleTile.x, possibleTile.y)->GetIsOccupied() == false)
		{
			possibleMoveTiles.push_back(possibleTile);
		}
	}

	if (possibleMoveTiles.size() != 0)
	{
		validMoves = possibleMoveTiles;
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
