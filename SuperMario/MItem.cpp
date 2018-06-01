#include "MItem.h"
#include "PlayerManager.h"
#include "MapManager.h"


void MItem::Init(Layer * layer, int index, Vec2 pos)
{
	m_bAlive = false;
	m_iIndex = index;
	m_pPos.x = pos.x;
	m_pPos.y = pos.y - 6;
	m_pItem = Sprite::create();
	m_pItem->setAnchorPoint(Vec2(0.5f, 0));
	m_pItem->setScale(2.0f);
	m_pItem->setPosition(m_pPos);
	m_bMove = false;
	m_fJumpSpeed = 0;
	m_fSpeed = 0;
	m_fGravityTime = 0;
	layer->addChild(m_pItem, 1);
	/*m_bodyHitbox.setRect(m_pPos.x - 10, m_pPos.y - 16, 20, 32);
	m_bottomHitbox.setRect(m_pPos.x - 10, m_pPos.y - 18, 20, 2);
	m_rearHitbox.setRect(m_pPos.x - 17, m_pPos.y - 16, 1, 30);
	m_frontHitbox.setRect(m_pPos.x + 16, m_pPos.y - 16, 1, 30);
	*/
	/*switch (m_iIndex)
	{
	case 1:
	case 4:
	{
		if (PlayerManager::GetInstance()->GetState() == PLAYER_STATE_SMALL)
		{
			m_iIndex = 1;
			m_pItem->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("item_mush0.png"));
			MoveBy* moveby = MoveBy::create(0.5f, Vec2(0, 33));
			CallFunc* func = CallFunc::create(CC_CALLBACK_0(MItem::SetMove, this, true));
			Sequence* seq = Sequence::create(moveby, func, NULL);
			m_pItem->runAction(seq);
		}
		else
		{
			m_iIndex = 4;
			m_pItem->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("item_flower.png"));
			
			

			MoveBy* moveby = MoveBy::create(0.5f, Vec2(0, 33));
			m_pItem->runAction(moveby);
			
		}
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
	case 5:
	{
		m_pItem->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("item_star.png"));
		break;
	}
	case 6: // block coin
	{
		
		m_pItem->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("item_coin0.png"));
		break;
	}
	case 7: // no block coin
	{

		m_pItem->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("item_coin0.png"));
		break;
	}
	}*/
}

void MItem::Update(float ElapsedTime)
{
	if (32 * 21 - MapManager::GetInstance()->GetPosX() <= m_pPos.x || m_pPos.x <= -MapManager::GetInstance()->GetPosX() - 50)
	{
		m_bAlive = true;
	}
	/*if (m_bMove)
	{
	}
	else
	{
		m_pPos = m_pItem->getPosition();
	}*/
	
}

void MItem::MoveUpItem()
{
	MoveBy* moveby = MoveBy::create(0.5f, Vec2(0, 23));
	CallFunc* func = CallFunc::create(CC_CALLBACK_0(MItem::SetMove, this, true));
	Sequence* seq = Sequence::create(moveby, func, NULL);
	m_pItem->runAction(seq);
}

void MItem::SetMove(bool move)
{
	m_bMove = move;
}

void MItem::SetHitbox()
{
	
}

int MItem::GetIndex()
{
	return m_iIndex;
}

void MItem::Jump()
{
	m_fJumpSpeed = 200.0f;
}

bool MItem::CheckBodyCrash(Rect hitbox)
{
	return m_bodyHitbox.intersectsRect(hitbox);
}

void MItem::Release(Layer * layer)
{
	layer->removeChild(m_pItem);
}

bool MItem::GetAlive()
{
	return m_bAlive;
}

MItem::MItem()
{
}


MItem::~MItem()
{
}
