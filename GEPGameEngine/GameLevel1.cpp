#include "GameLevel1.h"
#include "Game.h"
#include "GameManager.h"

void GameLevel1::Enter()
{

	bgSpriteTex = Game::Instance()->LoadTexture("resources/images/bg_level1.jpg");
	mainSpriteTex = Game::Instance()->LoadTexture("resources/images/PlayerKenSprite.png");

	enemySpriteTex = Game::Instance()->LoadTexture("resources/images/PlayerKenSpriteEnemy.png");

	SDL_Rect bgDestRect;
	bgDestRect.x = bgDestRect.y = 0;
	SDL_GetWindowSize(Game::Instance()->GetWindow(), &bgDestRect.w, &bgDestRect.h);
	player = new Player(mainSpriteTex, bgDestRect.w * 0.5, bgDestRect.h - 100);

	enemy = new Enemy(enemySpriteTex, bgDestRect.w * 0.75, bgDestRect.h - 100, player);
	player->SetEnemy(enemy);

	GameState::Enter();



}

void GameLevel1::Update()
{
	
	GameState::Update();
	if (enemy) enemy->Update();
}

void GameLevel1::Render()
{

	SDL_SetRenderDrawColor(Game::Instance()->GetRenderer(), 0, 0, 0, 255); //set background window color
	SDL_RenderClear(Game::Instance()->GetRenderer()); //clear the screen

	bg->Render();

	if (player) player->Render();
	if (enemy) enemy->Render();
	char * playerHealth = new char [64];
	if (snprintf(playerHealth,64, "Health: %d", GameManager::Instance()->GetPlayerOneHealth()) >= 0) {
		ScreenState::RenderFont(true, playerHealth, 0, 0);
	}
	char * enemyHealth = new char[64];
	if (snprintf(enemyHealth, 64, "Health: %d", GameManager::Instance()->GetPlayerTwoHealth()) >= 0) {
		ScreenState::RenderFont(true, enemyHealth,800, 0);
	}
	
	//Free array to stop memory leak
	delete[] playerHealth;
	delete[] enemyHealth;

	ScreenState::Render();

	//cout << "Rendering GameLevel1" << endl;
}

void GameLevel1::Exit()
{
	GameState::Exit();
}