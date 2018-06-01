#pragma once
#include "define.h"
#include "MEffect.h"

class FireEffect : public MEffect
{
private:
	Sprite* m_pSpr;
public:
	void Init(Layer* layer, int x, int y);
	virtual void Update(float ElapsedTime);
	virtual void Release(Layer* layer);
	void SetAlive(bool alive);
	FireEffect();
	~FireEffect();
};

