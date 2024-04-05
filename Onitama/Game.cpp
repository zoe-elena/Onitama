#include <functional>
#include <random>
#include "Game.h"
#include "Action.h"
#include "MoveAction.h"
#include "SelectCardAction.h"
#include "SelectPieceAction.h"

Game::Game(SDL_Renderer* _sdlRenderer) :
	playerRed(E_PLAYERCOLOR::red), playerBlue(E_PLAYERCOLOR::blue), cardManager(&playerRed, &playerBlue)
{
	InitGame();
}

void Game::InitGame()
{
	std::mt19937 rng(std::random_device{}());
	std::uniform_int_distribution<int> dist(0, 99);
	int random = dist(rng);
	activePlayer = random < 50 ? &playerRed : &playerBlue;

	UpdateTilePointer();
	cardManager.InitCards(activePlayer);
}

void Game::Update()
{
	inputManager.PollEvents();

	if (inputManager.IsLeftArrowButtonPressed())
	{
		actionStack.UndoLastAction(*this);
		return;
	}

	if (CheckForGameEnd() || isWin)
	{
		return;
	}

	DoTurn();
}

void Game::UpdateTilePointer()
{
	for (size_t i = 0; i < PIECECOUNT; i++)
	{
		tileManager.SetTilePiece(playerRed.GetPlayerPiece(static_cast<int>(i)));
		tileManager.SetTilePiece(playerBlue.GetPlayerPiece(static_cast<int>(i)));
	}
}

bool Game::CheckForGameEnd()
{
	if (inputManager.IsQuitButtonPressed())
	{
		hasQuit = true;
		return true;
	}
	else if (inputManager.IsRestartButtonPressed())
	{
		hasRestart = true;
		return true;
	}

	return false;
}

void Game::DoTurn()
{
	Vector2 currentMousePos = inputManager.GetMousePosition();
	bool leftMouseButtonDown = inputManager.IsLeftMouseButtonPressed();

	if (leftMouseButtonDown)
	{
		ResolveLeftMouseButtonPressed(currentMousePos);
	}
	else if (selectedCard)
	{
		TryHoverPiece(currentMousePos);
	}
}

void Game::ResolveLeftMouseButtonPressed(Vector2 _mousePos)
{
	Vector2 tileIndex = tileManager.GetClosestTile(_mousePos);
	Tile selectedTile = tileManager.GetTile(tileIndex);
	E_CARDPOSITIONTYPE cardPositionType = cardManager.CheckCardHover(activePlayer->GetColor(), _mousePos);

	if (tileManager.IsInBounds(selectedTile))
	{
		Piece* nextSelectedPiece = selectedTile.GetOccupyingPiece();

		if (selectedCard != nullptr && selectedPiece != nullptr)
		{
			if (IsValidMove(selectedTile.GetIndex()))
			{
				auto* action = new MoveAction(selectedTile, selectedPiece, selectedCard, selectedTile.GetOccupyingPiece(), activePlayer);
				actionStack.ExecuteAction(action, *this);
			}
		}
		else if (nextSelectedPiece != nullptr && TrySelectPiece(nextSelectedPiece))
		{
			auto* action = new SelectPieceAction(nextSelectedPiece, activePlayer);
			actionStack.ExecuteAction(action, *this);
		}
	}
	else if (selectedCard == nullptr && cardPositionType != E_CARDPOSITIONTYPE::none)
	{
		auto* action = new SelectCardAction(cardManager.GetCard(cardPositionType), activePlayer);
		actionStack.ExecuteAction(action, *this);
	}
}

void Game::TryHoverPiece(Vector2 _mousePos)
{
	Vector2 mouseIndex = tileManager.GetClosestTile(_mousePos);
	Tile tile = tileManager.GetTile(mouseIndex);

	// Check for Piece on mouse position
	if (tileManager.IsInBounds(tile) && tile.IsOccupied())
	{
		Piece* currentHoveredPiece = tile.GetOccupyingPiece();

		if (currentHoveredPiece->GetOwnerColor() == activePlayer->GetColor())
		{
			hoveredPiece = currentHoveredPiece;
			return;
		}
	}

	// Unhover last hovered piece if no new piece gets hovered
	hoveredPiece = nullptr;
}

