#pragma once
#include "MEffect.h"

class EffectManager
{
private:
	static EffectManager* m_this;
	std::vector <MEffect*> m_vecEffect;
	Layer* m_layer;
	EffectManager();
public:
	static EffectManager* GetInstance()
	{
		if (m_this == NULL)
		{
			m_this = new EffectManager();
		}
		return m_this;
	}
	void Init(Layer* layer);
	void Update(float ElapsedTime);
	void MakeBlockEffect(int x, int y);
	void MakeBlockEffect(Vec2 pos);
	void MakeFireEffect(int x, int y);
	void MakeFireEffect(Vec2 pos);
	void MakeEnemyEffect(int index, int x, int y);
	void MakeEnemyEffect(int index, Vec2 pos);
	void MakeScoreEffect(int score, int x, int y);
	void MakeScoreEffect(int score, Vec2 pos);
	void Release();
	~EffectManager();
};

