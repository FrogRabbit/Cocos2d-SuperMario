#include "EffectManager.h"
#include "BlockEffect.h"
#include "EnemyEffect.h"
#include "FireEffect.h"
#include "ScoreEffect.h"

EffectManager* EffectManager::m_this = NULL;

EffectManager::EffectManager()
{
}


void EffectManager::Init(Layer * layer)
{
	m_layer = layer;
}

void EffectManager::Update(float ElapsedTime)
{
	for (auto iter = m_vecEffect.begin(); iter != m_vecEffect.end();)
	{
		MEffect* effect = *iter;
		effect->Update(ElapsedTime);
		if (effect->CheckAlive())
		{
			effect->Release(m_layer);
			iter = m_vecEffect.erase(iter);
		}
		else
		{
			iter++;
		}
	}
}

void EffectManager::MakeBlockEffect(int x, int y)
{
	BlockEffect* effect;
	effect = new BlockEffect();
	effect->Init(m_layer, x, y);
	m_vecEffect.push_back(effect);
}

void EffectManager::MakeBlockEffect(Vec2 pos)
{
	BlockEffect* effect;
	effect = new BlockEffect();
	effect->Init(m_layer, pos.x, pos.y);
	m_vecEffect.push_back(effect);
}

void EffectManager::MakeFireEffect(int x, int y)
{
	FireEffect* effect;
	effect = new FireEffect();
	effect->Init(m_layer, x, y);
	m_vecEffect.push_back(effect);
}

void EffectManager::MakeFireEffect(Vec2 pos)
{
	FireEffect* effect;
	effect = new FireEffect();
	effect->Init(m_layer, pos.x, pos.y);
	m_vecEffect.push_back(effect);
}

void EffectManager::MakeEnemyEffect(int index, int x, int y)
{
	EnemyEffect* effect;
	effect = new EnemyEffect();
	effect->Init(m_layer, index, x, y);
	m_vecEffect.push_back(effect);
}

void EffectManager::MakeEnemyEffect(int index, Vec2 pos)
{
	EnemyEffect* effect;
	effect = new EnemyEffect();
	effect->Init(m_layer, index, pos.x, pos.y);
	m_vecEffect.push_back(effect);
}

void EffectManager::MakeScoreEffect(int score, int x, int y)
{
	ScoreEffect* effect;
	effect = new ScoreEffect();
	effect->Init(m_layer, score, x, y);
	m_vecEffect.push_back(effect);
}

void EffectManager::MakeScoreEffect(int score, Vec2 pos)
{
	EffectManager::MakeScoreEffect(score, pos.x, pos.y);
}

void EffectManager::Release()
{
	for (auto iter = m_vecEffect.begin(); iter != m_vecEffect.end();)
	{
		MEffect* effect = *iter;
		effect->Release(m_layer);
		iter = m_vecEffect.erase(iter);
	}
}

EffectManager::~EffectManager()
{
}
