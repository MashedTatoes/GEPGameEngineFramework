#include "Hadouken.h"

Hadouken::Hadouken(SDL_Texture* tex, double x, double y,int dir) : SpriteExAnimated(tex, x, y, 0)
{
    spriteSrcRect = { 0,350,70,80 };
    spriteDestRect = { (int)(m_X - 50),(int)(m_Y - 50)  ,70,80 };
    m_velX = 3.0f;
    m_DY = 0.1f;
    m_dRadius = 20;
    AddAnimState("Moving", AnimStateDefinition{ 4,2,15 });
    AddAnimState("Destroying", AnimStateDefinition{ 5,4,70 });
    moveDirection = dir;
    isDestroyed = false;
    if (moveDirection == -1) {
        flippedDimensions.first = true;
    }
}

bool Hadouken::Update()
{
    
    
    if (isDestroyed) {
        PlayState("Destroying");
        if (isAnimFinished) {
            return true;
        }
    }
    else {
        m_X += m_velX * moveDirection;
        PlayState("Moving");
    }
    if (GetX() >= 1024 || GetX() <= 0) {
        isDestroyed = true;
    }
    spriteSrcRect.x = spriteSrcRect.w * m_iFrame; //updates the animation
    UpdateDestRect();

    return false;
}
