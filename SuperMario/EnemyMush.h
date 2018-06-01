#pragma once
#include "Enemy.h"

class EnemyMush : public Enemy
{
private:
public:
	virtual void Init(Layer* layer, int index, Vec2 pos);
	virtual void Update(float ElapsedTime);
	virtual void SetHitbox();
	virtual bool CheckDieCrash(Rect hitbox);
	virtual bool CheckPerfectDie(Rect hitbox);
	virtual void PerfecdDie();
	virtual bool CheckCrashBody(Rect hitbox);
	EnemyMush();
	~EnemyMush();
};

