#include "ItemStar.h"



void ItemStar::Init(Layer * layer, int index, Vec2 pos)
{
	MItem::Init(layer, index, pos);
	SetHitbox();
	m_fSpeed = 150.0f;
	m_MoveState = MOVE_STATE_RIGHT;

	Vector<SpriteFrame*> animationFrame(4);
	for (int i = 0; i < 4; i++)
	{
		char szFileName[256];
		sprintf(szFileName, "item_star%d.png", i);
		SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(szFileName);
		animationFrame.pushBack(frame);
	}
	Animation* animation = Animation::createWithSpriteFrames(animationFrame, 0.1f);
	Animate* animate = Animate::create(animation);
	m_pItem->runAction(RepeatForever::create(animate));
	MoveUpItem();
}

void ItemStar::Update(float ElapsedTime)
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
			m_fSpeed = 150.0f;
			break;
		}
		case MOVE_STATE_LEFT:
		{
			m_fSpeed = -150.0f;
			break;
		}
		}
		if (BlockManager::GetInstance()->CheckOnGround(m_bottomHitbox))
		{
			Vec2 pos = BlockManager::GetInstance()->GetBlockPos(m_bottomHitbox);
			m_pPos.y = pos.y + 16;
			m_fJumpSpeed = 400;
		}
		else
		{
			if (BlockManager::GetInstance()->CheckOnGround(m_topHitbox))
			{
				m_fJumpSpeed = -50;
			}
			m_fGravityTime += ElapsedTime;
			if (m_fGravityTime > 0.1f)
			{
				m_fGravityTime = 0;
				m_fJumpSpeed -= GRAVITY;
			}
		}
		m_pPos.y = m_pPos.y + (m_fJumpSpeed *ElapsedTime);
		m_pPos.x = m_pPos.x + (m_fSpeed * ElapsedTime);
		m_pItem->setPosition(m_pPos);
	}
	else
	{
		m_pPos = m_pItem->getPosition();
	}
	MItem::Update(ElapsedTime);
	SetHitbox();
}

void ItemStar::SetHitbox()
{
	m_bodyHitbox.setRect(m_pPos.x - 14, m_pPos.y, 28, 32);
	m_frontHitbox.setRect(m_pPos.x + 14, m_pPos.y + 6, 2, 20);
	m_rearHitbox.setRect(m_pPos.x - 16, m_pPos.y + 6, 2, 20);
	m_bottomHitbox.setRect(m_pPos.x - 10, m_pPos.y - 1, 20, 1);
	m_topHitbox.setRect(m_pPos.x - 10, m_pPos.y + 30, 20, 2);
}

ItemStar::ItemStar()
{
}


ItemStar::~ItemStar()
{
}
