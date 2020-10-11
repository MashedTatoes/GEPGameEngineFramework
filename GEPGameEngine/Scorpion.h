#pragma once
#include "SpriteEx.h"
#include <vector>
class Scorpion : public SpriteExAnimated
{
private:
	double m_velX = 0,
		m_velY = 0,
		m_velMax = 10;
public:
	Scorpion(double x, double y);
	void Update();
	void Render();
};

