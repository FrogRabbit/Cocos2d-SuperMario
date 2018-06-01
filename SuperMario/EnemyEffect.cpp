#include "EnemyEffect.h"



void EnemyEffect::Init(Layer * layer, int index, int x, int y)
{
	m_bAlive = false;
	m_fTime = 0;
	m_pSpr = Sprite::create();
	m_pSpr->setPosition(x, y);
	m_pSpr->setAnchorPoint(Vec2(0.5f, 0));
	m_pSpr->setScale(2.0f);
	layer->addChild(m_pSpr);
	switch (index)
	{
	case 0:
	{
		m_pSpr->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy0_0.png"));
		Vec2 pos = m_pSpr->getPosition();
		pos.x += 50;
		pos.y -= 600;
		JumpTo* jump = JumpTo::create(1.5f, pos, 230, 1);
		m_pSpr->setFlipY(true);
		m_pSpr->runAction(jump);
		break;
	}
	case 1:
	{
		m_pSpr->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy0_2.png"));
		break;
	}
	case 2:
	{
		m_pSpr->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy3_0.png"));
		Vec2 pos = m_pSpr->getPosition();
		m_pSpr->setFlipY(true);
		pos.x += 50;
		pos.y -= 600;
		JumpTo* jump = JumpTo::create(1.5f, pos, 230, 1);
		m_pSpr->runAction(jump);
		break;
	}
	}
}

void EnemyEffect::Update(float ElapsedTime)
{
	m_fTime = m_fTime + ElapsedTime;
	if (m_fTime >= 1.5f)
	{
		m_bAlive = true;
	}
}

void EnemyEffect::Release(Layer * layer)
{
	layer->removeChild(m_pSpr);
}

EnemyEffect::EnemyEffect()
{
}


EnemyEffect::~EnemyEffect()
{
}
