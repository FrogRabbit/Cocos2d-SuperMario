#include "Fire.h"
#include "BlockManager.h"
#include "MapManager.h"
#include "EffectManager.h"
#include "EnemyManager.h"


void Fire::Init(Layer * layer, PMOVE_STATE direction, int x, int y)
{
	switch (direction)
	{
	case PMOVE_STATE_RIGHT:
		m_fSpeed = 200;
		break;
	case PMOVE_STATE_LEFT:
		m_fSpeed = -200;
		break;
	}
	
	m_fJumpSpeed = -80;
	m_fGravityTime = 0;
	m_bAlive = false;
	m_pPos.set(x, y);
	m_pSpr = Sprite::create();
	m_pSpr->setScale(2.0f);
	m_pSpr->setPosition(m_pPos);
	layer->addChild(m_pSpr);
	Vector<SpriteFrame*> animationFrame(4);
	for (int i = 0; i < 4; i++)
	{
		char szFileName[256];
		sprintf(szFileName, "fire%d.png", i);
		SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(szFileName);
		animationFrame.pushBack(frame);
	}
	Animation* animation = Animation::createWithSpriteFrames(animationFrame, 0.1f);
	Animate* animate = Animate::create(animation);
	m_pSpr->runAction(RepeatForever::create(animate));
	SetHitbox();
}

void Fire::Update(float ElapsedTime)
{
	if (BlockManager::GetInstance()->CheckOnGround(m_bottomHitbox))
	{
		Vec2 pos = BlockManager::GetInstance()->GetBlockPos(m_bottomHitbox);
		m_fJumpSpeed = 200;
		m_fGravityTime = 0;
	}
	else if (BlockManager::GetInstance()->CheckOnGround(m_hitbox))
	{
		m_bAlive = true;
	}
	else
	{
		m_fGravityTime += ElapsedTime;
		if (m_fGravityTime > 0.1f)
		{
			m_fGravityTime = 0;
			m_fJumpSpeed -= GRAVITY;
		}
	}
	m_pPos.x = m_pPos.x + (m_fSpeed * ElapsedTime);
	m_pPos.y = m_pPos.y + (m_fJumpSpeed * ElapsedTime);
	m_pSpr->setPosition(m_pPos);
	if (EnemyManager::GetInstance()->CheckPerfectDie(m_hitbox))
	{
		m_bAlive = true;
	}
	if (32 * 19 - MapManager::GetInstance()->GetPosX() <= m_pPos.x || m_pPos.x <= -MapManager::GetInstance()->GetPosX())
	{
		m_bAlive = true;
	}
	SetHitbox();
}

void Fire::SetHitbox()
{
	m_hitbox.setRect(m_pPos.x - 8, m_pPos.y - 8, 16, 16);
	m_bottomHitbox.setRect(m_pPos.x - 2, m_pPos.y - 10, 4, 2);
}

void Fire::Release(Layer * layer)
{
	EffectManager::GetInstance()->MakeFireEffect(m_pSpr->getPosition());
	layer->removeChild(m_pSpr);
}

bool Fire::GetAlive()
{
	return m_bAlive;
}

Fire::Fire()
{
}


Fire::~Fire()
{
}
