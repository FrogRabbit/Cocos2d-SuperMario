#pragma once
#include "cocos2d.h"
#include "define.h"

USING_NS_CC;

class GameScene : public cocos2d::Layer
{
private:
	KEY m_Key_Z;
	KEY m_Key_X;
	KEY m_Key_Left;
	KEY m_Key_Right;
	Sprite* spr;
	bool m_ZKey;
	bool m_XKey;
	bool m_LeftKey;
	bool m_RightKey;
	bool m_DownKey;

	bool m_LeftKeyPressed;
public:
	static cocos2d::Scene* createScene();
	virtual bool init();

	virtual void OnKeyPress(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	virtual void OnKeyUp(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

	void Update(float ElapsedTime);

	CREATE_FUNC(GameScene);
};

