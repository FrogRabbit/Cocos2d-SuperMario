#include "MapBlock.h"
#include "EffectManager.h"
#include "ItemManager.h"
#include "PlayerManager.h"
#include "MapManager.h"



void MapBlock::Init(Layer * layer, int index, int x, int y, int item, int itemsize)
{
	m_bAlive = false;
	m_iIndex = index;
	m_bAction = false;
	switch (m_iIndex)
	{
	case 1:
		m_pBlock = Sprite::create("block_rock0.png");
		m_bBreak = false;
		m_bMoveUp = false;
		break;
	case 2:
		m_pBlock = Sprite::create("block_rock1.png");
		m_bBreak = false;
		m_bMoveUp = false;
		break;
	case 3:
		m_pBlock = Sprite::create("block_brick0.png");
		m_bBreak = true;
		m_bMoveUp = true;
		break;
	case 4:
		m_pBlock = Sprite::create("block_brick1.png");
		m_bBreak = true;
		m_bMoveUp = true;
		break;
	case 5:
		m_pBlock = Sprite::create("block_pipe0.png");
		m_pBlock->setAnchorPoint(Vec2(0.25f, 0.5f));
		m_bBreak = false;
		m_bMoveUp = false;
		break;
	case 6:
		m_pBlock = Sprite::create("block_pipe1.png");
		m_pBlock->setAnchorPoint(Vec2(0.25f, 0.5f));
		m_bBreak = false;
		m_bMoveUp = false;
		break;
	case 7:
		m_pBlock = Sprite::create("block_pipe2.png");
		m_pBlock->setAnchorPoint(Vec2(0.25f, 0.5f));
		m_bBreak = false;
		m_bMoveUp = false;
		break;
	case 8:
	{
		m_bBreak = false;
		m_bMoveUp = true;
		Vector<SpriteFrame*> animationFrame(4);
		for (int i = 0; i < 3; i++)
		{
			char szFileName[256];
			sprintf(szFileName, "block_qst%d.png", i);
			SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(szFileName);
			animationFrame.pushBack(frame);
		}
		SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("block_qst1.png");
		animationFrame.pushBack(frame);
		Animation* animation = Animation::createWithSpriteFrames(animationFrame, 0.25f);
		Animate* animate = Animate::create(animation);
		m_pBlock = Sprite::createWithSpriteFrameName("block_qst0.png");
		m_pRepeat = RepeatForever::create(animate);
		m_pRepeat->retain();
		m_pBlock->runAction(m_pRepeat);
		break;
	}
	case 9:
		m_bBreak = false;
		m_bMoveUp = false;
		m_pBlock = Sprite::create("jumper0.png");
		break;
	case 10:
		m_bBreak = false;
		m_bMoveUp = false;
		m_pBlock = Sprite::create("pole.png");
		m_pBlock->setAnchorPoint(Vec2(0.5f, 0.05f));
		m_pFlag = Sprite::create("Flag.png");
		m_pFlag->setScale(2.0f);
		m_pFlag->setAnchorPoint(Vec2(1.0f, 0.5f));
		m_pFlag->setPosition(Vec2(x, y + (32 * 8) + 6));
		layer->addChild(m_pFlag, 3);
		break;
	}
	m_bItem = false;
	m_iItemIndex = item;
	m_iItemSize = itemsize;
	if (m_iItemIndex != 0)
	{
		m_bBreak = false;
		m_bItem = true;
	}
	if (m_iIndex == 10)
	{
		m_hitbox.setRect(x - 2, y - 16, 4, 500);
	}
	else
	{
		m_hitbox.setRect(x - 16, y - 16, 32, 32);
	}
	if (m_iIndex == 5 || m_iIndex == 6)
	{
		m_hitbox.setRect(x - 16, y - 16, 64, 32);
	}
	m_pBlock->setScale(2.0f);
	m_pBlock->setPosition(Vec2(x, y));
	layer->addChild(m_pBlock, 2);
	
}

void MapBlock::Break()
{
	if (m_bBreak && !m_bAction)
	{
		m_bAlive = true;
		m_bAction = true;
		EffectManager::GetInstance()->MakeBlockEffect(m_pBlock->getPosition());
	}
}

void MapBlock::MoveUp()
{
	if (m_bMoveUp && !m_bAction)
	{
		m_bAction = true;
		JumpBy* jump1;
		jump1 = JumpBy::create(0.2f, Vec2(0, 0), 10, 1);
		JumpBy* jump2;
		jump2 = JumpBy::create(0.1f, Vec2(0, 0), -5, 1);
		CallFunc* func = CallFunc::create(CC_CALLBACK_0(MapBlock::SetbAction, this, false));
		Sequence* seq = Sequence::create(jump1, jump2, func, NULL);
		m_pBlock->runAction(seq);
	}
}

void MapBlock::MakeItem()
{
	if (m_iItemSize > 0)
	{
		m_iItemSize--;
		ItemManager::GetInstance()->MakeItem(m_iItemIndex, m_pBlock->getPosition());
		if (m_iItemSize == 0)
		{

			//m_pBlock->stopallAction();
			ChangeBlock();
		}
	}
}

void MapBlock::ChangeBlock()
{
	if (m_iIndex == 8)
	{
		m_pBlock->stopAction(m_pRepeat);
	}
	m_pBlock->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("block_hit.png"));
	m_bMoveUp = false;
}

bool MapBlock::CheckOnGround(Rect hitbox)
{
	if (m_hitbox.intersectsRect(hitbox))
	{
		return true;
	}
	return  false;
}

void MapBlock::TopCrash()
{
	if (m_bBreak)
	{
		if (PlayerManager::GetInstance()->GetState() == PLAYER_STATE_SMALL)
		{
			MoveUp();
		}
		else
		{
			Break();
		}
	}
	else
	{
		if (m_bItem)
		{
			if (!m_bAction)
			{
				MoveUp();
				MakeItem();
			}
			
		}
		else
		{

		}
	}
}

void MapBlock::SetbAction(bool action)
{
	m_bAction = action;
}

bool MapBlock::CheckAlive()
{
	return m_bAlive;
}

void MapBlock::Release(Layer * layer)
{
	layer->removeChild(m_pBlock);
	if (m_iIndex == 10)
	{
		layer->removeChild(m_pFlag);
	}
}

Point MapBlock::GetPos()
{
	return m_pBlock->getPosition();
}

bool MapBlock::CheckFinish(Rect hitbox)
{
	if (m_iIndex == 10 && !m_bAction)
	{
		if (m_hitbox.intersectsRect(hitbox))
		{
			MapManager::GetInstance()->Finish();
			PlayerManager::GetInstance()->Finish(m_pBlock->getPosition());
			m_bAction = true;
			MoveTo* move = MoveTo::create(1.2f, m_pBlock->getPosition());
			m_pFlag->runAction(move);
			return true;
		}
	}
	return false;
}


MapBlock::MapBlock()
{
}


MapBlock::~MapBlock()
{
}
