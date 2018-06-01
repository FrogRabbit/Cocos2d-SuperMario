#include "ItemMushRoom.h"



void ItemMushRoom::Init(Layer * layer, int index, Vec2 pos)
{
	MItem::Init(layer, index, pos);
	SetHitbox();
	m_fSpeed = 100.0f;
	m_MoveState = MOVE_STATE_RIGHT;
	switch (m_iIndex)
	{
	case 1:
	{
		m_pItem->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("item_mush0.png"));
		break;
	}
	case 2:
	{
		m_pItem->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("item_mush1.png"));
		break;
	}
	case 3:
	{
		m_pItem->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("item_mush2.png"));
		break;
	}
	}
	MoveUpItem();
}

void ItemMushRoom::Update(float ElapsedTime)
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
			m_fSpeed = 100.0f;
			break;
		}
		case MOVE_STATE_LEFT:
		{
			m_fSpeed = -100.0f;
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

void ItemMushRoom::SetHitbox()
{
	m_bodyHitbox.setRect(m_pPos.x - 16, m_pPos.y, 32, 32);
	m_frontHitbox.setRect(m_pPos.x + 16, m_pPos.y + 6, 2, 20);
	m_rearHitbox.setRect(m_pPos.x - 18, m_pPos.y + 6, 2, 20);
	m_bottomHitbox.setRect(m_pPos.x - 10, m_pPos.y - 1, 20, 1);
	m_topHitbox.setRect(m_pPos.x - 10, m_pPos.y + 30, 20, 2);
}

ItemMushRoom::ItemMushRoom()
{
}


ItemMushRoom::~ItemMushRoom()
{
}
