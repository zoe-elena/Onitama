#include "Game.h"

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
	activePlayer = playerBlue;
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

Vector2 Game::GetTileFromMove(Vector2 _move) const
{
	Vector2 pieceIndex = selectedPiece->GetIndex();
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

	// TODO: Select Piece and Card in one Function

	if (leftMouseButtonDown)
	{
		TrySelectTile(currentMousePos);
	}
	else if(selectedCard != nullptr)
	{
		TryHoverTile(currentMousePos);
	}
}

void Game::TrySelectTile(Vector2 _mousePos)
{
	Vector2 mouseIndex = tileManager->GetClosestTile(_mousePos.x, _mousePos.y);
	Tile* tile = tileManager->GetTile(mouseIndex.x, mouseIndex.y);

	// Check for Piece on mouse position
	if (tile != nullptr && tile->GetIsOccupied())
	{
		Piece* currentSelectedPiece = tile->GetPiece();

		// Return if piece isn't from active pslayer
		if (currentSelectedPiece->GetOwnerPlayer() == activePlayer)
		{
			selectedPiece = currentSelectedPiece;

			moveTiles = SetMoveTiles();
			if (moveTiles.size() == 0)
			{
				selectedPiece = nullptr;
			}

			// Unhover the now selected piece
			hoveredPiece = nullptr;
			return;
		}
	}
	else if (activePlayer->IsOnLeftCard(_mousePos))
	{
		selectedCard = activePlayer->GetLeftCard();
		return;
	}
	else if (activePlayer->IsOnRightCard(_mousePos))
	{
		selectedCard = activePlayer->GetRightCard();
		return;
	}

	// Unselect if clicking anywhere else
	selectedPiece = nullptr;
	selectedCard = nullptr;
}

void Game::TryHoverTile(Vector2 _mousePos)
{
	Vector2 mouseIndex = tileManager->GetClosestTile(_mousePos.x, _mousePos.y);
	Tile* tile = tileManager->GetTile(mouseIndex.x, mouseIndex.y);

	// Check for Piece on mouse position
	if (tile != nullptr && tile->GetIsOccupied())
	{
		Piece* currentHoveredPiece = tile->GetPiece();

		// Check if Piece is from the active player and 
		if (currentHoveredPiece->GetOwnerPlayer() == activePlayer)
		{
			hoveredPiece = currentHoveredPiece;
			return;
		}
	}

	// Unhover last hovered piece if no new piece gets hovered
	hoveredPiece = nullptr;
}

std::vector<Vector2> Game::SetMoveTiles()
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

		if (tileManager->IsInBounds(possibleTile.x, possibleTile.y) && tileManager->GetTile(possibleTile.x, possibleTile.y)->GetIsOccupied() == false)
		{
			possibleMoveTiles.push_back(possibleTile);
		}
	}

	return possibleMoveTiles;
}
