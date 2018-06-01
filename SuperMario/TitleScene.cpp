#include "TitleScene.h"
#include "SimpleAudioEngine.h"
#include "GameScene.h"
USING_NS_CC;

Scene* TitleScene::createScene()
{
	return TitleScene::create();
}

// on "init" you need to initialize your instance
bool TitleScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	
	m_background = Sprite::create("background_main.png");
	m_background->setAnchorPoint(Vec2(0, 0));
	m_background->setPosition(Vec2(0, 0));
	m_background->setContentSize(Size(600, 448));
	this->addChild(m_background);

	m_title = Sprite::create("title.png");
	m_title->setPosition(Vec2(300, 300));
	m_title->setScale(2.5f);
	this->addChild(m_title);

	m_Label = Label::create();
	m_Label->setString("Please Enter Any Key");
	m_Label->setPosition(Vec2(300, 150));
	m_Label->setScale(1.2f);
	m_Label->setSystemFontSize(15);
	FadeIn* fadein = FadeIn::create(0.5f);
	ScaleTo* scaledown = ScaleTo::create(0.5f, 1.0f);
	FadeOut* fadeout = FadeOut::create(0.5f);
	ScaleTo* scaleup = ScaleTo::create(0.5f, 1.2f);
	Spawn* spawn1 = Spawn::create(fadeout, scaledown,NULL);
	Spawn* spawn2 = Spawn::create(fadein, scaleup, NULL);
	Sequence* seq = Sequence::create(spawn1, spawn2, NULL);
	m_Label->runAction(RepeatForever::create(seq));
	this->addChild(m_Label);

	m_interface = Label::create();
	m_interface->setString("\"Z\" - Jump\n\"X\" - Dash, Fire\n\"Arrow\" - Move");
	m_interface->setAnchorPoint(Vec2(0, 0));
	m_interface->setSystemFontSize(12);
	m_interface->setPosition(Vec2(50, 50));
	this->addChild(m_interface);

	auto key_listener = EventListenerKeyboard::create();
	key_listener->onKeyPressed = CC_CALLBACK_2(TitleScene::OnKeyPress, this);
	key_listener->onKeyReleased = CC_CALLBACK_2(TitleScene::OnKeyUp, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(key_listener, this);

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	this->schedule(schedule_selector(TitleScene::Update));
	return true;
}


void TitleScene::Update(float ElapsedTime)
{
	
}

void TitleScene::ChangeScene()
{
	
}


void TitleScene::OnKeyPress(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{
	switch (keyCode)
	{
	default:
	//case EventKeyboard::KeyCode::KEY_Z:
	{
		Director::getInstance()->replaceScene(GameScene::createScene());
		break;
	}
	}
}

void TitleScene::OnKeyUp(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{
}
