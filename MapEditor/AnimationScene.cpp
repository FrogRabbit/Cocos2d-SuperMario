#include "AnimationScene.h"



bool AnimationScene::Init()
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("filename");

	int size = 0; //size
	Vector<SpriteFrame*> animationFrame(size);
	for (int i = 0; i < size; i++)
	{
		char szFileName[256];
		sprintf(szFileName, "filename%d.png", i);
		SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(szFileName);
		animationFrame.pushBack(frame);
	}

	Sprite *pSpr = Sprite::createWithSpriteFrameName("first img name");
	pSpr->setPosition(Vec2(0, 0));
	addChild(pSpr);

	Animation* animation = Animation::createWithSpriteFrames(animationFrame, 0.5f/*аж╠Б*/);
	Animate* animate = Animate::create(animation);
	pSpr->runAction(RepeatForever::create(animate));

	return true;
}

AnimationScene::AnimationScene()
{
}


AnimationScene::~AnimationScene()
{
}
