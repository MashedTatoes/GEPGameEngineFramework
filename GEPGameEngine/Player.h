#pragma once
#include "SpriteEx.h"
#include <vector>
using namespace std;
class Player : public SpriteExAnimated
{
private:
	double m_velX = 0,
		m_velY = 0,
		m_velMax = 10;
	void MovePlayer(bool isFwd);
	void UpdatePlayer();
	int health;
	int ground;
	bool isAttacking;
	int attackStart;

protected:
	std::vector<std::string> attackPool;
	int lastCrouch;
	int crouchTimeout;
public:
	Player(SDL_Texture* tex, double x, double y);
	~Player();
	virtual void Update();
	void Render();
	//void SetIdle();
	void Jump();
	void OnJumpAnimComplete();
	void OnAttackCompleted();
	void OnAttackStart();
	bool IsAttacking() { return isAttacking; }
	int GetAttackStart(){ return attackStart; }
	void Attack(std::string attackName);


};