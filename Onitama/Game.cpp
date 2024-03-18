#include "Game.h"
#include "Defines.h"

Game::Game() { }

void Game::InitGame(SDL_Renderer* _SDLRenderer)
{
	SDLRenderer = _SDLRenderer;
	// Create Players
	playerRed = new Player(red);
	playerBlue = new Player(blue);

	// Create Renderer
	renderer = new Renderer(_SDLRenderer, this);
}

void Game::Update()
{
	renderer->RenderGame();
}
