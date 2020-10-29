#include "Player.h"
#include "Game.h"
#include <algorithm> //for min/max functions
#include "GameManager.h"
Player::Player(SDL_Texture* tex, double x, double y)
    : SpriteExAnimated(tex, x - 50, y - 50, 0)
{
    lastHadouken = SDL_GetTicks();
    hadoukenTimeout = 4000;
    spriteSrcRect = { 0,0,70,80 };
    spriteDestRect = { (int)(m_X - 50),(int)(m_Y - 50)  ,70,80 };
    m_velX = 0.7f;
    m_DY = 0.1f;
    m_dRadius = 10;
    ground = m_Y;
    health = 250;
    lastCrouch = SDL_GetTicks();
    crouchTimeout = 150;
    AddAnimState("Hadouken", AnimStateDefinition(0, 4, 90));
    AddAnimState("Idle", AnimStateDefinition(1, 4, 90, true, false));
    AddAnimState("Punch", AnimStateDefinition(2, 3, 90));
    AddAnimState("Move", AnimStateDefinition(3, 5, 90, true,false));
    AddAnimState("Kick", AnimStateDefinition(6, 5, 90));
    AddAnimState("Roundhouse", AnimStateDefinition(7, 5, 90));
    AddAnimState("Jump", AnimStateDefinition(8, 7, 90));
    AddAnimState("Crouch", AnimStateDefinition(9, 1, 360,false,true));
    this->attackPool.push_back("Punch");
    this->attackPool.push_back("Kick");
    this->attackPool.push_back("Roundhouse");
    this->attackPool.push_back("Hadouken");
    animStates["Jump"].AddCallbackOnComplete(std::bind(&Player::OnJumpAnimComplete, this));
    for (auto& state : this->attackPool) {
        animStates[state].AddCallbackOnComplete(std::bind(&Player::OnAttackCompleted, this));
    }
    invincibiltyTime = 500;
    invinvibilityStart = SDL_GetTicks();
}
Player::~Player()
{

}
void Player::Render()
{
    if (currentHadouken.get() != nullptr) {
       currentHadouken->Render();
    }
    this->SpriteExAnimated::Render(); //invoke the base class's Render()
}

void Player::Update()
{

    this->UpdatePlayer();
}
void Player::MovePlayer(bool isFwd)
{
    if (isFwd)
        m_X += m_velX;
    else
        m_X -= m_velX;
    PlayState("Move");
}
void Player::Jump()
{
    m_velY += m_DY;
    m_velY = min(max(m_velY, -(m_velMax * fabs(m_DY))), (m_velMax * fabs(m_DY)));
    if (m_iFrame < 3)
    {
        m_Y -= m_velY;
    }
    else if (m_iFrame > 3)
    {
        m_Y += m_velY;
    }
}
void Player::UpdatePlayer()
{
    
    //press D to move right... A to move left
    if (Game::Instance()->KeyDown(SDL_SCANCODE_D))
        this->MovePlayer(true);
    else if (Game::Instance()->KeyDown(SDL_SCANCODE_A))
        this->MovePlayer(false);
    else if (Game::Instance()->KeyDown(SDL_SCANCODE_SPACE))
    {
        PlayState("Jump");
        //do jump here
    }
    else if (Game::Instance()->KeyDown(SDL_SCANCODE_P))
    {
        Attack("Punch");
        isAttacking = true;
        //play punch animation here
    }
    else if (Game::Instance()->KeyDown(SDL_SCANCODE_K)) {
        Attack("Kick");
        isAttacking = true;
    }


    else if (Game::Instance()->KeyDown(SDL_SCANCODE_RETURN)) {
        if (SDL_TICKS_PASSED(SDL_GetTicks(), lastHadouken + hadoukenTimeout)) {
            if (currentHadouken == nullptr) {
                Attack("Hadouken");
                    isAttacking = true;
                    currentHadouken = std::make_unique<Hadouken>(texture, GetX(), GetY(), 1);
            }
        }
        

    }
    else if (Game::Instance()->KeyDown(SDL_SCANCODE_R)) {
        Attack("Roundhouse");
        isAttacking = true;
    }
    else if (Game::Instance()->KeyDown(SDL_SCANCODE_LSHIFT)) {
        PlayState("Crouch");

    }
    else  //idle animation
    {
        PlayState("Idle");
    }

    if (currentState == "Jump")
        Jump();
    spriteSrcRect.x = spriteSrcRect.w * m_iFrame; //updates the animation
    
    
    //In attack range
    if (CalculateNormal(enemey->GetX() - 50, enemey->GetY()).first == 0) {
        if (currentState.compare("Crouch") != 0 && enemey->isAttacking) {
            if (SDL_TICKS_PASSED(SDL_GetTicks(), invincibiltyTime + invinvibilityStart)) {
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

                GameManager::Instance()->DamagePlayerOne(damage);
                invinvibilityStart = SDL_GetTicks();
            }
            
            
        }
    }
    if (enemey->GetHadouken() != nullptr) {
        if (CircleCollisionTest(enemey->GetHadouken()->GetX(), enemey->GetHadouken()->GetY(), GetX(), GetY(), enemey->GetHadouken()->GetRadius(), GetRadius())) {
            if (currentState.compare("Crouch") != 0) {

                GameManager::Instance()->DamagePlayerOne(30);
                enemey->GetHadouken()->SetDestroyed(true);
            }
        }
    }
    if (currentHadouken != nullptr) {
        if (currentHadouken->Update()) {
            currentHadouken.release();
        }
    }

    this->UpdateDestRect();
}
void Player::OnJumpAnimComplete() {
    std::cout << "Jumped";
    m_Y = ground;
}

void Player::OnAttackCompleted() {
    
    isAttacking = false;
}

void Player::OnAttackStart()
{
}

void Player::Attack(std::string attackName)
{
    PlayState(attackName);
    attackStart = SDL_GetTicks();
    if (m_iFrame == 0) {
        
        if (animStates[attackName].callbackOnStart != nullptr) {
            
            animStates[attackName].callbackOnStart();
        }
    }
}

void Player::CheckForCollisions()
{
}
