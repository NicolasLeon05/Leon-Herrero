#include "BaseGame.h"

class Game : public BaseGame
{
public:
	void InitGame() override;
	void Update() override;
	void DeInitGame() override;
};

void main()
{
	Game game;

	game.RunEngine();
}

void Game::InitGame()
{

}

void Game::Update()
{

}

void Game::DeInitGame()
{

}
