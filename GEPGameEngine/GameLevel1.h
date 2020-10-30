#pragma once
#include "GameState.h"
#include "Player.h"
#include "Enemy.h"
class GameLevel1 : public GameState
{
protected:
	SDL_Texture* enemySpriteTex;//load and store the enemy sprite texture
	Enemy* enemy;
	int gameStart;
public:
	GameLevel1(){}
	void Enter() override;
	void Update() override;
	void Render() override;
	void Exit() override;
	virtual void ResetStage();

};