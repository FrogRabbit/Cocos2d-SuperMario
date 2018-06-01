#pragma once
#include "cocos2d.h"

USING_NS_CC;

class MEffect
{
protected:
	bool m_bAlive;
public:
	virtual void Update(float ElapsedTime);
	bool CheckAlive();
	virtual void Release(Layer* layer);
	MEffect();
	~MEffect();
};

