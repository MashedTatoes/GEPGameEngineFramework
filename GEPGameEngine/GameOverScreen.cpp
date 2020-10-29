#include "GameOverScreen.h"
#include <iostream>
#include "Game.h"
#include "MainMenuState.h"
#include "GameManager.h"
using namespace std;

// Begin PauseState
void GameOverScreen::Enter()
{
	m_pFont = TTF_OpenFont("Font/LTYPE.TTF", 30);
	m_vButtons.push_back(new Button("Img/exit.png", { 0,0,400,100 }, { 412,400,200,80 }));

}

void GameOverScreen::Update()
{
	// Update buttons. Allows for mouseovers.
	for (int i = 0; i < (int)m_vButtons.size(); i++)
		m_vButtons[i]->Update();

	//close the pause menu popup
	
	//else if exit was clicked, we need to go back to main menu
	 if (m_vButtons[btn::exit]->Clicked())
	{
		Game::Instance()->GetFSM()->Clean(); // Clear all states, including GameState on bottom.
		//go back to main menu
		Game::Instance()->GetFSM()->ChangeState(new MainMenuState());
		return;
	}
	


}


void GameOverScreen::Render()
{

	SDL_RenderClear(Game::Instance()->GetRenderer());
	//Game::Instance()->GetFSM()->GetStates().front()->Render();
	//SDL_SetRenderDrawBlendMode(Game::Instance()->GetRenderer(), SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(Game::Instance()->GetRenderer(), 64, 64, 128, 128);

	//draw background 
	SDL_Rect rect = { 256, 128, 512, 512 };
	SDL_RenderFillRect(Game::Instance()->GetRenderer(), &rect);

	//draw the buttons
	for (int i = 0; i < (int)m_vButtons.size(); i++)
		m_vButtons[i]->Render();
	char* text = new char[64];
	if (snprintf(text, 64, "Game over %s wins!", GameManager::Instance()->GetGameWinner().c_str()) >= 0) {
		RenderFont(true, text, 400, 0);
	}
	delete[] text;

	ScreenState::Render();

}


void GameOverScreen::Exit()
{

	cout << "Exiting Pause..." << endl;

	for (int i = 0; i < (int)m_vButtons.size(); i++)
	{
		delete m_vButtons[i];
		m_vButtons[i] = nullptr;
	}
	m_vButtons.clear();
	m_vButtons.shrink_to_fit();
}

