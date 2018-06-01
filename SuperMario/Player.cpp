#include "Player.h"
#include "BlockManager.h"
#include "ItemManager.h"
#include "MapManager.h"
#include "define.h"
#include "EnemyManager.h"
#include "FireManager.h"
#include "GameInfo.h"
#include "EffectManager.h"
#include "ClearScene.h"
#include "GameOverScene.h"
#include "TimeOverScene.h"



void Player::Init(Layer * layer, int x, int y)
{

	m_bRun = false;
	m_bFire = false;
	m_bStar = false;
	m_pPos.x = x;
	m_pPos.y = y - 15;
	m_pSpr = Sprite::create("s_mario_stand.png");
	m_pSpr->setAnchorPoint(Vec2(0.5f, 0));
	m_pSpr->setPosition(m_pPos);
	m_pSpr->setScale(2.0f);
	//m_pSpr->setVisible(true);
	//m_pSpr->runAction();
	layer->addChild(m_pSpr, 8);
	SetHitbox();
	m_bFinish = false;
	m_bChange = false;
	m_bDuck = false;
	m_bDash = false;
	m_bOnGround = true;
	m_bJump = false;
	m_bDie = false;
	m_iStarCount = 0;
	m_fStarCountTime = 0;
	m_fStarTime = 0;
	m_fGravityTime = 0;
	m_fJumpSpeed = 0;
	m_fCheckJumpTime = 0;
	m_fDieTime = 0;
	m_pmoveState = PMOVE_STATE_STOP;
	m_curMoveState = PMOVE_STATE_RIGHT;
	m_fLeftAccel = 0;
	m_fRightAccel = 0;
	m_fLeftSpeed = 0;
	m_fRightSpeed = 0;
	m_bDestroy = false;
	m_bAction = false;
	m_bCheckJump = false;
	m_bDown = false;
	m_iRunCount = 0;
	m_fRunTime = 0;
	m_fRunCountTime = 0;
	m_pState = PLAYER_STATE_SMALL;
	//m_pState = PLAYER_STATE_FIRE;
	m_pOldState = m_pState;
	m_fLeftMaxSpeed = L_NORMAL_SPEED;
	m_fRightMaxSpeed = R_NORMAL_SPEED;
	m_pCurAction = NULL;
	{ //run action
		Vector<SpriteFrame*> animationFrame(4);
		Vector<SpriteFrame*> animationFrame1(4);
		Vector<SpriteFrame*> animationFrame2(4);
		for (int i = 0; i < 3; i++)
		{
			char szFileName[256];
			sprintf(szFileName, "s_mario_run%d.png", i);
			SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(szFileName);
			animationFrame.pushBack(frame);
			sprintf(szFileName, "b_mario_run%d.png", i);
			SpriteFrame* frame1 = SpriteFrameCache::getInstance()->getSpriteFrameByName(szFileName);
			animationFrame1.pushBack(frame1);
			sprintf(szFileName, "f_mario_run%d.png", i);
			SpriteFrame* frame2 = SpriteFrameCache::getInstance()->getSpriteFrameByName(szFileName);
			animationFrame2.pushBack(frame2);
		}
		Animation* animation = Animation::createWithSpriteFrames(animationFrame, 0.16f);
		Animate* animate = Animate::create(animation);
		m_pSRunAction = RepeatForever::create(animate);
		m_pSRunAction->retain();

		Animation* animation1 = Animation::createWithSpriteFrames(animationFrame1, 0.16f);
		Animate* animate1 = Animate::create(animation1);
		m_pBRunAction = RepeatForever::create(animate1);
		m_pBRunAction->retain();

		Animation* animation2 = Animation::createWithSpriteFrames(animationFrame2, 0.16f);
		Animate* animate2 = Animate::create(animation2);
		m_pFRunAction = RepeatForever::create(animate2);
		m_pFRunAction->retain();
	}
	{ //change action
		Vector<SpriteFrame*> animationFrame(7);
		Vector<SpriteFrame*> animationFrame1(7);
		Vector<SpriteFrame*> animationFrame2(7);
		{
			SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("s_mario_stand.png");
			animationFrame.pushBack(frame);
			SpriteFrame* frame1 = SpriteFrameCache::getInstance()->getSpriteFrameByName("b_mario_change.png");
			animationFrame.pushBack(frame1);
			SpriteFrame* frame2 = SpriteFrameCache::getInstance()->getSpriteFrameByName("s_mario_stand.png");
			animationFrame.pushBack(frame2);
			SpriteFrame* frame3 = SpriteFrameCache::getInstance()->getSpriteFrameByName("b_mario_change.png");
			animationFrame.pushBack(frame3);
			SpriteFrame* frame4 = SpriteFrameCache::getInstance()->getSpriteFrameByName("b_mario_stand.png");
			animationFrame.pushBack(frame4);
			SpriteFrame* frame5 = SpriteFrameCache::getInstance()->getSpriteFrameByName("b_mario_change.png");
			animationFrame.pushBack(frame5);
			SpriteFrame* frame6 = SpriteFrameCache::getInstance()->getSpriteFrameByName("b_mario_stand.png");
			animationFrame.pushBack(frame6);
		}
		{
			SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("b_mario_stand.png");
			animationFrame1.pushBack(frame);
			SpriteFrame* frame1 = SpriteFrameCache::getInstance()->getSpriteFrameByName("f_mario_stand.png");
			animationFrame1.pushBack(frame1);
			SpriteFrame* frame2 = SpriteFrameCache::getInstance()->getSpriteFrameByName("b_mario_stand.png");
			animationFrame1.pushBack(frame2);
			SpriteFrame* frame3 = SpriteFrameCache::getInstance()->getSpriteFrameByName("f_mario_stand.png");
			animationFrame1.pushBack(frame3);
			SpriteFrame* frame4 = SpriteFrameCache::getInstance()->getSpriteFrameByName("b_mario_stand.png");
			animationFrame1.pushBack(frame4);
			SpriteFrame* frame5 = SpriteFrameCache::getInstance()->getSpriteFrameByName("f_mario_stand.png");
			animationFrame1.pushBack(frame5);
			SpriteFrame* frame6 = SpriteFrameCache::getInstance()->getSpriteFrameByName("b_mario_stand.png");
			animationFrame1.pushBack(frame6);
		}
		{
			SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("s_mario_stand.png");
			animationFrame2.pushBack(frame);
			SpriteFrame* frame1 = SpriteFrameCache::getInstance()->getSpriteFrameByName("b_mario_change.png");
			animationFrame2.pushBack(frame1);
			SpriteFrame* frame2 = SpriteFrameCache::getInstance()->getSpriteFrameByName("s_mario_stand.png");
			animationFrame2.pushBack(frame2);
			SpriteFrame* frame3 = SpriteFrameCache::getInstance()->getSpriteFrameByName("b_mario_change.png");
			animationFrame2.pushBack(frame3);
			SpriteFrame* frame4 = SpriteFrameCache::getInstance()->getSpriteFrameByName("f_mario_stand.png");
			animationFrame2.pushBack(frame4);
			SpriteFrame* frame5 = SpriteFrameCache::getInstance()->getSpriteFrameByName("b_mario_stand.png");
			animationFrame2.pushBack(frame5);
			SpriteFrame* frame6 = SpriteFrameCache::getInstance()->getSpriteFrameByName("f_mario_stand.png");
			animationFrame2.pushBack(frame6);
		}
		Animation* animation = Animation::createWithSpriteFrames(animationFrame, 0.16f);
		m_pStoBAction = Animate::create(animation);
		m_pStoBAction->retain();

		Animation* animation1 = Animation::createWithSpriteFrames(animationFrame1, 0.16f);
		m_pBtoFAction = Animate::create(animation1);
		m_pBtoFAction->retain();

		Animation* animation2 = Animation::createWithSpriteFrames(animationFrame2, 0.16f);
		m_pStoFAction = Animate::create(animation2);
		m_pStoFAction->retain();
	}
}

