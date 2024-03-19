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
	tilemanager = new Tilemanager();
	renderer = new Renderer(_SDLRenderer, this);
}

void Game::Update()
{
	renderer->RenderGame();
}
