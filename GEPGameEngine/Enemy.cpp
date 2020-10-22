#include "Enemy.h"

Enemy::Enemy(SDL_Texture* tex, double x, double y)
    : Player(tex, x, y)
{
	this->flippedDimensions.first = true;
}
Enemy::~Enemy()
{

}
void Enemy::Update() 
{
	this->UpdateEnemy();
}

void Enemy::UpdateEnemy()
{
	PlayState("Idle");
	spriteSrcRect.x = spriteSrcRect.w * m_iFrame; //updates the animation
}