void Player::Update(float ElapsedTime)
{
	if (m_bFinish )
	{
		//ChangeHangSprite();
	}
	else if (m_bDie)
	{
		m_fDieTime += ElapsedTime;
		if (m_fDieTime >= 2.0f)
		{
			m_fDieTime = 0;
			GameInfo::GetInstance()->SetState(GAME_STATE_SEMITITLE);
		}
		m_pSpr->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("s_mario_die.png"));
	}
	else if(!m_bChange)
	{
		if (-MapManager::GetInstance()->GetPosX() + 16 > m_pPos.x)
		{
			m_fLeftSpeed = 0;
		}
		
		if (m_pmoveState != PMOVE_STATE_LEFT || (!m_bDash && m_fRightSpeed < L_NORMAL_SPEED))
		{
			if (m_fLeftSpeed < 0)
			{
				m_fLeftAccel += ElapsedTime;
				if (m_fLeftAccel >= 0.1f)
				{
					m_fLeftAccel = 0;
					m_fLeftSpeed += 50;
					if (m_fLeftSpeed >= 0) m_fLeftSpeed = 0;
				}
			}
		}
		if (m_pmoveState != PMOVE_STATE_RIGHT || (!m_bDash && m_fRightSpeed > R_NORMAL_SPEED))
		{
			if (m_fRightSpeed > 0)
			{
				m_fRightAccel += ElapsedTime;
				if (m_fRightAccel >= 0.1f)
				{
					m_fRightAccel = 0;
					m_fRightSpeed -= 50;
					if (m_fRightSpeed <= 0) m_fRightSpeed = 0;
				}
			}
		}
		if (m_pmoveState != PMOVE_STATE_STOP)
		{
			/*if (!m_bAction && !m_bJump)
			{
				m_pSpr->runAction(m_pSRunAction);
				m_bAction = true;
			}*/
		}
		BlockManager::GetInstance()->CheckFinish(m_frontHitbox);
		if (BlockManager::GetInstance()->CheckOnGround(m_frontHitbox))
		{
			ChangeStandSprite();
			m_fRightSpeed = 0;
			m_fRightAccel = 0;
		}
		if (BlockManager::GetInstance()->CheckOnGround(m_rearHitbox))
		{
			ChangeStandSprite();
			m_fLeftSpeed = 0;
			m_fLeftAccel = 0;
		}
		if (BlockManager::GetInstance()->CheckTopCrash(m_topHitbox) && !m_bDown)
		{
			m_fJumpSpeed = -40.0f;
		}
		int itemIndex = ItemManager::GetInstance()->CheckCrash(m_hitbox);
		if (itemIndex != 0)
		{
			switch (itemIndex)
			{
			case 1:
			{
				if (m_pState == PLAYER_STATE_SMALL)
				{
					EffectManager::GetInstance()->MakeScoreEffect(500, m_pSpr->getPosition());
					Upgrade();
				}
				break;
			}
			case 4:
			{
				if (m_pState != PLAYER_STATE_FIRE)
				{
					Upgrade();
				}
				EffectManager::GetInstance()->MakeScoreEffect(1000, m_pSpr->getPosition());

				break;
			}
			case 5:
			{
				EffectManager::GetInstance()->MakeScoreEffect(2000, m_pSpr->getPosition());
				m_bStar = true;
				break;
			}
			case 2:
			{
				UiManager::GetInstance()->IncLife();
				break;
			}
			case 3:
			{
				Downgrade();
				break;
			}
				
			}
			itemIndex = 0;
		}
		if (m_bDuck)
		{
			ChangeDuckSprite();
		}
		/*
		if (m_bJump)
		{
		m_fGravityTime += ElapsedTime;
		if (m_fGravityTime >= 0.1f)
		{
		m_fGravityTime = 0;
		m_fJumpSpeed -= GRAVITY;
		}
		m_pPos.y = m_pPos.y + (m_fJumpSpeed * ElapsedTime);
		}
		if (BlockManager::GetInstance()->CheckOnGround(m_bottomHitbox))
		{
		m_bOnGround = true;
		m_fGravityTime = 0;
		if ((int)(m_pPos.y) % 32 != 0)
		{
		Point pos = BlockManager::GetInstance()->GetBlockPos(m_bottomHitbox);
		m_pPos.y = pos.y + 16;
		}
		}
		*/
		//jump or air
		if (m_bJump)
		{
			m_fGravityTime += ElapsedTime;
			if (m_fGravityTime >= 0.1f)
			{
				m_fGravityTime = 0;
				m_fJumpSpeed -= GRAVITY;
			}
			m_pPos.y = m_pPos.y + (m_fJumpSpeed * ElapsedTime);
		}
		if (m_fJumpSpeed < 0)
		{
			m_bDown = true;
		}
		else
		{
			m_bDown = false;
		}
		if (m_bStar)
		{
			m_fStarTime += ElapsedTime;
			m_fStarCountTime += ElapsedTime;
			if (m_fStarCountTime >= 0.1f)
			{
				m_fStarCountTime = 0;
				m_iStarCount++;
			}
			if (m_fStarTime >= 10.0f)
			{
				m_fStarTime = 0;
				m_bStar = false;
			}
			EnemyManager::GetInstance()->CheckPerfectDie(m_hitbox);
		}
		else
		{
			if (m_bDown)
			{
				if (EnemyManager::GetInstance()->CheckDieCrash(m_bottomHitbox))
				{
					{
						Jump(0.1f);
					}
				}
			}
			if (EnemyManager::GetInstance()->CheckCrashBody(m_hitbox) && !m_bChange)
			{
				Downgrade();
			}
		}
		if (!m_bCheckJump)
		{
			m_fCheckJumpTime = 0;
		}
		
		SetHitbox();
		m_pPos.x = m_pPos.x + (m_fLeftSpeed * ElapsedTime) + (m_fRightSpeed * ElapsedTime);
		if (BlockManager::GetInstance()->CheckOnGround(m_bottomHitbox))
		{
			m_bJump = false;
			m_bOnGround = true;
			m_fJumpSpeed = 0;
			m_fGravityTime = 0;
			if (!m_bJump && !m_bAction && !m_bChange && !m_bDuck)
			{
				ChangeStandSprite();
			}
			if ((int)m_pPos.y % 32 != 0 && m_bDown)
			{

				Point pos = BlockManager::GetInstance()->GetBlockPos(m_bottomHitbox);
				m_pPos.y = pos.y + 17;
			}
		}
		else
		{
			m_bJump = true;
			m_bOnGround = false;
			if (!m_bChange)
			{
				ChangeJumpSprite();
			}

		}
		if (m_pPos.y <= -30)
		{
			Die(false);
		}
		MapManager::GetInstance()->MoveLeft(ElapsedTime, m_fRightSpeed);
		m_pSpr->setPosition(m_pPos);
	}
}

