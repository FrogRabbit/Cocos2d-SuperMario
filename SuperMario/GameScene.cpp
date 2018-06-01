#include "GameScene.h"
#include "MapManager.h"
#include "EffectManager.h"
#include "BlockManager.h"
#include "PlayerManager.h"
#include "ItemManager.h"
#include "EnemyManager.h"
#include "FireManager.h"
#include "GameInfo.h"
#include "UiManager.h"


cocos2d::Scene * GameScene::createScene()
{
	Scene *scene = Scene::create();
	GameScene *layer = GameScene::create();
	scene->addChild(layer);
	return scene;
}

bool GameScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	UiManager::GetInstance()->Init(this);
	MapManager::GetInstance()->Init(this);
	Layer* layer = MapManager::GetInstance()->GetLayer();
	PlayerManager::GetInstance()->Init(layer);
	BlockManager::GetInstance()->Init(layer);
	EffectManager::GetInstance()->Init(layer);
	ItemManager::GetInstance()->Init(layer);
	EnemyManager::GetInstance()->Init(layer);
	FireManager::GetInstance()->Init(layer);
	GameInfo::GetInstance()->Init();
	MapManager::GetInstance()->MakeMap();

	m_ZKey = false;
	m_XKey = false;
	m_DownKey = false;
	m_LeftKey = false;
	m_RightKey = false;
	auto key_listener = EventListenerKeyboard::create();
	key_listener->onKeyPressed = CC_CALLBACK_2(GameScene::OnKeyPress, this);
	key_listener->onKeyReleased = CC_CALLBACK_2(GameScene::OnKeyUp, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(key_listener, this);

	
	this->schedule(schedule_selector(GameScene::Update));

	return true;
}

void GameScene::OnKeyPress(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
	{
		PlayerManager::GetInstance()->Duck();
		m_DownKey = true;
		break;
	}
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
	{
		//PlayerManager::GetInstance()->MoveLeft(0);
		m_LeftKey = true;
		break;
	}
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
	{
		//PlayerManager::GetInstance()->MoveRight(0);
		m_RightKey = true;
		break;
	}
	case EventKeyboard::KeyCode::KEY_Z:
	{
		//PlayerManager::GetInstance()->Dash();
		m_ZKey = true;
		break;
	}
	case EventKeyboard::KeyCode::KEY_X:
	{
		PlayerManager::GetInstance()->Fire();
		PlayerManager::GetInstance()->Dash();
		m_XKey = true;
		break;
	}
	case EventKeyboard::KeyCode::KEY_P:
	{
		PlayerManager::GetInstance()->Cheat();
		break;
	}
	}
}

void GameScene::OnKeyUp(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
	{
		PlayerManager::GetInstance()->Stand();
		m_DownKey = false;
		break;
	}
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
	{
		PlayerManager::GetInstance()->Stop();
		m_LeftKey = false;
		break;
	}
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
	{
		PlayerManager::GetInstance()->Stop();
		m_RightKey = false;
		break;
	}
	case EventKeyboard::KeyCode::KEY_Z:
	{
		//PlayerManager::GetInstance()->StopDash();
		PlayerManager::GetInstance()->CheckJumpTime();
		m_ZKey = false;
		break;
	}
	case EventKeyboard::KeyCode::KEY_X:
	{
		PlayerManager::GetInstance()->StopDash();
		m_XKey = false;
		break;
	}
	}
}

void GameScene::Update(float ElapsedTime)
{
	if (m_LeftKey)
	{
		//MapManager::GetInstance()->MoveRight(ElapsedTime);
		PlayerManager::GetInstance()->MoveLeft(ElapsedTime);
	}
	if (m_RightKey)
	{
		//MapManager::GetInstance()->MoveLeft(ElapsedTime);
		PlayerManager::GetInstance()->MoveRight(ElapsedTime);
	}
	if (m_ZKey)
	{
		PlayerManager::GetInstance()->CheckJumpTime(ElapsedTime);
	}
	if (m_XKey)
	{
		
	}
	GameInfo::GetInstance()->Update(ElapsedTime);
	
}
