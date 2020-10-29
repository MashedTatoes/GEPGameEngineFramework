#pragma once

#include "ScreenState.h"
#include <vector>
#include "Button.h"
#include <string>
using namespace std;

class GameOverScreen : public ScreenState
{
private:
	vector<Button*> m_vButtons;
	enum btn {  exit };
	std::string winner;

public:
	GameOverScreen(){}
	void Update(); // Method prototype.
	void Render();
	void Enter();
	void Exit();
	void Resume() {}

};