void Player::MoveLeft(float ElapsedTime)
{
	if (!m_bDuck && !m_bFinish && !m_bDie)
	{
		m_fRunCountTime += ElapsedTime;
		if (m_fRunCountTime >= 20 / (-m_fLeftSpeed + 1.0f))
		{
			m_fRunCountTime = 0;
			m_iRunCount++;
		}
		if (-MapManager::GetInstance()->GetPosX() + 16 < m_pPos.x)
		{
			if (!m_bJump && !m_bChange)
			{
				m_bAction = true;
				ChangeRunSprite();
				/*switch (m_pState)
				{
				case PLAYER_STATE_SMALL:
				{
					RunAction(m_pSRunAction);
					break;
				}
				case PLAYER_STATE_BIG:
				{
					RunAction(m_pBRunAction);
					break;
				}
				case PLAYER_STATE_FIRE:
				{
					RunAction(m_pFRunAction);
					break;
				}
				}*/
			}
			if (m_fRightSpeed >= 150)
			{
				ChangeDashSprite();
			}
			m_curMoveState = PMOVE_STATE_LEFT;
			m_pmoveState = PMOVE_STATE_LEFT;
			m_pSpr->setFlipX(true);
			if (m_fLeftSpeed >= m_fLeftMaxSpeed)
			{
				m_fLeftAccel += ElapsedTime;
				if (m_fLeftAccel >= 0.1f)
				{
					m_fLeftAccel = 0;
					m_fLeftSpeed -= 25;
				}
			}
		}
		else
		{
			ChangeStandSprite();
			m_pmoveState = PMOVE_STATE_STOP;
			m_fLeftAccel = 0;
			m_fLeftSpeed = 0;
		}
	}
}

void Player::MoveRight(float ElapsedTime)
{
	if (!m_bDuck && !m_bFinish && !m_bDie)
	{
		m_fRunCountTime += ElapsedTime;
		if (m_fRunCountTime >= 20 / (m_fRightSpeed + 1.0f))
		{
			m_fRunCountTime = 0;
			m_iRunCount++;
			if (m_iRunCount >= 3)
			{
				m_iRunCount = 0;
			}
		}
		if (!m_bJump && !m_bChange)
		{
			m_bAction = true;
			ChangeRunSprite();
			/*switch (m_pState)
			{
			case PLAYER_STATE_SMALL:
			{
				RunAction(m_pSRunAction);
				break;
			}
			case PLAYER_STATE_BIG:
			{
				RunAction(m_pBRunAction);
				break;
			}
			case PLAYER_STATE_FIRE:
			{
				RunAction(m_pFRunAction);
				break;
			}
			}*/

		}
		if (m_fLeftSpeed <= -150)
		{
			ChangeDashSprite();
		}
		m_pmoveState = PMOVE_STATE_RIGHT;
		m_curMoveState = PMOVE_STATE_RIGHT;
		m_pSpr->setFlipX(false);
		if (m_fRightSpeed <= m_fRightMaxSpeed)
		{
			m_fRightAccel += ElapsedTime;
			if (m_fRightAccel >= 0.1f)
			{
				m_fRightAccel = 0;
				m_fRightSpeed += 25;
			}
		}
	}
}


