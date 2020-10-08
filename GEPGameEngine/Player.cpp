#include "Player.h"
#include "Game.h"
#include <algorithm> //for min/max functions
Player::Player(SDL_Texture* tex, double x, double y)
    : SpriteExAnimated(tex, x - 50, y - 50, 0)
{
    spriteSrcRect = { 0,0,70,80 };
    spriteDestRect = { (int)(m_X - 50),(int)(m_Y - 50)  ,70,80 };
    m_velX = 0.7f;
    m_DY = 0.2f;
    m_dRadius = 50;
    AddAnimState("Hadouken", AnimStateDefinition(0, 4, 150,false));
    AddAnimState("Idle", AnimStateDefinition(1, 4, 150, true));
    AddAnimState("Punch", AnimStateDefinition(2, 3, 150, false));
    AddAnimState("Move", AnimStateDefinition(3, 5, 150, true));
    AddAnimState("Kick", AnimStateDefinition(6, 5, 150, false));
    AddAnimState("Roundhouse", AnimStateDefinition(7, 5, 150, false));
    AddAnimState("Jump", AnimStateDefinition(8, 7, 150, false));
    AddAnimState("Crouch", AnimStateDefinition(9, 1, 150, false));
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
    /*m_velY += m_DY;
    m_velY = min(max(m_velY, -(m_velMax * fabs(m_DY))), (m_velMax * fabs(m_DY)));
    if (m_iFrame < m_iFrameMax/2)
    {
        m_Y -= m_velY;
    }
    else if (m_iFrame >= m_iFrameMax/2)
    {
        m_Y += m_velY;
    }*/
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
