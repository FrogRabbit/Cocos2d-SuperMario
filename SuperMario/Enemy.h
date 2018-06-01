#pragma once
#include "define.h"
#include "BlockManager.h"
#include "EffectManager.h"
#include "UiManager.h"

class Enemy
{
protected:
	MOVE_STATE m_MoveState;
	Vec2 m_pPos;
	Sprite* m_pEnemy;
	Rect m_bodyHitbox;
	Rect m_bottomHitbox;
	Rect m_rearHitbox;
	Rect m_frontHitbox;
	Rect m_topHitbox;
	int m_iIndex;
	float m_fSpeed;
	float m_fJumpSpeed;
	float m_fGravityTime;
	bool m_bMove;
	bool m_bAlive;
	bool m_bPerfectAlive;
	bool m_bInvincible;
	float m_fInvincible;
public:
	virtual void Init(Layer* layer, int index, Vec2 pos);
	virtual void Update(float ElapsedTime);
	virtual void SetHitbox();
	virtual bool CheckDieCrash(Rect hitbox);
	virtual bool CheckCrashBody(Rect hitbox);
	void Release(Layer* layer);
	virtual void PerfecdDie();
	virtual bool CheckPerfectDie(Rect hitbox);
	bool CheckAlive();
	bool CheckPAlive();
	void SetPerfectDie(bool alive);
	Enemy();
	~Enemy();
};