void Player::Stop()
{
	m_iRunCount = 0;
	m_fRunCountTime = 0;
	m_fRunTime = 0;
	m_pmoveState = PMOVE_STATE_STOP;
	if (!m_bJump && !m_bChange)
	{
		m_bAction = false;
		m_pSpr->stopAction(m_pSRunAction);	
		ChangeStandSprite();
	}
}

void Player::Dash()
{
	m_bDash = true;
	m_fLeftMaxSpeed = L_DASH_SPEED;
	m_fRightMaxSpeed = R_DASH_SPEED;
}

void Player::Duck()
{
	m_pmoveState = PMOVE_STATE_STOP;
	m_bDuck = true;
}

void Player::Stand()
{
	m_bDuck = false;
}

void Player::StopDash()
{
	m_bDash = false;
	m_fLeftMaxSpeed = L_NORMAL_SPEED;
	m_fRightMaxSpeed = R_NORMAL_SPEED;
}

void Player::ChangeDuckSprite()
{
	if (m_bStar)
	{
		int i = m_iStarCount % 4;
		switch (m_pState)
		{
		case PLAYER_STATE_SMALL:
		{
			switch (i)
			{
			case 0:
				m_pSpr->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("s_mario_stand.png"));
				break;
			case 1:
				m_pSpr->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("s_mario_stand_star0.png"));
				break;
			case 2:
				m_pSpr->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("s_mario_stand_star1.png"));
				break;
			case 3:
				m_pSpr->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("s_mario_stand_star2.png"));
				break;
			}
			break;
		}
		case PLAYER_STATE_BIG:
		{
			switch (i)
			{
			case 0:
				m_pSpr->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("b_mario_duck.png"));
				break;
			case 1:
				m_pSpr->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("b_mario_duck_star0.png"));
				break;
			case 2:
				m_pSpr->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("b_mario_duck_star1.png"));
				break;
			case 3:
				m_pSpr->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("b_mario_duck_star2.png"));
				break;
			}
			break;
		}
		case PLAYER_STATE_FIRE:
		{
			switch (i)
			{
			case 0:
				m_pSpr->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("f_mario_duck.png"));
				break;
			case 1:
				m_pSpr->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("b_mario_duck_star0.png"));
				break;
			case 2:
				m_pSpr->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("b_mario_duck_star1.png"));
				break;
			case 3:
				m_pSpr->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("b_mario_duck_star2.png"));
				break;
			}
			break;
		}
		}
	}
	else
	{
		switch (m_pState)
		{
		case PLAYER_STATE_SMALL:
		{
			m_pSpr->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("s_mario_stand.png"));
			break;
		}
		case PLAYER_STATE_BIG:
		{
			m_pSpr->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("b_mario_duck.png"));
			break;
		}
		case PLAYER_STATE_FIRE:
		{
			m_pSpr->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("f_mario_duck.png"));
			break;
		}
		}
	}
}

void Player::ChangeStandSprite()
{
	if (m_bStar)
	{
		int i = m_iStarCount % 4;
		switch (m_pState)
		{
		case PLAYER_STATE_SMALL:
		{
			switch (i)
			{
			case 0:
				m_pSpr->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("s_mario_stand.png"));
				break;
			case 1:
				m_pSpr->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("s_mario_stand_star0.png"));
				break;
			case 2:
				m_pSpr->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("s_mario_stand_star1.png"));
				break;
			case 3:
				m_pSpr->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("s_mario_stand_star2.png"));
				break;
			}
			break;
		}
		case PLAYER_STATE_BIG:
		{
			switch (i)
			{
			case 0:
				m_pSpr->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("b_mario_stand.png"));
				break;
			case 1:
				m_pSpr->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("b_mario_stand_star0.png"));
				break;
			case 2:
				m_pSpr->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("b_mario_stand_star1.png"));
				break;
			case 3:
				m_pSpr->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("b_mario_stand_star2.png"));
				break;
			}
			break;
		}
		case PLAYER_STATE_FIRE:
		{
			switch (i)
			{
			case 0:
				m_pSpr->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("f_mario_stand.png"));
				break;
			case 1:
				m_pSpr->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("b_mario_stand_star0.png"));
				break;
			case 2:
				m_pSpr->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("b_mario_stand_star1.png"));
				break;
			case 3:
				m_pSpr->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("b_mario_stand_star2.png"));
				break;
			}
			break;
		}
		}
	}
	else
	{
		switch (m_pState)
		{
		case PLAYER_STATE_SMALL:
		{
			m_pSpr->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("s_mario_stand.png"));
			break;
		}
		case PLAYER_STATE_BIG:
		{
			m_pSpr->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("b_mario_stand.png"));
			break;
		}
		case PLAYER_STATE_FIRE:
		{
			m_pSpr->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("f_mario_stand.png"));
			break;
		}
		}
	}
}

void Player::ChangeJumpSprite()
{
	if (m_bStar)
	{
		int i = m_iStarCount % 4;
		switch (m_pState)
		{
		case PLAYER_STATE_SMALL:
		{
			switch (i)
			{
			case 0:
				m_pSpr->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("s_mario_jump.png"));
				break;
			case 1:
				m_pSpr->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("s_mario_jump_star0.png"));
				break;
			case 2:
				m_pSpr->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("s_mario_jump_star1.png"));
				break;
			case 3:
				m_pSpr->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("s_mario_jump_star2.png"));
				break;
			}
			break;
		}
		case PLAYER_STATE_BIG:
		{
			switch (i)
			{
			case 0:
				m_pSpr->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("b_mario_jump.png"));
				break;
			case 1:
				m_pSpr->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("b_mario_jump_star0.png"));
				break;
			case 2:
				m_pSpr->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("b_mario_jump_star1.png"));
				break;
			case 3:
				m_pSpr->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("b_mario_jump_star2.png"));
				break;
			}
			break;
		}
		case PLAYER_STATE_FIRE:
		{
			switch (i)
			{
			case 0:
				m_pSpr->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("f_mario_jump.png"));
				break;
			case 1:
				m_pSpr->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("b_mario_jump_star0.png"));
				break;
			case 2:
				m_pSpr->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("b_mario_jump_star1.png"));
				break;
			case 3:
				m_pSpr->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("b_mario_jump_star2.png"));
				break;
			}
			break;
		}
		}
	}
	else
	{
		switch (m_pState)
		{
		case PLAYER_STATE_SMALL:
		{
			m_pSpr->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("s_mario_jump.png"));
			break;
		}
		case PLAYER_STATE_BIG:
		{
			m_pSpr->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("b_mario_jump.png"));
			break;
		}
		case PLAYER_STATE_FIRE:
		{
			m_pSpr->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("f_mario_jump.png"));
			break;
		}
		}
	}
}

