#include "EnemyTurtle.h"
#include "MapManager.h"
#include "EnemyManager.h"
#include "PlayerManager.h"


void EnemyTurtle::Init(Layer * layer, int index, Vec2 pos)
{
	m_bSlide = false;
	Enemy::Init(layer, index, pos);
	switch (m_iIndex)
	{
	case 2:
	{
		Vector<SpriteFrame*> animationFrame(2);
		for (int i = 0; i < 2; i++)
		{
			char szFileName[256];
			sprintf(szFileName, "enemy1_%d.png", i);
			SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(szFileName);
			animationFrame.pushBack(frame);
		}
		Animation* animation = Animation::createWithSpriteFrames(animationFrame, 0.3f);
		Animate* animate = Animate::create(animation);
		m_pEnemy->runAction(RepeatForever::create(animate));
		m_fCurSpeed = 80.0f;
		break;
	}
	case 3:
	{
		Vector<SpriteFrame*> animationFrame(2);
		for (int i = 0; i < 2; i++)
		{
			char szFileName[256];
			sprintf(szFileName, "enemy2_%d.png", i);
			SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(szFileName);
			animationFrame.pushBack(frame);
		}
		Animation* animation = Animation::createWithSpriteFrames(animationFrame, 0.3f);
		Animate* animate = Animate::create(animation);
		m_pEnemy->runAction(RepeatForever::create(animate));
		m_fCurSpeed = 80.0f;
		break;
	}
	}
	m_MoveState = MOVE_STATE_LEFT;
	m_fSpeed = -80.0f;
	SetHitbox();
}

