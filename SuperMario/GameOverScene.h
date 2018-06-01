#pragma once
#include "cocos2d.h"
#include "TouchEventScene.h"
#include "define.h"

class GameOverScene : public cocos2d::Scene
{
private:
	LayerColor* m_layer;
	Label* m_string;
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	virtual void OnKeyPress(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	GameOverScene();
	~GameOverScene();
	CREATE_FUNC(GameOverScene);
};

