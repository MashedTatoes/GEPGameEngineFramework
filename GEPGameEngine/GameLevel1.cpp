#include "GameLevel1.h"
#include "Game.h"
void GameLevel1::Enter()
{
	bgSpriteTex = Game::Instance()->LoadTexture("resources/images/bg_level1.jpg");
	mainSpriteTex = Game::Instance()->LoadTexture("resources/images/PlayerKenSprite.png");
	
	enemySpriteTex = Game::Instance()->LoadTexture("resources/images/PlayerKenSpriteEnemy.png");
	
	SDL_Rect bgDestRect;
	bgDestRect.x = bgDestRect.y = 0;
	SDL_GetWindowSize(Game::Instance()->GetWindow(), &bgDestRect.w, &bgDestRect.h);

	
	enemy = new Enemy(enemySpriteTex, bgDestRect.w * 0.75, bgDestRect.h - 90);


	GameState::Enter();

	

}

void GameLevel1::Update()
{
	if (enemy) enemy->Update();
	GameState::Update();
}

void GameLevel1::Render()
{
	
	SDL_SetRenderDrawColor(Game::Instance()->GetRenderer(), 0, 0, 0, 255); //set background window color
	SDL_RenderClear(Game::Instance()->GetRenderer()); //clear the screen

	bg->Render();

	if (player) player->Render();
	if (enemy) enemy->Render();

	ScreenState::Render();
	
	//cout << "Rendering GameLevel1" << endl;
}

void GameLevel1::Exit()
{
	GameState::Exit();
}