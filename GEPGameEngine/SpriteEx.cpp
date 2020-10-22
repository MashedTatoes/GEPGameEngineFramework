#include "Game.h"
void SpriteEx::Render()
{
	if (SDL_RenderCopyEx(Game::Instance()->GetRenderer(), texture,
		&spriteSrcRect, &spriteDestRect, angle, nullptr, SDL_FLIP_NONE) == 0)
	{
		// std::cout << "Success...\n";
	}
	else
	{
		std::cout << "Failed to render..\n";
	}
}
SpriteExAnimated::SpriteExAnimated(SDL_Texture* tex, double x, double y,
	double a)
{
	texture = tex;
	m_X = x;
	m_Y = y;
	angle = a;
}
void SpriteExAnimated::Animate()
{
	m_iFrame++;
	if (m_iFrame >= m_iFrameMax)
	{
		m_iFrame = 0;

	}
}
void SpriteExAnimated::AnimateRange(AnimStateDefinition asd)
{
	//change the row
	spriteSrcRect.y = spriteSrcRect.h * asd.rowIndex;
	if (SDL_TICKS_PASSED(SDL_GetTicks(),
		Game::Instance()->GetLastTick() + asd.time))
	{
		Game::Instance()->UpdateTick();
		m_iFrameMax = asd.frames;
		Animate();
	}
}
void SpriteExAnimated::PlayState(std::string stateName)
{
	if (currentState != stateName)
		m_iFrame = 0;
	AnimateRange(animStates[stateName]);
	currentState = stateName;
}
void SpriteEx::UpdateDestRect()
{
	spriteDestRect.x = (int)(m_X - spriteDestRect.w * 0.5f);
	spriteDestRect.y = (int)(m_Y - spriteDestRect.h * 0.5f);
}
void SpriteExAnimated::AddAnimState(std::string stateName, AnimStateDefinition asd)
{
	//animStates.insert(std::pair<std::string,AnimStateDefinition>(stateName,asd));
	animStates[stateName] = asd;
}