void Player::ChangeRunSprite()
{
	int run = m_iRunCount % 3;
	if (m_bStar)
	{
		int i = m_iStarCount % 4;
		switch (m_pState)
		{
		case PLAYER_STATE_SMALL:
		{
			char szTemp[128];
			switch (i)
			{
			case 0:
				sprintf(szTemp, "s_mario_run%d.png", run);
				m_pSpr->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(szTemp));
				break;
			case 1:	
				sprintf(szTemp, "s_mario_run_star%d_%d.png", run, i-1);
				m_pSpr->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(szTemp));
				break;
			case 2:
				sprintf(szTemp, "s_mario_run_star%d_%d.png", run, i-1);
				m_pSpr->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(szTemp));
				break;
			case 3:
				sprintf(szTemp, "s_mario_run_star%d_%d.png", run, i-1);
				m_pSpr->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(szTemp));
				break;
			}
			break;
		}
		case PLAYER_STATE_BIG:
		{
			char szTemp[128];
			switch (i)
			{
			case 0:
				sprintf(szTemp, "b_mario_run%d.png", run);
				m_pSpr->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(szTemp));
				break;
			case 1:
				sprintf(szTemp, "b_mario_run_star%d_%d.png", run, i - 1);
				m_pSpr->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(szTemp));
				break;
			case 2:
				sprintf(szTemp, "b_mario_run_star%d_%d.png", run, i - 1);
				m_pSpr->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(szTemp));
				break;
			case 3:
				sprintf(szTemp, "b_mario_run_star%d_%d.png", run, i - 1);
				m_pSpr->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(szTemp));
				break;
			}
			break;
		}
		case PLAYER_STATE_FIRE:
		{
			char szTemp[128];
			switch (i)
			{
			case 0:
				sprintf(szTemp, "f_mario_run%d.png", run);
				m_pSpr->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(szTemp));
				break;
			case 1:
				sprintf(szTemp, "b_mario_run_star%d_%d.png", run, i - 1);
				m_pSpr->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(szTemp));
				break;
			case 2:
				sprintf(szTemp, "b_mario_run_star%d_%d.png", run, i - 1);
				m_pSpr->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(szTemp));
				break;
			case 3:
				sprintf(szTemp, "b_mario_run_star%d_%d.png", run, i - 1);
				m_pSpr->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(szTemp));
				break;
			}
			break;
		}
		}
	}
	else
	{
		char szTemp[128];
		switch (m_pState)
		{
		case PLAYER_STATE_SMALL:
		{
			sprintf(szTemp, "s_mario_run%d.png", run);
			m_pSpr->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(szTemp));
			break;
		}
		case PLAYER_STATE_BIG:
		{
			sprintf(szTemp, "b_mario_run%d.png", run);
			m_pSpr->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(szTemp));
			break;
		}
		case PLAYER_STATE_FIRE:
		{
			sprintf(szTemp, "f_mario_run%d.png", run);
			m_pSpr->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(szTemp));
			break;
		}
		}
	}
}

void Player::ChangeDashSprite()
{
	if (m_bStar)
	{
		int i = m_iStarCount % 4;
		switch (m_pState)
		{
		case PLAYER_STATE_SMALL:
		{
			switch (i)
			{
			case 0:
				m_pSpr->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("s_mario_dash.png"));
				break;
			case 1:
				m_pSpr->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("s_mario_dash_star0.png"));
				break;
			case 2:
				m_pSpr->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("s_mario_dash_star1.png"));
				break;
			case 3:
				m_pSpr->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("s_mario_dash_star2.png"));
				break;
			}
			break;
		}
		case PLAYER_STATE_BIG:
		{
			switch (i)
			{
			case 0:
				m_pSpr->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("b_mario_dash.png"));
				break;
			case 1:
				m_pSpr->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("b_mario_dash_star0.png"));
				break;
			case 2:
				m_pSpr->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("b_mario_dash_star1.png"));
				break;
			case 3:
				m_pSpr->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("b_mario_dash_star2.png"));
				break;
			}
			break;
		}
		case PLAYER_STATE_FIRE:
		{
			switch (i)
			{
			case 0:
				m_pSpr->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("f_mario_dash.png"));
				break;
			case 1:
				m_pSpr->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("b_mario_dash_star0.png"));
				break;
			case 2:
				m_pSpr->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("b_mario_dash_star1.png"));
				break;
			case 3:
				m_pSpr->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("b_mario_dash_star2.png"));
				break;
			}
			break;
		}
		}
	}
	else
	{
		switch (m_pState)
		{
		case PLAYER_STATE_SMALL:
		{
			m_pSpr->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("s_mario_dash.png"));
			break;
		}
		case PLAYER_STATE_BIG:
		{
			m_pSpr->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("b_mario_dash.png"));
			break;
		}
		case PLAYER_STATE_FIRE:
		{
			m_pSpr->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("f_mario_dash.png"));
			break;
		}
		}
	}
}