void EnemyTurtle::Update(float ElapsedTime)
{
	if (m_bMove)
	{
		switch (m_iIndex)
		{
		case 1:
		{
			if (m_bSlide)
			{
				m_fCurSpeed = 200.0;
				if (BlockManager::GetInstance()->CheckOnGround(m_frontHitbox))
				{
					m_MoveState = MOVE_STATE_LEFT;
				}
				if (BlockManager::GetInstance()->CheckOnGround(m_rearHitbox))
				{
					m_MoveState = MOVE_STATE_RIGHT;
				}
				if (EnemyManager::GetInstance()->CheckPerfectDie(this, m_bodyHitbox))
				{

				}
			}
			else
			{
				m_fCurSpeed = 0;
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
			break;
		}
		case 2:
		{
			if (BlockManager::GetInstance()->CheckOnGround(m_frontHitbox) || !BlockManager::GetInstance()->CheckOnGround(m_bottomFrontHitbox))
			{
				m_MoveState = MOVE_STATE_LEFT;
			}
			if (BlockManager::GetInstance()->CheckOnGround(m_rearHitbox) || !BlockManager::GetInstance()->CheckOnGround(m_bottomRearHitbox))
			{
				m_MoveState = MOVE_STATE_RIGHT;
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
			break;
		}
		case 3:
		{
			if (BlockManager::GetInstance()->CheckOnGround(m_frontHitbox))
			{
				m_MoveState = MOVE_STATE_LEFT;
			}
			if (BlockManager::GetInstance()->CheckOnGround(m_rearHitbox))
			{
				m_MoveState = MOVE_STATE_RIGHT;
			}
			if (BlockManager::GetInstance()->CheckOnGround(m_bottomHitbox))
			{
				Vec2 pos = BlockManager::GetInstance()->GetBlockPos(m_bottomHitbox);
				m_pPos.y = pos.y + 16;
				m_fGravityTime = 0;
				m_fJumpSpeed = 300;
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
			if (BlockManager::GetInstance()->CheckOnGround(m_topHitbox))
			{
				m_fJumpSpeed = -40.0f;
			}
			break;
		}
		}
		switch (m_MoveState)
		{
		case MOVE_STATE_RIGHT:
		{
			m_pEnemy->setFlipX(true);
			m_fSpeed = m_fCurSpeed;
			break;
		}
		case MOVE_STATE_LEFT:
		{
			m_pEnemy->setFlipX(false);
			m_fSpeed = -m_fCurSpeed;
			break;
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

void EnemyTurtle::SetHitbox()
{
	m_bodyHitbox.setRect(m_pPos.x - 16, m_pPos.y, 32, 24);
	m_frontHitbox.setRect(m_pPos.x + 17, m_pPos.y + 6, 2, 20);
	m_rearHitbox.setRect(m_pPos.x - 19, m_pPos.y + 6, 2, 20);
	m_bottomHitbox.setRect(m_pPos.x - 10, m_pPos.y - 1, 20, 1);
	m_topHitbox.setRect(m_pPos.x - 5, m_pPos.y + 30, 10, 2);
	m_bottomFrontHitbox.setRect(m_pPos.x + 11, m_pPos.y - 1, 3, 1);
	m_bottomRearHitbox.setRect(m_pPos.x - 15, m_pPos.y - 1, 4, 1);
}

bool EnemyTurtle::CheckDieCrash(Rect hitbox)
{
	if (m_bodyHitbox.intersectsRect(hitbox))
	{
		switch (m_iIndex)
		{
		case 1:
			m_bSlide = !m_bSlide;
			EffectManager::GetInstance()->MakeScoreEffect(100, m_pEnemy->getPosition());
			//UiManager::GetInstance()->AddScore(100);
			switch (PlayerManager::GetInstance()->GetDirection())
			{
			case PMOVE_STATE_LEFT:
				m_MoveState = MOVE_STATE_LEFT;
				break;
			case PMOVE_STATE_RIGHT:
				m_MoveState = MOVE_STATE_RIGHT;
				break;
			}
			break;
		case 2:
			m_iIndex--;
			m_pEnemy->stopAllActions();
			EffectManager::GetInstance()->MakeScoreEffect(300, m_pEnemy->getPosition());
			m_pEnemy->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy3_0.png"));
			m_fCurSpeed = 0;
			break;
		case 3:
			m_iIndex--;
			m_pEnemy->stopAllActions();
			EffectManager::GetInstance()->MakeScoreEffect(500, m_pEnemy->getPosition());
			Vector<SpriteFrame*> animationFrame(2);
			for (int i = 0; i < 2; i++)
			{
				char szFileName[256];
				sprintf(szFileName, "enemy1_%d.png", i);
				SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(szFileName);
				animationFrame.pushBack(frame);
			}
			Animation* animation = Animation::createWithSpriteFrames(animationFrame, 0.3f);
			Animate* animate = Animate::create(animation);
			m_pEnemy->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy1_0.png"));
			m_pEnemy->runAction(RepeatForever::create(animate));
			m_fJumpSpeed = -60;
			break;
		}
		return true;
	}
}

bool EnemyTurtle::CheckPerfectDie(Rect hitbox)
{
	if (m_bodyHitbox.intersectsRect(hitbox))
	{
		EffectManager::GetInstance()->MakeEnemyEffect(2, m_pEnemy->getPosition());
		EffectManager::GetInstance()->MakeScoreEffect(m_iIndex * 200, m_pEnemy->getPosition());
		m_bPerfectAlive = true;
		return true;
	}
	return false;
}

void EnemyTurtle::PerfectDie()
{
}

bool EnemyTurtle::CheckCrashBody(Rect hitbox)
{
	if (m_bodyHitbox.intersectsRect(hitbox))
	{
		switch (m_iIndex)
		{
		case 1:
			if (m_bSlide)
			{
				return true;
			}
			else if (!m_bSlide)
			{
				m_bSlide = true;
				switch (PlayerManager::GetInstance()->GetDirection())
				{
				case PMOVE_STATE_LEFT:
					m_MoveState = MOVE_STATE_LEFT;
					break;
				case PMOVE_STATE_RIGHT:
					m_MoveState = MOVE_STATE_RIGHT;
					break;
				}
				return false;
			}
			break;
		case 2:
			return true;
		case 3:
			return true;
		}
	}
	return false;
}


EnemyTurtle::EnemyTurtle()
{
}


EnemyTurtle::~EnemyTurtle()
{
}
