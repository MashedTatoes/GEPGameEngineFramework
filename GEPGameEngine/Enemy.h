#pragma once
#include "Player.h"
class Enemy : public Player
{
private:
	void UpdateEnemy();
	Player* target;

	Uint32 lastAttack;
	Uint32 attackTimeout;
public:
	Enemy(SDL_Texture* tex, double x, double y, Player* target);
	~Enemy();
	//over-ride the base player class's Update funtionality
	void Update() override;
	void Attack();
	void OnTargetAttack();

};