void Player::SetHitbox()
{
	switch (m_pState)
	{
	case PLAYER_STATE_SMALL:
	{
		m_hitbox.setRect(m_pPos.x - 3, m_pPos.y + 6 , 6, 20);
		m_frontHitbox.setRect(m_pPos.x + 16, m_pPos.y + 6, 1, 20);
		m_rearHitbox.setRect(m_pPos.x - 17, m_pPos.y + 6, 1, 20);
		m_topHitbox.setRect(m_pPos.x - 10, m_pPos.y + 30, 20, 1);
		m_bottomHitbox.setRect(m_pPos.x - 12, m_pPos.y - 1, 24, 1);
		break;
	}
	case PLAYER_STATE_BIG:
	case PLAYER_STATE_FIRE:
	{
		if (m_bDuck)
		{
			m_hitbox.setRect(m_pPos.x - 3, m_pPos.y + 6, 6, 20);
			m_frontHitbox.setRect(m_pPos.x + 16, m_pPos.y + 6, 1, 20);
			m_rearHitbox.setRect(m_pPos.x - 17, m_pPos.y + 6, 1, 20);
			m_topHitbox.setRect(m_pPos.x - 10, m_pPos.y + 30, 20, 1);
			m_bottomHitbox.setRect(m_pPos.x - 12, m_pPos.y - 1, 24, 1);
		}
		else
		{
			m_hitbox.setRect(m_pPos.x - 3, m_pPos.y + 6, 6, 52);
			m_frontHitbox.setRect(m_pPos.x + 16, m_pPos.y + 6, 1, 52);
			m_rearHitbox.setRect(m_pPos.x - 17, m_pPos.y + 6, 1, 52);
			m_topHitbox.setRect(m_pPos.x - 10, m_pPos.y + 62, 20, 1);
			m_bottomHitbox.setRect(m_pPos.x - 12, m_pPos.y - 1, 24, 1);
		}
		break;
	}
	}
	
}

Rect Player::GetHitbox(int index)
{
	switch (index)
	{
	case HITBOX_FRONT:
		return m_frontHitbox;
	case HITBOX_REAR:
		return m_rearHitbox;
	case HITBOX_TOP:
		return m_topHitbox;
	case HITBOX_BOTTOM:
		return m_bottomHitbox;
	case HITBOX_BODY:
		return m_hitbox;
	}
}

void Player::CheckJumpTime(float ElapsedTime)
{
	if (m_bOnGround && !m_bJump)
	{
		m_bCheckJump = true;
		m_fCheckJumpTime += ElapsedTime;
		if (m_fCheckJumpTime >= 0.2f)
		{
			m_fCheckJumpTime = 0.2f;
			Jump(m_fCheckJumpTime);
		}
	}
}


void Player::CheckJumpTime()
{
	if (m_bOnGround && !m_bJump)
	{
		if (m_fCheckJumpTime < 0.2f)
		{
			if (m_fCheckJumpTime < 0.1f)
			{
				m_fCheckJumpTime = 0.1f;
			}
			Jump(m_fCheckJumpTime);
		}
	}
}

Point Player::GetPos()
{
	return m_pPos;
}

float Player::GetPosX()
{
	return m_pPos.x;
}

void Player::SetChange(bool change)
{
	m_bChange = change;
}

void Player::SetbAction(bool action)
{
	m_bAction = action;
}

void Player::RunAction(Action* action)
{
	if (m_pCurAction != NULL)
	{
		m_pSpr->stopAction(m_pCurAction);
	}
	m_pSpr->runAction(action);
	m_bAction = true;
	m_pCurAction = action;
}

void Player::RunSeq(Sequence * seq)
{
	if (m_pCurAction != NULL)
	{
		m_pSpr->stopAction(m_pCurAction);
	}
	m_pSpr->runAction(seq);
}

PMOVE_STATE Player::GetMState()
{
	return m_pmoveState;
}

PMOVE_STATE Player::GetDirection()
{
	return m_curMoveState;
}

PLAYER_STATE Player::GetState()
{
	return m_pState;
}

void Player::ChangePlayer(PLAYER_STATE state)
{
	m_pState = state;
	switch (state)
	{
	case PLAYER_STATE_SMALL:
	{
		RunAction(m_pStoBAction->reverse());
		break;
	}
	case PLAYER_STATE_BIG:
	{
		switch (m_pState)
		{
		case PLAYER_STATE_SMALL:
		{
			m_bChange = true;
			m_pState = PLAYER_STATE_BIG;
			CallFunc* func = CallFunc::create(CC_CALLBACK_0(Player::SetChange, this, false));
			Sequence* seq = Sequence::create(m_pStoBAction, func, NULL);
			RunSeq(seq);
			break;
		}
		case PLAYER_STATE_BIG:
		{
			break;
		}
		case PLAYER_STATE_FIRE:
		{
			RunAction(m_pBtoFAction->reverse());
			break;
		}
		}
		break;
	}
	case PLAYER_STATE_FIRE:
	{
		switch (m_pState)
		{
		case PLAYER_STATE_SMALL:
		{
			m_bChange = true;
			m_pState = PLAYER_STATE_FIRE;
			CallFunc* func = CallFunc::create(CC_CALLBACK_0(Player::SetChange, this, false));
			Sequence* seq = Sequence::create(m_pStoFAction, func, NULL);
			RunSeq(seq);
			break;
		}
		case PLAYER_STATE_BIG:
		{
			m_bChange = true;
			m_pState = PLAYER_STATE_FIRE;
			CallFunc* func = CallFunc::create(CC_CALLBACK_0(Player::SetChange, this, false));
			Sequence* seq = Sequence::create(m_pBtoFAction, func, NULL);
			RunSeq(seq);
			break;
		}
		case PLAYER_STATE_FIRE:
		{
			break;
		}
		}
		break;
	}
	}
}

void Player::Die(bool check)
{
	UiManager::GetInstance()->DecLife();
	m_bDie = true;
	m_pSpr->stopAllActions();
	JumpBy* jump = JumpBy::create(1.5f, Vec2(0, -600), 300, 1);
	CallFunc* func = CallFunc::create(CC_CALLBACK_0(Player::CheckFinish, this));
	Sequence* seq = Sequence::create(DelayTime::create(0.5f), jump, func, NULL);
	if(check)
	{
		m_pSpr->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("s_mario_die.png"));
		m_pSpr->runAction(seq);
	}
}

