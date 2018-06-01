#pragma once
#include "define.h"
#include "MEffect.h"

class EnemyEffect : public MEffect
{
private:
	Sprite* m_pSpr;
	float m_fTime;
public:
	void Init(Layer* layer, int index, int x, int y);
	virtual void Update(float ElapsedTime);
	virtual void Release(Layer* layer);
	EnemyEffect();
	~EnemyEffect();
};

