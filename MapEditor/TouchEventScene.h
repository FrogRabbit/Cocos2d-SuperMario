#pragma once
#ifndef __TOUCHEVENT_SCENE_H__
#define __TOUCHEVENT_SCENE_H__

#include "cocos2d.h"


USING_NS_CC;

class TouchEventScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* CreateScene();

	virtual bool Init();

#if	(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	virtual void OnMouseDown1(cocos2d::Event* event);
	virtual void OnMouseUp1(cocos2d::Event* event);
	virtual void OnMouseMove1(cocos2d::Event* event);
	virtual void OnMouseScroll1(cocos2d::Event* event);

	virtual void OnKeyPress(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	virtual void OnKeyUp(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	virtual bool onTouchBegan(Touch* touch, Event* unused_event);
	virtual void onTouchMoved(Touch* touch, Event* unused_event);
	virtual void onTouchCancelled(Touch* touch, Event* unused_event);
	virtual void onTouchEnded(Touch* touch, Event *unused_event);
#endif

	CREATE_FUNC(TouchEventScene);
	TouchEventScene();
	~TouchEventScene();
};
#endif
