#include "GameManager.h"

GameManager::GameManager()
{
	player1Health = 100;
	player2Health = 100;
	isGameOver = false;
	playerOneWins = 0;
	playerTwoWins = 0;
}

GameManager* GameManager::Instance()
{
	static GameManager* instance = new GameManager();
	return instance;
}



std::string GameManager::GetWinner()
{
	std::string winner = "Undefined";

	if (player2Health <= 0) {
		winner = "Player";
	}
	if (player1Health <= 0) {
		winner = "Computer";
	}

	return winner;
}

void GameManager::Reset()
{
	isGameOver = false;
	player1Health = 100;
	player2Health = 100;

}
