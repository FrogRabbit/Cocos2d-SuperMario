#include "BlockEffect.h"



void BlockEffect::Init(Layer * layer, int x, int y)
{
	m_bAlive = false;
	m_fTime = 0;
	for (int i = 0; i < 4; i++)
	{
		JumpBy* jump;
		if (i % 2 == 0)
		{
			m_pSpr[i] = Sprite::create("effect_brick0.png");
			m_pSpr[i]->setPosition(Vec2(x - 8, y + 8 - (i * 8)));
			jump = JumpBy::create(2.0f - (i * 0.25f), Vec2(-250, -448), 200 - (i * 50), 1);
		}
		else
		{
			m_pSpr[i] = Sprite::create("effect_brick1.png");
			m_pSpr[i]->setPosition(Vec2(x + 8, y + 16 - (i * 8)));
			jump = JumpBy::create(2.25f - (i * 0.25f), Vec2(250, -448), 250 - (i * 50), 1);
		}
		m_pSpr[i]->setScale(2.0f);
		m_pSpr[i]->runAction(jump);
		layer->addChild(m_pSpr[i]);
	}
}

void BlockEffect::Update(float ElapsedTime)
{
	m_fTime = m_fTime + ElapsedTime;
	if (m_fTime >= 3.0f)
	{
		m_bAlive = true;
	}
}

void BlockEffect::Release(Layer * layer)
{
	layer->removeChild(m_pSpr[0]);
	layer->removeChild(m_pSpr[1]);
	layer->removeChild(m_pSpr[2]);
	layer->removeChild(m_pSpr[3]);
}

BlockEffect::BlockEffect()
{
}


BlockEffect::~BlockEffect()
{
}