void Player::Die()
{
	m_bDie = true;
	m_pSpr->stopAllActions();
	m_pSpr->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("s_mario_die.png"));
	JumpBy* jump = JumpBy::create(1.5f, Vec2(0, -600), 300, 1);
	CallFunc* func = CallFunc::create(CC_CALLBACK_0(Player::ChangeScene, this, 1));
	Sequence* seq = Sequence::create(DelayTime::create(0.5f), jump, func, NULL);
	
	m_pSpr->runAction(seq);
}

void Player::Upgrade()
{
	switch (m_pState)
	{
	case PLAYER_STATE_SMALL:
	{
		m_bChange = true;
		m_pState = PLAYER_STATE_BIG;
		CallFunc* func = CallFunc::create(CC_CALLBACK_0(Player::SetChange, this, false));
		Sequence* seq = Sequence::create(m_pStoBAction, func, NULL);
		RunSeq(seq);
		break;
	}
	case PLAYER_STATE_BIG:
	{
		m_bChange = true;
		m_pState = PLAYER_STATE_FIRE;
		CallFunc* func = CallFunc::create(CC_CALLBACK_0(Player::SetChange, this, false));
		Sequence* seq = Sequence::create(m_pBtoFAction, func, NULL);
		RunSeq(seq);
		break;
	}
	case PLAYER_STATE_FIRE:
	{
		m_pState = PLAYER_STATE_FIRE;
		break;
	}
	}
	
}

void Player::Downgrade()
{
	switch (m_pState)
	{
	case PLAYER_STATE_SMALL:
	{
		Die(true);
		break;
	}
	case PLAYER_STATE_BIG:
	{
		m_bChange = true;
		m_pState = PLAYER_STATE_SMALL;
		CallFunc* func = CallFunc::create(CC_CALLBACK_0(Player::SetChange, this, false));
		Spawn* spawn = Spawn::create(m_pStoBAction->reverse(), Blink::create(1.1f, 8), NULL);
		Sequence* seq = Sequence::create(spawn, func, NULL);
		RunSeq(seq);
		break;
	}
	case PLAYER_STATE_FIRE:
	{
		m_bChange = true;
		m_pState = PLAYER_STATE_BIG;
		CallFunc* func = CallFunc::create(CC_CALLBACK_0(Player::SetChange, this, false));
		Spawn* spawn = Spawn::create(m_pBtoFAction->reverse(), Blink::create(1.1f, 8), NULL);
		Sequence* seq = Sequence::create(spawn, func, NULL);
		RunSeq(seq);
		break;
	}
	}
}

void Player::Fire()
{
	if (m_pState == PLAYER_STATE_FIRE && !m_bFinish)
	{
		Vec2 pos = m_pSpr->getPosition();
		pos.y += 32;
		FireManager::GetInstance()->MakeFire(m_curMoveState, pos);
	}
}

void Player::SetPosition(int x, int y)
{
	m_pPos.x = x;
	m_pPos.y = y - 15;
	m_pSpr->setPosition(m_pPos);
	SetHitbox();
}

void Player::Finish(Vec2 pos)
{
	m_bStar = false;
	m_pSpr->stopAllActions();
	m_bFinish = true;
	Vector<SpriteFrame*> HanganimationFrame(2);
	Animation* hanganimation;
	Animate* hanganimate;
	Vector<SpriteFrame*> WalkanimationFrame(2);
	Animation* Walkanimation;
	Animate* Walkanimate;
	switch (m_pState)
	{
	case PLAYER_STATE_SMALL:
	{
		for (int i = 0; i < 2; i++)
		{
			char szFileName[256];
			sprintf(szFileName, "s_mario_hang%d.png", i);
			SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(szFileName);
			HanganimationFrame.pushBack(frame);
		}
		hanganimation = Animation::createWithSpriteFrames(HanganimationFrame, 0.2f);
		hanganimate = Animate::create(hanganimation);

		for (int i = 0; i < 3; i++)
		{
			char szFileName[256];
			sprintf(szFileName, "s_mario_run%d.png", i);
			SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(szFileName);
			WalkanimationFrame.pushBack(frame);
		}
		Walkanimation = Animation::createWithSpriteFrames(WalkanimationFrame, 0.2f);
		Walkanimate = Animate::create(Walkanimation);
		break;
	}
	case PLAYER_STATE_BIG:
	{
		for (int i = 0; i < 2; i++)
		{
			char szFileName[256];
			sprintf(szFileName, "b_mario_hang%d.png", i);
			SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(szFileName);
			HanganimationFrame.pushBack(frame);
		}
		hanganimation = Animation::createWithSpriteFrames(HanganimationFrame, 0.2f);
		hanganimate = Animate::create(hanganimation);

		for (int i = 0; i < 3; i++)
		{
			char szFileName[256];
			sprintf(szFileName, "b_mario_run%d.png", i);
			SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(szFileName);
			WalkanimationFrame.pushBack(frame);
		}
		Walkanimation = Animation::createWithSpriteFrames(WalkanimationFrame, 0.2f);
		Walkanimate = Animate::create(Walkanimation);
		break;
	}
	case PLAYER_STATE_FIRE:
	{
		for (int i = 0; i < 2; i++)
		{
			char szFileName[256];
			sprintf(szFileName, "f_mario_hang%d.png", i);
			SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(szFileName);
			HanganimationFrame.pushBack(frame);
		}
		hanganimation = Animation::createWithSpriteFrames(HanganimationFrame, 0.2f);
		hanganimate = Animate::create(hanganimation);

		for (int i = 0; i < 3; i++)
		{
			char szFileName[256];
			sprintf(szFileName, "f_mario_run%d.png", i);
			SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(szFileName);
			WalkanimationFrame.pushBack(frame);
		}
		Walkanimation = Animation::createWithSpriteFrames(WalkanimationFrame, 0.2f);
		Walkanimate = Animate::create(Walkanimation);
		break;
	}
	}
	hang = RepeatForever::create(hanganimate);
	hang->retain();
	walk = RepeatForever::create(Walkanimate);
	walk->retain();
	m_pSpr->runAction(hang);

	Vec2 des = pos;
	des.x -= 16;
	des.y -= 16;
	int gap = m_pSpr->getPositionY() - des.y;
	EffectManager::GetInstance()->MakeScoreEffect(5000, m_pSpr->getPosition());
	//UiManager::GetInstance()->AddScore((int)(gap / 100) * 10 * 1000);
	MoveTo* move = MoveTo::create(gap/ 150.0f, des);
	des.x += 32;
	Place* place = Place::create(des);
	CallFunc* Flip1 = CallFunc::create(CC_CALLBACK_0(Player::FlipX, this, true));
	CallFunc* Flip2 = CallFunc::create(CC_CALLBACK_0(Player::FlipX, this, false));
	CallFunc* StopHangFunc = CallFunc::create(CC_CALLBACK_0(Player::StopAction, this, hang));
	CallFunc* JumpSprite = CallFunc::create(CC_CALLBACK_0(Player::ChangeJumpSprite, this));
	CallFunc* WalkFunc = CallFunc::create(CC_CALLBACK_0(Player::RunFinishAction, this, walk));
	CallFunc* InvisibleFunc = CallFunc::create(CC_CALLBACK_0(Player::SetVisible, this, false));
	CallFunc* changeScene = CallFunc::create(CC_CALLBACK_0(Player::ChangeScene, this, 2));
	des.x += 48;
	des.y -= 32;
	JumpTo* jump = JumpTo::create(0.8f, des, 32, 1);
	Vec2 Destination = GameInfo::GetInstance()->GetDesPos();
	Destination.y -= 16;
	int gapX = Destination.x - des.x;
	MoveTo* move1 = MoveTo::create((gapX / 96), Destination);
	Sequence* seq = Sequence::create(move, Flip1, place, DelayTime::create(0.5f), Flip2, StopHangFunc, JumpSprite, jump, WalkFunc, move1, InvisibleFunc, changeScene, NULL);
	m_pSpr->runAction(seq);

}

