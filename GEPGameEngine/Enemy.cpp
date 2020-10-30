#include "Enemy.h"
#include "GameManager.h"
Enemy::Enemy(SDL_Texture* tex, double x, double y, Player* target)
	: Player(tex, x, y)
{
	//TurnOn();
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
	if (currentHadouken.get() != nullptr) {
		if (currentHadouken->Update()) {
			currentHadouken.release();
		}
	}
	UpdateDestRect();
}
void Enemy::Render()
{
	if (currentHadouken.get() != nullptr) {
		currentHadouken->Render();
	}
	this->SpriteExAnimated::Render(); //invoke the base class's Render()
}

void Enemy::UpdateEnemy()
{
	
	std::pair<int, int> moveVector = { 0,0 };
	CheckForCollisions();
	if (SDL_TICKS_PASSED(SDL_GetTicks(), hadoukenTimeout + lastHadouken)) {
		std::string state = "Hadouken";
		PlayState("Hadouken");
		if (currentHadouken == nullptr) {

			isAttacking = true;
			currentHadouken = std::make_unique<Hadouken>(texture, GetX(), GetY(), -1);
			lastHadouken = SDL_GetTicks();
			lastAttack = SDL_GetTicks();
		}
		
	}
	else if ((currentState.compare("Idle") == 0 || currentState.compare("Move") == 0) || animationReset) {

		moveVector = MoveTowards(enemey->GetX() + 50, enemey->GetY(), 0.7f);
	}
	
	if (moveVector.first != 0) {
		
		if (currentState.compare("Hadouken") == 0) {
			PlayState("Hadouken");
		}
		else {
			PlayState("Move");
		}
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
		std::string state;
		if (animationReset || !animStates[currentState].isInterrupt) {
			isAttacking = true;
			std::string state = attackPool[rand() % (attackPool.size() - 1)];
			PlayState(state);
			
			lastAttack = SDL_GetTicks();
		}
	}
	else {
		PlayState("Idle");
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
				enemey->GetHadouken()->SetDestroyed(true);
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
