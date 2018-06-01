#include "FireEffect.h"



void FireEffect::Init(Layer * layer,int x, int y)
{
	m_bAlive = false;
	m_pSpr = Sprite::create("effect_fire0.png");
	m_pSpr->setPosition(Vec2(x, y));
	m_pSpr->setScale(2.0f);
	Vector<SpriteFrame*> animationFrame(3);
	for (int i = 0; i < 3; i++)
	{
		char szFileName[256];
		sprintf(szFileName, "effect_fire%d.png", i);
		SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(szFileName);
		animationFrame.pushBack(frame);
	}
	Animation* animation = Animation::createWithSpriteFrames(animationFrame, 0.1f);
	Animate* animate = Animate::create(animation);
	CallFunc* func = CallFunc::create(CC_CALLBACK_0(FireEffect::SetAlive, this, true));
	Sequence* seq = Sequence::create(animate, func, NULL);
	layer->addChild(m_pSpr,3);
	m_pSpr->runAction(seq);

}

void FireEffect::Update(float ElapsedTime)
{
	
}

void FireEffect::Release(Layer * layer)
{
	layer->removeChild(m_pSpr);
}

void FireEffect::SetAlive(bool alive)
{
	m_bAlive = alive;
}

FireEffect::FireEffect()
{
}


FireEffect::~FireEffect()
{
}
