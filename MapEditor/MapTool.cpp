#include "MapTool.h"
#include "TopUI.h"
#include "BGUI.h"
#include "BlockUI.h"
#include "ItemUI.h"
#include "EnemyUI.h"
#include "MapManager.h"
#include "MapEditor.h"
#include "EtcUI.h"



cocos2d::Scene * MapTool::createScene()
{
	Scene *scene = Scene::create();
	MapTool *layer = MapTool::create();
	scene->addChild(layer);
	return scene;
}

bool MapTool::init()
{
	if (!LayerColor::initWithColor(Color4B(50, 50, 100, 255)))
	{
		return false;
	}

	m_clickTime = 0;
	m_mouseDown = false;
	auto listener = EventListenerMouse::create();
	listener->onMouseMove = CC_CALLBACK_1(MapTool::OnMouseMove1, this);
	listener->onMouseDown = CC_CALLBACK_1(MapTool::OnMouseDown1, this);
	listener->onMouseUp = CC_CALLBACK_1(MapTool::OnMouseUp1, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	auto key_listener = EventListenerKeyboard::create();
	key_listener->onKeyPressed = CC_CALLBACK_2(MapTool::OnKeyPress, this);
	key_listener->onKeyReleased = CC_CALLBACK_2(MapTool::OnKeyUp, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(key_listener, this);

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 visibleOrigin = Director::getInstance()->getVisibleOrigin();

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("mario.plist");

	TopUI::GetInstance()->Init(this);
	BGUI::GetInstance()->Init(this);
	BlockUI::GetInstance()->Init(this);
	ItemUI::GetInstance()->Init(this);
	EnemyUI::GetInstance()->Init(this);
	MapEditor::GetInstance()->Init(this);
	EtcUI::GetInstance()->Init(this);
	MapManager::GetInstance()->LoadFile(1);

	

	

	for (int i = 0; i < BLOCKSIZE; i++)
	{
		m_blockButton[i] = ui::Button::create("rbutton_off.png", "rbutton_on.png");
	}
	for (int i = 0; i < ITEMSIZE; i++)
	{
		m_blockButton[i] = ui::Button::create("rbutton_off.png", "rbutton_on.png");
	}
	
	for (int i = 0; i < ENEMYSIZE; i++)
	{
		m_blockButton[i] = ui::Button::create("rbutton_off.png", "rbutton_on.png");
	}
	for (int i = 0; i < SUMSIZE; i++)
	{

	}
	this->schedule(schedule_selector(MapTool::Update));
	return true;
}

void MapTool::menuCloseCallback(cocos2d::Ref * pSender)
{
}


void MapTool::OnMouseMove1(cocos2d::Event * event)
{
	EventMouse* e = (EventMouse*)event;
	MapEditor::GetInstance()->SetCursor(e->getCursorX(), e->getCursorY());
}

void MapTool::OnMouseUp1(cocos2d::Event * event)
{
	m_mouseDown = false;
	if (m_clickTime <= 0.1)
	{
		MapEditor::GetInstance()->OnMouseDown();
	}
	m_clickTime = 0;
}

void MapTool::OnMouseDown1(cocos2d::Event * event)
{
	m_mouseDown = true;
	//MapEditor::GetInstance()->OnMouseDown();
}

void MapTool::OnKeyPress(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{
}

void MapTool::OnKeyUp(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{
}



void MapTool::PressBlockButton(int index)
{
}

void MapTool::PressBackgroundButton(int index)
{
}

void MapTool::PressItemButton(int index)
{
}

void MapTool::PressEnemyButton(int index)
{
}

void MapTool::Update(float ElapsedTime)
{
	MapEditor::GetInstance()->Update(ElapsedTime);
	if (m_mouseDown)
	{
		m_clickTime += ElapsedTime;
	}
}
