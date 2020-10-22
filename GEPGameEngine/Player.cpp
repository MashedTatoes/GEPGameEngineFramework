#include "Player.h"
#include "Game.h"
#include <algorithm> //for min/max functions
Player::Player(SDL_Texture* tex, double x, double y)
    : SpriteExAnimated(tex, x - 50, y - 50, 0)
{
    spriteSrcRect = { 0,0,70,80 };
    spriteDestRect = { (int)(m_X - 50),(int)(m_Y - 50)  ,70,80 };
    m_velX = 0.7f;
    m_DY = 0.1f;
    m_dRadius = 50;
    ground = m_Y;
    AddAnimState("Hadouken", AnimStateDefinition(0, 4, 90));
    AddAnimState("Idle", AnimStateDefinition(1, 4, 90, true, false));
    AddAnimState("Punch", AnimStateDefinition(2, 3, 90));
    AddAnimState("Move", AnimStateDefinition(3, 5, 90, true));
    AddAnimState("Kick", AnimStateDefinition(6, 5, 90));
    AddAnimState("Roundhouse", AnimStateDefinition(7, 5, 90));
    AddAnimState("Jump", AnimStateDefinition(8, 7, 90));
    AddAnimState("Crouch", AnimStateDefinition(9, 1, 180));
    animStates["Jump"].AddCallbackOnComplete(std::bind(&Player::OnJumpAnimComplete, this));
}
Player::~Player()
{

}
void Player::Render()
{

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
        PlayState("Punch");
        //play punch animation here
    }
    else if (Game::Instance()->KeyDown(SDL_SCANCODE_K))
        PlayState("Kick");
    else  //idle animation
    {
        PlayState("Idle");
    }
    if (currentState == "Jump")
        Jump();
    spriteSrcRect.x = spriteSrcRect.w * m_iFrame; //updates the animation
    this->UpdateDestRect();
}
void Player::OnJumpAnimComplete() {
    std::cout << "Jumped";
    m_Y = ground;
}