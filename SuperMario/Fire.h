#pragma once
#include "define.h"

class Fire
{
private:
	float m_fSpeed;
	float m_fJumpSpeed;
	float m_fGravityTime;
	bool m_bAlive;
	Sprite* m_pSpr;
	Vec2 m_pPos;
	Rect m_hitbox;
	Rect m_bottomHitbox;
public:
	void Init(Layer* layer, PMOVE_STATE direction, int x, int y);
	void Update(float ElapsedTime);
	void SetHitbox();
	void Release(Layer* layer);
	bool GetAlive();
	Fire();
	~Fire();
};

