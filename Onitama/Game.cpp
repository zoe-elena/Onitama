#include "Game.h"
#include "Board.h"
#include "Defines.h"

Game::Game() { }

void Game::InitGame(SDL_Renderer* _renderer, SDL_Window* _window)
{
	// Create Players
	playerRed = new Player(red);
	playerBlue = new Player(blue);

	// Create Board
	Board* board = new Board();
	board->InitBoard(this, _renderer);
	renderer = _renderer;
}