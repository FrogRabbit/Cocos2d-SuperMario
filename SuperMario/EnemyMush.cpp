#include "EnemyMush.h"
#include "MapManager.h"
#include "EnemyManager.h"


void EnemyMush::Init(Layer * layer, int index, Vec2 pos)
{
	Enemy::Init(layer, index, pos);
	Vector<SpriteFrame*> animationFrame(2);
	for (int i = 0; i < 2; i++)
	{
		char szFileName[256];
		sprintf(szFileName, "enemy0_%d.png", i);
		SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(szFileName);
		animationFrame.pushBack(frame);
	}
	Animation* animation = Animation::createWithSpriteFrames(animationFrame, 0.3f);
	Animate* animate = Animate::create(animation);
	m_pEnemy->runAction(RepeatForever::create(animate));
	SetHitbox();
	m_MoveState = MOVE_STATE_LEFT;
	m_fSpeed = -60.0f;
}

void EnemyMush::Update(float ElapsedTime)
{
	if (m_bMove)
	{
		if (BlockManager::GetInstance()->CheckOnGround(m_frontHitbox))
		{
			m_MoveState = MOVE_STATE_LEFT;
		}
		if (BlockManager::GetInstance()->CheckOnGround(m_rearHitbox))
		{
			m_MoveState = MOVE_STATE_RIGHT;
		}
		
		switch (m_MoveState)
		{
		case MOVE_STATE_RIGHT:
		{
			m_fSpeed = 80.0f;
			break;
		}
		case MOVE_STATE_LEFT:
		{
			m_fSpeed = -80.0f;
			break;
		}
		}
		if (BlockManager::GetInstance()->CheckOnGround(m_bottomHitbox))
		{
			Vec2 pos = BlockManager::GetInstance()->GetBlockPos(m_bottomHitbox);
			m_pPos.y = pos.y + 16;
			m_fJumpSpeed = 0;
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
		if (32 * 21 - MapManager::GetInstance()->GetPosX() <= m_pPos.x || m_pPos.x <= -MapManager::GetInstance()->GetPosX() - 50)
		{
			m_bAlive = true;
		}
		m_pPos.x = m_pPos.x + (m_fSpeed * ElapsedTime);
		m_pPos.y = m_pPos.y + (m_fJumpSpeed * ElapsedTime);
		m_pEnemy->setPosition(m_pPos);
		SetHitbox();
	}
	else
	{
		if (32 * 20 - MapManager::GetInstance()->GetPosX() >= m_pPos.x)
		{
			m_bMove = true;
		}
	}
}

void EnemyMush::SetHitbox()
{
	m_bodyHitbox.setRect(m_pPos.x - 16, m_pPos.y, 32, 24);
	m_frontHitbox.setRect(m_pPos.x + 17, m_pPos.y + 6, 2, 20);
	m_rearHitbox.setRect(m_pPos.x - 19, m_pPos.y + 6, 2, 20);
	m_bottomHitbox.setRect(m_pPos.x - 10, m_pPos.y - 1, 20, 1);
	m_topHitbox.setRect(m_pPos.x - 10, m_pPos.y + 30, 20, 2);
}

bool EnemyMush::CheckDieCrash(Rect hitbox)
{
	if (m_bodyHitbox.intersectsRect(hitbox))
	{
		EffectManager::GetInstance()->MakeEnemyEffect(1, m_pEnemy->getPosition());
		EffectManager::GetInstance()->MakeScoreEffect(100, m_pEnemy->getPosition());
		//EffectManager::GetInstance()->MakeBlockEffect(m_pEnemy->getPosition());
		m_bAlive = true;
		return true;
	}
	return false;
}

bool EnemyMush::CheckPerfectDie(Rect hitbox)
{
	if (m_bodyHitbox.intersectsRect(hitbox))
	{
		EffectManager::GetInstance()->MakeEnemyEffect(0, m_pEnemy->getPosition());
		EffectManager::GetInstance()->MakeScoreEffect(100, m_pEnemy->getPosition());
		//EffectManager::GetInstance()->MakeFireEffect(m_pEnemy->getPosition());
		m_bPerfectAlive = true;
		return true;
	}
	return false;
}

void EnemyMush::PerfecdDie()
{
}

bool EnemyMush::CheckCrashBody(Rect hitbox)
{
	return m_bodyHitbox.intersectsRect(hitbox);
}

EnemyMush::EnemyMush()
{
}


EnemyMush::~EnemyMush()
{
}
