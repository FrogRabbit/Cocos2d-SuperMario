#pragma once
#include "Enemy.h"

class EnemyTurtle : public Enemy
{
private:
	Rect m_bottomFrontHitbox;
	Rect m_bottomRearHitbox;
	bool m_bSlide;
	float m_fCurSpeed;
public:
	virtual void Init(Layer* layer, int index, Vec2 pos);
	virtual void Update(float ElapsedTime);
	virtual void SetHitbox();
	virtual bool CheckDieCrash(Rect hitbox);
	virtual bool CheckPerfectDie(Rect hitbox);
	virtual void PerfectDie();
	virtual bool CheckCrashBody(Rect hitbox);
	EnemyTurtle();
	~EnemyTurtle();
};

