#pragma once
#include "Player.h"
class Enemy : public Player
{
private:
	void UpdateEnemy();
public:
	Enemy(SDL_Texture* tex, double x, double y);
	~Enemy();
	//over-ride the base player class's Update funtionality
	void Update() override;
	

};

