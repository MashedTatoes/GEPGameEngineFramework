#pragma once
#include "SpriteEx.h"
class Hadouken :
    public SpriteExAnimated
{
private:
    double m_velX = 0,
        m_velY = 0,
        m_velMax = 10;
    int moveDirection;
    bool isDestroyed;
public:
    Hadouken(SDL_Texture* tex, double x, double y,int dir);
    bool Update();
    void SetDestroyed(bool d) { isDestroyed = d; }
    bool GetDestroyed() { return isDestroyed; }
    
};

