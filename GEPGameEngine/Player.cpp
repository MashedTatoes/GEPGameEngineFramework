#include "Player.h"
#include "Game.h"
#include <algorithm> //for min/max functions

Player::Player(SDL_Texture *tex, double x, double y)
	: SpriteExAnimated(tex, x - 50, y - 50, 0, 1, 4, 0.1f)
{

	spriteSrcRect = { 0,0,100,100 };
	spriteDestRect = { (int)(m_X - 50),(int) (m_Y-50)  ,100,100 };

	m_dRadius = 50;
}

Player::~Player()
{
 

}


void Player::Render()
{
 
this->SpriteExAnimated::Render(); //invoke the base class's Render()

}


void Player::SetIdle()
{
	spriteSrcRect.y = 0;
	m_iFrame = 0;
	m_iSprite = 0;
}

void Player::Update()
{
 
	this->UpdatePlayer();
 }


void Player::MoveForward()
{
 
}

void Player::UpdatePlayer()
{
	 
}

  