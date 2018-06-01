#include "ScoreEffect.h"
#include "UiManager.h"



void ScoreEffect::Init(Layer * layer, int score, int x, int y)
{
	m_time = 0;
	UiManager::GetInstance()->AddScore(score);
	m_bAlive = false;
	char temp[128];
	m_score = Label::create();
	sprintf(temp, "%d", score);
	m_score->setString(temp);
	m_score->setPosition(x+16, y+16);
	m_score->setSystemFontSize(15);
	FadeTo* fade = FadeTo::create(1.0f, 0);
	MoveBy* move = MoveBy::create(1.0f, Vec2(0, 32));
	Spawn* spawn = Spawn::create(fade, move, NULL);
	m_score->runAction(spawn);
	layer->addChild(m_score, 3);
}

void ScoreEffect::Update(float ElapsedTime)
{
	m_time += ElapsedTime;
	if (m_time >= 2.0f)
	{
		m_time = true;
		m_bAlive = true;
	}
}

void ScoreEffect::Release(Layer * layer)
{
	layer->removeChild(m_score);
}

ScoreEffect::ScoreEffect()
{
}


ScoreEffect::~ScoreEffect()
{
}
