#include "GameLevel1.h"
#include "Game.h"
void GameLevel1::Enter()
{
	bgSpriteTex = Game::Instance()->LoadTexture("resources/images/bg_level1.jpg");
	mainSpriteTex = Game::Instance()->LoadTexture("resources/images/PlayerKenSprite.png");
	GameState::Enter();
}