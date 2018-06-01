#pragma once
#include "define.h"
#include "MEffect.h"

class BlockEffect : public MEffect
{
private:
	Sprite* m_pSpr[4];
	float m_fTime;
public:
	void Init(Layer* layer, int x, int y);
	virtual void Update(float ElapsedTime);
	virtual void Release(Layer* layer);
	BlockEffect();
	~BlockEffect();
};

