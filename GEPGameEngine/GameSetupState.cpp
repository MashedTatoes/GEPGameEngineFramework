#include "GameSetupState.h"
#include "Game.h"
#include "GameLevel1.h"

void GameSetupState::Enter()
{
	cout << "Entering GameSetup...\n";
	Game::Instance()->SetLeftMouse(false);

	//m_vButtons.push_back(new Button("Img/play.png", { 0,0,400,100 }, { 312,200,400,100 }));
	//m_vButtons.push_back(new Button("Img/play.png", { 0,0,400,100 }, { 312,400,400,100 }));
	string font = "Font/LTYPE.TTF";
	string level1 = "Level 1";
	string level2 = "Level 2";
	string level3 = "Level 3";
	m_vButtons.push_back(new LabeledButton("Img/BlueButton.png", { 0, 0, 190, 49 }, { 312,200,190,49 }, level1.c_str(), font.c_str(), 10, { 255, 255, 255, 255 }));
	m_vButtons.push_back(new LabeledButton("Img/BlueButton.png", { 0, 0, 190, 49 }, { 312,400,190,49 }, level2.c_str(), font.c_str(), 10, { 255, 255, 255, 255 }));
	m_vButtons.push_back(new LabeledButton("Img/BlueButton.png", { 0, 0, 190, 49 }, { 312,600,190,49 }, level3.c_str(), font.c_str(), 10, { 255, 255, 255, 255 }));
}

void GameSetupState::Update()
{

	// Update buttons. Allows for mouseovers.
	for (int i = 0; i < (int)m_vButtons.size(); i++)
		m_vButtons[i]->Update();

	if (m_vButtons[btn::level1]->Clicked())
	{
		Game::Instance()->GetFSM()->ChangeState(new GameLevel1());
	}

	else if (m_vButtons[btn::level2]->Clicked())
	{
		Game::Instance()->GetFSM()->ChangeState(new GameLevel1());
	}

	else if (m_vButtons[btn::level3]->Clicked())
	{
		Game::Instance()->GetFSM()->ChangeState(new GameLevel1());
	}

}


void GameSetupState::Render()
{


	SDL_SetRenderDrawColor(Game::Instance()->GetRenderer(), 255, 128, 0, 255);
	SDL_RenderClear(Game::Instance()->GetRenderer());



	for (int i = 0; i < (int)m_vButtons.size(); i++)
		m_vButtons[i]->Render();


	ScreenState::Render();

}

void GameSetupState::Exit()
{
	cout << "Exiting GameSetup...\n";

	for (int i = 0; i < (int)m_vButtons.size(); i++)
	{
		delete m_vButtons[i];
		m_vButtons[i] = nullptr;
	}
	m_vButtons.clear();
	m_vButtons.shrink_to_fit();

}
