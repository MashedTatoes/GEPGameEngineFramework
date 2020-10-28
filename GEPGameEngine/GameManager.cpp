#include "GameManager.h"

GameManager::GameManager()
{
	player1Health = 100;
	player2Health = 100;
}

GameManager* GameManager::Instance()
{
	static GameManager* instance = new GameManager();
	return instance;
}
