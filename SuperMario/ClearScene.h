#pragma once
#include "cocos2d.h"
#include "TouchEventScene.h"
#include "define.h"

class ClearScene : public cocos2d::Scene
{
private:
	Sprite* m_background;
	Sprite* m_castle;
	Label* m_string;
	Layer* m_layer;
	Sprite* m_flag;
	float m_time;
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	virtual void OnKeyPress(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void Update(float ElapsedTime);
	ClearScene();
	~ClearScene();
	CREATE_FUNC(ClearScene);
};

