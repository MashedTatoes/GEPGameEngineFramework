#include "Scorpion.h"
#include "Game.h"
Scorpion::Scorpion(double x, double y) : SpriteExAnimated(Game::Instance()->LoadTexture("resources/images/Scorpion.png") , x - 50, y - 50, 0)
{
	spriteSrcRect = { 0,0,60,120 };
	spriteDestRect = { (int)(m_X - 50),(int)(m_Y - 50)  ,60,100 };
	m_velX = 0.7f;
	m_DY = 0.1f;
	m_dRadius = 50;
	this->AddAnimState("Idle", AnimStateDefinition(0, 8, 60));


}


void Scorpion::Render() {
	this->SpriteExAnimated::Render();
}

void Scorpion::Update() {
	PlayState("Idle");
	spriteSrcRect.x = spriteSrcRect.w * m_iFrame; //updates the animation
	//std::cout << m_iFrame << "\n";
	this->UpdateDestRect();
}