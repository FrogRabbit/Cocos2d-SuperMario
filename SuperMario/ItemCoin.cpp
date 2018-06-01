#include "ItemCoin.h"
#include "EffectManager.h"


void ItemCoin::Init(Layer * layer, int index, Vec2 pos)
{
	
	MItem::Init(layer, index, pos);
	SetHitbox();
	UiManager::GetInstance()->AddCoin();
	EffectManager::GetInstance()->MakeScoreEffect(100, m_pItem->getPosition());
	Vector<SpriteFrame*> animationFrame(4);
	for (int i = 0; i < 3; i++)
	{
		char szFileName[256];
		sprintf(szFileName, "item_coin1_%d.png", i);
		SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(szFileName);
		animationFrame.pushBack(frame);
	}
	SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("item_coin1_1.png");
	animationFrame.pushBack(frame);

	Animation* animation = Animation::createWithSpriteFrames(animationFrame, 0.1f);
	Animate* animate = Animate::create(animation);
	m_pItem->runAction(RepeatForever::create(animate));
	Jump(layer);
}

void ItemCoin::Update(float ElapsedTime)
{
}

void ItemCoin::Jump(Layer* layer)
{
	JumpBy* jump = JumpBy::create(0.6f, Vec2(0, 32), 100, 1);
	CallFunc* func = CallFunc::create(CC_CALLBACK_0(MItem::Release, this, layer));
	Sequence* seq = Sequence::create(jump, func, NULL);
	m_pItem->runAction(seq);
}

void ItemCoin::SetHitbox()
{
	m_bodyHitbox.setRect(m_pPos.x - 16, m_pPos.y, 32, 32);
	m_frontHitbox.setRect(m_pPos.x + 16, m_pPos.y + 6, 2, 20);
	m_rearHitbox.setRect(m_pPos.x - 18, m_pPos.y + 6, 2, 20);
	m_bottomHitbox.setRect(m_pPos.x - 10, m_pPos.y - 1, 20, 1);
	m_topHitbox.setRect(m_pPos.x - 10, m_pPos.y + 30, 20, 2);
}

ItemCoin::ItemCoin()
{
}


ItemCoin::~ItemCoin()
{
}
