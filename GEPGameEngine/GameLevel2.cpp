#include "GameLevel2.h"
#include "Game.h"
#include "GameManager.h"
#include "GameOverScreen.h"
void GameLevel2::Enter()
{

	gameStart = SDL_GetTicks();
	bgSpriteTex = Game::Instance()->LoadTexture("resources/images/bg_level2.png");
	mainSpriteTex = Game::Instance()->LoadTexture("resources/images/PlayerKenSprite.png");

	enemySpriteTex = Game::Instance()->LoadTexture("resources/images/PlayerKenSpriteEnemy.png");

	SDL_Rect bgDestRect;
	bgDestRect.x = bgDestRect.y = 0;
	SDL_GetWindowSize(Game::Instance()->GetWindow(), &bgDestRect.w, &bgDestRect.h);
	player = new Player(mainSpriteTex, bgDestRect.w * 0.5, bgDestRect.h - 75);

	enemy = new Enemy(enemySpriteTex, bgDestRect.w * 0.75, bgDestRect.h - 75, player);
	player->SetEnemy(enemy);

	GameState::Enter();


}

void GameLevel2::ResetStage()
{

	if (GameManager::Instance()->Reset()) {
		Game::Instance()->GetFSM()->ChangeState(new GameOverScreen());
		return;
	}
	else {
		Game::Instance()->GetFSM()->ChangeState(new GameLevel2());
	}
}
