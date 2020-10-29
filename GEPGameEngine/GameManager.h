#pragma once
#include <string>
class GameManager
{
private:
	int player1Health;
	int player2Health;
	bool isGameOver;
	int playerOneWins;
	int playerTwoWins;
	
public:
	GameManager();
	static GameManager* Instance(); //singleton instance reference
	int GetPlayerOneHealth() { return player1Health; }
	int GetPlayerTwoHealth() { return player2Health; }
	void DamagePlayerOne(int amt) {
		player1Health -= amt;
		if (player1Health <= 0) {
			isGameOver = true;
		}
		
	}
	void DamagePlayerTwo(int amt) {
		player2Health -= amt;
		if (player2Health <= 0) {
			isGameOver = true;
		}
	}
	bool IsGameOver() { return isGameOver; }
	std::string GetWinner();
	void Reset();
	void SetPlayerOneWins(int wins) { playerOneWins = wins; }
	void SetPlayerTwoWins(int wins) { playerTwoWins = wins; }

	int GetPlayerOneWins() { return playerOneWins; }
	int GetPlayerTwoWins() { return playerTwoWins; }

};