void Player::ChangeHangSprite()
{
	
}

void Player::Jump(float jumptime)
{
	m_bCheckJump = false;
	m_fCheckJumpTime = 0;
	m_bJump = true;
	m_bOnGround = false;
	m_fJumpSpeed = jumptime * 2300;
	m_bAction = false;
	//m_pSpr->stopAction(m_pSRunAction);
	m_pSpr->stopAction(m_pCurAction);
	//m_pSpr->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("s_mario_jump.png"));
}

void Player::Run()
{
}

bool Player::GetDestroy()
{
	return m_bDestroy;
}

void Player::FlipX(bool flip)
{
	m_pSpr->setFlipX(flip);
}

void Player::StopAction(Action * action)
{
	m_pSpr->stopAction(action);
}

void Player::RunFinishAction(Action * action)
{
	m_pSpr->runAction(action);
}

void Player::SetVisible(bool visible)
{
	m_pSpr->setVisible(visible);
}

void Player::Reset()
{
	//m_pSpr->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("s_mario_stand.png"));
	//m_pState = PLAYER_STATE_SMALL;
	m_bRun = false;
	m_bFire = false;
	m_bStar = false;
	m_bFinish = false;
	m_bChange = false;
	m_bDuck = false;
	m_bDash = false;
	m_bOnGround = true;
	m_bJump = false;
	m_bDie = false;
	m_iStarCount = 0;
	m_fStarCountTime = 0;
	m_fStarTime = 0;
	m_fGravityTime = 0;
	m_fJumpSpeed = 0;
	m_fCheckJumpTime = 0;
	m_fDieTime = 0;
	m_pmoveState = PMOVE_STATE_STOP;
	m_curMoveState = PMOVE_STATE_RIGHT;
	m_fLeftAccel = 0;
	m_fRightAccel = 0;
	m_fLeftSpeed = 0;
	m_fRightSpeed = 0;
	m_bDestroy = false;
	m_bAction = false;
	m_bCheckJump = false;
	m_bDown = false;
	m_iRunCount = 0;
	m_fRunTime = 0;
	m_fRunCountTime = 0;
	m_pOldState = m_pState;

	m_pCurAction = NULL;
}

void Player::ResetAll()
{
	m_pSpr->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("s_mario_stand.png"));
	m_pState = PLAYER_STATE_SMALL;
	m_bRun = false;
	m_bFire = false;
	m_bStar = false;
	m_bFinish = false;
	m_bChange = false;
	m_bDuck = false;
	m_bDash = false;
	m_bOnGround = true;
	m_bJump = false;
	m_bDie = false;
	m_iStarCount = 0;
	m_fStarCountTime = 0;
	m_fStarTime = 0;
	m_fGravityTime = 0;
	m_fJumpSpeed = 0;
	m_fCheckJumpTime = 0;
	m_fDieTime = 0;
	m_pmoveState = PMOVE_STATE_STOP;
	m_curMoveState = PMOVE_STATE_RIGHT;
	m_fLeftAccel = 0;
	m_fRightAccel = 0;
	m_fLeftSpeed = 0;
	m_fRightSpeed = 0;
	m_bDestroy = false;
	m_bAction = false;
	m_bCheckJump = false;
	m_bDown = false;
	m_iRunCount = 0;
	m_fRunTime = 0;
	m_fRunCountTime = 0;
	m_pOldState = m_pState;

	m_pCurAction = NULL;
}

void Player::ChangeScene(int index)
{
	switch (index)
	{
	case 0:
		Director::getInstance()->replaceScene(GameOverScene::create());
		break;
	case 1:
		Director::getInstance()->replaceScene(TimeOverScene::create());
		break;
	case 2:
		if (GameInfo::GetInstance()->GetStage() == 1)
		{
			m_pSpr->setVisible(true);
			GameInfo::GetInstance()->SetStage(2);
			GameInfo::GetInstance()->SetState(GAME_STATE_SEMITITLE);
		}
		else
		{
			Director::getInstance()->replaceScene(ClearScene::create());
		}
		break;
	}
}

void Player::CheckFinish()
{
	ResetAll();
	if (UiManager::GetInstance()->GetLife() < 0)
	{
		ChangeScene(0);
	}
}

void Player::Cheat()
{
	m_bStar = true;
}

Player::Player()
{
}


Player::~Player()
{
}
