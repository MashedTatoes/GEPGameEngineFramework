#include "Enemy.h"
#include "GameManager.h"
Enemy::Enemy(SDL_Texture* tex, double x, double y, Player* target)
	: Player(tex, x, y)
{
	lastAttack = SDL_GetTicks();
	attackTimeout = 1000;
	this->target = target;
	this->flippedDimensions.first = true;
	PlayState("Idle");
	
}
Enemy::~Enemy()
{

}
void Enemy::Update()
{
	this->UpdateEnemy();
	UpdateDestRect();
}

void Enemy::UpdateEnemy()
{
	PlayState("Idle");
	std::pair<int, int> moveVector = { 0,0 };



	if ((currentState.compare("Idle") == 0 || currentState.compare("Move") == 0) || animationReset) {

		moveVector = MoveTowards(target->GetX() + 50, target->GetY(), 0.7f);
	}

	if (moveVector.first != 0) {
		PlayState("Move");
	}



	else {
		
		if (target->IsAttacking() && target->GetCurrentAnimFrame() == 0) {
			int rnd = rand() % 11;
			
			if (SDL_TICKS_PASSED(SDL_GetTicks(), lastCrouch + crouchTimeout)) {
				if (rnd <= 4) {
					PlayState("Crouch");
					lastCrouch = SDL_GetTicks();
				}
				else {
					int damage = 0;
					if (target->GetCurrentState().compare("Punch") == 0) {
						damage = 5;
					}
					else if (target->GetCurrentState().compare("Kick") == 0) {
						damage = 10;
					}
					else if (target->GetCurrentState().compare("Roundhouse") == 0) {
						damage = 15;
					}
					GameManager::Instance()->DamagePlayerTwo(damage);
					lastCrouch = SDL_GetTicks();
				}
				
			}
			
			
		}
		//Attack();
	}



	spriteSrcRect.x = spriteSrcRect.w * m_iFrame; //updates the animation
}

void Enemy::Attack() {
	if (SDL_TICKS_PASSED(SDL_GetTicks(), lastAttack + attackTimeout)) {
		if (animationReset || !animStates[currentState].isInterrupt) {
			PlayState(attackPool[rand() % attackPool.size()]);
			lastAttack = SDL_GetTicks();
		}
	}

}

void Enemy::OnTargetAttack()
{
	if (CalculateNormal(target->GetX() + 50, target->GetY()).first == 0) {
		int rnd = rand() % 11;
		std::cout << rnd << std::endl;
		if (rnd <= 2) {
			PlayState("Crouch");
		}
	}
	
}