void Game::SelectCard(Card* _card)
{
	selectedCard = _card;
}

bool Game::TrySelectPiece(Piece* _piece)
{
	return _piece->GetOwnerColor() == activePlayer->GetColor() && TrySetMoveTiles(selectedCard, _piece, activePlayer);
}

bool Game::TrySetMoveTiles(Card* _card, Piece* _piece, Player* _activePlayer)
{
	if (_card == nullptr || _piece == nullptr)
	{
		return false;
	}

	std::vector<Vector2> selectedCardMoves = _card->GetMoves();
	std::vector<Vector2> tempValidMovesTileIndices = tileManager.GetValidMoveTileIndices(selectedCardMoves, _piece->GetIndex(), _activePlayer);

	if (tempValidMovesTileIndices.empty() == false)
	{
		validMovesTileIndices = tempValidMovesTileIndices;
		return true;
	}

	return false;
}

void Game::SelectPiece(Piece* _piece)
{
	selectedPiece = _piece;
}

const bool Game::IsValidMove(const Vector2 _index) const
{
	for (auto& tileIndex : validMovesTileIndices)
	{
		if (tileIndex == _index)
		{
			return true;
		}
	}

	return false;
}

void Game::MovePiece(Tile _selectedTile, Piece* _selectedPiece, Card* _selectedCard, Piece* _capturedPiece, Player* _activePlayer)
{
	tileManager.TryCapturePiece(_selectedTile);
	tileManager.ClearTile(_selectedPiece->GetIndex());
	_selectedPiece->SetIndex(_selectedTile.GetIndex());
	tileManager.SetTilePiece(_selectedPiece);
	validMovesTileIndices.clear();

	if (CheckForWin(_capturedPiece))
	{
		DoWin();
	}
	else
	{
		cardManager.MoveCardsAlong(_activePlayer, _selectedCard);
		NextPlayer(_activePlayer);
	}

	UnselectAll();
}

void Game::MovePieceBack(Tile _prevTile, Piece* _piece, Card* _selectedCard, Card* _prevSideCard, Piece* _capturedPiece, Player* _lastActivePlayer)
{
	// Respawn piece
	if (_capturedPiece != nullptr)
	{
		tileManager.SetTilePiece(_capturedPiece);
		_capturedPiece->SetCaptured(false);
	}
	else
	{
		tileManager.ClearTile(_piece->GetIndex());
	}

	// Move piece back
	selectedPiece = _piece;
	_piece->SetIndex(_prevTile.GetIndex());
	tileManager.SetTilePiece(_piece);

	selectedCard = _selectedCard;
	if (isWin == false)
	{
		cardManager.MoveCardsBack(_lastActivePlayer, _prevSideCard);
	}
	isWin = false;

	activePlayer = _lastActivePlayer;
	TrySetMoveTiles(selectedCard, selectedPiece, activePlayer);
}

const bool Game::CheckForWin(const Piece* _capturedPiece) const
{
	if (_capturedPiece && _capturedPiece->IsMaster())
	{
		return true;
	}

	if (selectedPiece->IsMaster())
	{
		if (activePlayer == &playerRed)
		{
			return selectedPiece->GetIndex() == playerBlue.GetTemplePosition();
		}
		else if (activePlayer == &playerBlue)
		{
			return selectedPiece->GetIndex() == playerRed.GetTemplePosition();
		}
	}

	return false;
}

void Game::DoWin()
{
	winningPlayer = activePlayer;
	activePlayer = nullptr;
	isWin = true;
}

void Game::NextPlayer(const Player* _activePlayer)
{
	if (_activePlayer == &playerRed)
	{
		activePlayer = &playerBlue;
	}
	else
	{
		activePlayer = &playerRed;
	}
}

void Game::UnselectAll()
{
	selectedCard = nullptr;
	selectedPiece = nullptr;
}
