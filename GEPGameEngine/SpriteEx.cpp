	#include "Game.h"
void SpriteEx::Render()
{
	SDL_RendererFlip flip = FLIPPED_HORIZONTAL(flippedDimensions.first) | FLIPPED_VERTICAL(flippedDimensions.second);
	if (SDL_RenderCopyEx(Game::Instance()->GetRenderer(), texture,
		&spriteSrcRect, &spriteDestRect, angle, nullptr, flip) >= 0)
	{
		// std::cout << "Success...\n";
	}
	else
	{
		std::cout << "Failed to render..\n";
		std::cout << SDL_GetError();
	}
}



SpriteExAnimated::SpriteExAnimated(SDL_Texture* tex, double x, double y,
	double a)
{
	lastUpdate = SDL_GetTicks();
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
		lastUpdate + asd.time))
	{
		lastUpdate = SDL_GetTicks();
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