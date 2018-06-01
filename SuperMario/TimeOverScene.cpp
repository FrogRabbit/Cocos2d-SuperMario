#include "TimeOverScene.h"
#include "TitleScene.h"


cocos2d::Scene * TimeOverScene::createScene()
{
	return TimeOverScene::create();
}

bool TimeOverScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto key_listener = EventListenerKeyboard::create();
	key_listener->onKeyPressed = CC_CALLBACK_2(TimeOverScene::OnKeyPress, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(key_listener, this);

	m_layer = LayerColor::create();
	m_layer->initWithColor(Color4B(0, 0, 0, 255));
	m_layer->setContentSize(Size(600, 448));
	m_layer->setPosition(Vec2(0, 0));
	m_layer->setAnchorPoint(Vec2(0, 0));
	this->addChild(m_layer);
	m_string = Label::create();
	m_string->setString("Time Over");
	m_string->setPosition(Vec2(300, 224));
	m_string->setTextColor(Color4B(255, 255, 255, 255));
	m_string->setScale(2.0f);
	m_layer->addChild(m_string);
	FadeIn* fadein = FadeIn::create(0.5f);
	ScaleTo* scaledown = ScaleTo::create(0.5f, 1.0f);
	FadeOut* fadeout = FadeOut::create(0.5f);
	ScaleTo* scaleup = ScaleTo::create(0.5f, 1.2f);
	Spawn* spawn1 = Spawn::create(fadeout, scaledown, NULL);
	Spawn* spawn2 = Spawn::create(fadein, scaleup, NULL);
	Sequence* seq = Sequence::create(spawn1, spawn2, NULL);
	m_string->runAction(RepeatForever::create(seq));
	return true;
}

void TimeOverScene::OnKeyPress(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{
	switch (keyCode)
	{
	default:
	{
		Director::getInstance()->replaceScene(TitleScene::createScene());
		break;
	}
	}
}

TimeOverScene::TimeOverScene()
{
}


TimeOverScene::~TimeOverScene()
{
}