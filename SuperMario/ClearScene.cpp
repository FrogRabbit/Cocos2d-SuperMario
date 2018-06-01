#include "ClearScene.h"
#include "BlockManager.h"
#include "TitleScene.h"
#include "EffectManager.h"

cocos2d::Scene * ClearScene::createScene()
{
	return ClearScene::create();
}

bool ClearScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	m_layer = Layer::create();
	m_layer->setAnchorPoint(Vec2(0, 0));
	m_layer->setPosition(Vec2(0, 0));
	this->addChild(m_layer);
	EffectManager::GetInstance()->Init(m_layer);
	BlockManager::GetInstance()->Init(m_layer);

	m_background = Sprite::create("background_main.png");
	m_background->setContentSize(Size(600, 448));
	m_background->setPosition(Vec2(0, 0));
	m_background->setAnchorPoint(Vec2(0, 0));
	m_layer->addChild(m_background, 0);

	FadeIn* fadein = FadeIn::create(0.5f);
	ScaleTo* scaledown = ScaleTo::create(0.5f, 1.8f);
	FadeOut* fadeout = FadeOut::create(0.5f);
	ScaleTo* scaleup = ScaleTo::create(0.5f, 2.0f);
	Spawn* spawn1 = Spawn::create(fadeout, scaledown, NULL);
	Spawn* spawn2 = Spawn::create(fadein, scaleup, NULL);
	Sequence* seq = Sequence::create(spawn1, spawn2, NULL);

	m_string = Label::create();
	m_string->setString("Game Clear");
	m_string->setPosition(Vec2(300, 224));
	m_string->setScale(2.0f);
	m_string->runAction(RepeatForever::create(seq));
	m_layer->addChild(m_string, 3);

	m_castle = Sprite::create("castle.png");
	m_castle->setAnchorPoint(Vec2(0.5f, 0));
	m_castle->setPosition(Vec2(300, 64));
	m_castle->setScale(2.0f);
	m_layer->addChild(m_castle, 2);

	m_flag = Sprite::create("ClearFlag.png");
	m_flag->setAnchorPoint(Vec2(0.5f, 0));
	m_flag->setPosition(Vec2(300, 160));
	m_flag->setScale(2.0f);
	m_layer->addChild(m_flag, 1);

	MoveBy* move = MoveBy::create(1.0f, Vec2(0, 64));
	m_flag->runAction(move);


	auto key_listener = EventListenerKeyboard::create();
	key_listener->onKeyPressed = CC_CALLBACK_2(ClearScene::OnKeyPress, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(key_listener, this);

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 19; j++)
		{
			BlockManager::GetInstance()->MakeBlock(1, (j * 32) + 16, (i * 32) + 16, 0, 0);
		}
	}
	m_time = 0;
	this->schedule(schedule_selector(ClearScene::Update));
	return true;
}

void ClearScene::OnKeyPress(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{
	switch (keyCode)
	{
	default:
	{
		EffectManager::GetInstance()->Release();
		BlockManager::GetInstance()->Release();
		Director::getInstance()->replaceScene(TitleScene::createScene());
		break;
	}
	}
}

void ClearScene::Update(float ElapsedTime)
{
	m_time += ElapsedTime;
	if (m_time >= 0.8f)
	{
		m_time = 0;
		int x = (rand() % 400) + 100;
		int y = (rand() % 200) + 250;
		EffectManager::GetInstance()->MakeFireEffect(Vec2(x, y));
	}
	EffectManager::GetInstance()->Update(ElapsedTime);
}

ClearScene::ClearScene()
{
}


ClearScene::~ClearScene()
{
}
