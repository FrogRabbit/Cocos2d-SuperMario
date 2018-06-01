#pragma once
#include "define.h"
#include "MEffect.h"


class ScoreEffect : public MEffect
{
private:
	Label* m_score;
	float m_time;
public:
	void Init(Layer* layer, int score, int x, int y);
	virtual void Update(float ElapsedTime);
	virtual void Release(Layer* layer);
	ScoreEffect();
	~ScoreEffect();

};

