#include "ItemFlower.h"



void ItemFlower::Init(Layer * layer, int index, Vec2 pos)
{
	MItem::Init(layer, index, pos);
	SetHitbox();
	Vector<SpriteFrame*> animationFrame(4);
	for (int i = 0; i < 4; i++)
	{
		char szFileName[256];
		sprintf(szFileName, "item_flower%d.png", i);
		SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(szFileName);
		animationFrame.pushBack(frame);
	}
	Animation* animation = Animation::createWithSpriteFrames(animationFrame, 0.1f);
	Animate* animate = Animate::create(animation);
	m_pItem->runAction(RepeatForever::create(animate));

	MoveUpItem();
}

void ItemFlower::Update(float ElapsedTime)
{
	if (m_bMove)
	{
		
	}
	else
	{
		m_pPos = m_pItem->getPosition();
	}
	MItem::Update(ElapsedTime);
	SetHitbox();
}

void ItemFlower::SetHitbox()
{
	m_bodyHitbox.setRect(m_pPos.x - 16, m_pPos.y, 32, 32);
	m_frontHitbox.setRect(m_pPos.x + 16, m_pPos.y + 6, 2, 20);
	m_rearHitbox.setRect(m_pPos.x - 18, m_pPos.y + 6, 2, 20);
	m_bottomHitbox.setRect(m_pPos.x - 10, m_pPos.y - 1, 20, 1);
	m_topHitbox.setRect(m_pPos.x - 10, m_pPos.y + 30, 20, 2);
}

ItemFlower::ItemFlower()
{
}


ItemFlower::~ItemFlower()
{
}
