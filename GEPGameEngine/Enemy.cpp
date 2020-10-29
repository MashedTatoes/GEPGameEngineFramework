#include "Enemy.h"
#include "GameManager.h"
Enemy::Enemy(SDL_Texture* tex, double x, double y, Player* target)
	: Player(tex, x, y)
{
	m_dRadius = 10;
	lastAttack = SDL_GetTicks();
	attackTimeout = 1500;
	this->SetEnemy(target);
	this->flippedDimensions.first = true;
	PlayState("Idle");
	for (auto& state : this->attackPool) {
		animStates[state].AddCallbackOnComplete(std::bind(&Player::OnAttackCompleted, this));
	}
	
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

		moveVector = MoveTowards(enemey->GetX() + 50, enemey->GetY(), 0.7f);
	}
	CheckForCollisions();
	if (moveVector.first != 0) {
		PlayState("Move");
	}


	
	else {
		
		if (enemey->IsAttacking() && enemey->GetCurrentAnimFrame() == 0) {
			if (!TryAvoidAttack())
			{
				int damage = 0;
				if (enemey->GetCurrentState().compare("Punch") == 0) {
					damage = 5;
				}
				else if (enemey->GetCurrentState().compare("Kick") == 0) {
					damage = 10;
				}
				else if (enemey->GetCurrentState().compare("Roundhouse") == 0) {
					damage = 15;
				}

				GameManager::Instance()->DamagePlayerTwo(damage);
			}
			
			
		}
		else {
			Attack();
		}
		
	}



	spriteSrcRect.x = spriteSrcRect.w * m_iFrame; //updates the animation
}

void Enemy::Attack() {
	if (SDL_TICKS_PASSED(SDL_GetTicks(), lastAttack + attackTimeout)) {
		if (animationReset || !animStates[currentState].isInterrupt) {
			isAttacking = true;
			PlayState(attackPool[rand() % attackPool.size()]);
			lastAttack = SDL_GetTicks();
		}
	}

}

void Enemy::OnTargetAttack()
{
	if (CalculateNormal(enemey->GetX() + 50, enemey->GetY()).first == 0) {
		int rnd = rand() % 11;
		std::cout << rnd << std::endl;
		if (rnd <= 2) {
			PlayState("Crouch");
		}
	}
	
}

void Enemy::CheckForCollisions() {
	if (enemey->GetHadouken() != nullptr) {
		if (CircleCollisionTest(enemey->GetHadouken()->GetX(), enemey->GetHadouken()->GetY(), GetX(), GetY(), enemey->GetHadouken()->GetRadius(), GetRadius())) {
			if (!TryAvoidAttack()) {
				GameManager::Instance()->DamagePlayerTwo(30);
			}
		}
	}
	
}

bool Enemy::TryAvoidAttack() {
	int rnd = rand() % 11;

	if (SDL_TICKS_PASSED(SDL_GetTicks(), lastCrouch + crouchTimeout)) {
		if (rnd <= 4) {
			PlayState("Crouch");
			lastCrouch = SDL_GetTicks();
			return true;
		}
		else {
			lastCrouch = SDL_GetTicks();
			return false;
		}

	}
}
