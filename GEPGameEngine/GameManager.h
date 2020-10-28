#pragma once
class GameManager
{
private:
	int player1Health;
	int player2Health;
public:
	GameManager();
	static GameManager* Instance(); //singleton instance reference
	int GetPlayerOneHealth() { return player1Health; }
	int GetPlayerTwoHealth() { return player2Health; }
	void DamagePlayerOne(int amt) {
		player1Health -= amt;
	}
	void DamagePlayerTwo(int amt) {
		player2Health -= amt;
	}
};

