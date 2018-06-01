#include "TouchEventScene.h"

USING_NS_CC;

cocos2d::Scene * TouchEventScene::CreateScene()
{
	return TouchEventScene::create();
}

bool TouchEventScene::Init()
{
	if (!Scene::init())
	{
		return false;
	}

#if	(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	auto listener = EventListenerMouse::create();
	listener->onMouseDown = CC_CALLBACK_1(TouchEventScene::OnMouseDown1, this);
	listener->onMouseUp = CC_CALLBACK_1(TouchEventScene::OnMouseUp1, this);
	listener->onMouseMove = CC_CALLBACK_1(TouchEventScene::OnMouseMove1, this);
	listener->onMouseScroll = CC_CALLBACK_1(TouchEventScene::OnMouseScroll1, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	auto key_listener = EventListenerKeyboard::create();
	key_listener->onKeyPressed = CC_CALLBACK_2(TouchEventScene::OnKeyPress, this);
	key_listener->onKeyReleased = CC_CALLBACK_2(TouchEventScene::OnKeyUp, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(key_listener, this);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(TouchAndEventScene::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(TouchAndEventScene::onTouchMoved, this);
	listener->onTouchCancelled = CC_CALLBACK_2(TouchAndEventScene::onTouchCancelled, this);
	listener->onTouchEnded = CC_CALLBACK_2(TouchAndEventScene::onTouchEnded, this);
#endif

	return true;
}

#if	(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
void TouchEventScene::OnMouseDown1(cocos2d::Event * event)
{
	EventMouse* e = (EventMouse*)event;
	log("%f , %f", e->getCursorX(), e->getCursorY());
}

void TouchEventScene::OnMouseUp1(cocos2d::Event * event)
{
}

void TouchEventScene::OnMouseMove1(cocos2d::Event * event)
{
}

void TouchEventScene::OnMouseScroll1(cocos2d::Event * event)
{
}

void TouchEventScene::OnKeyPress(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
	{
		log("up");
		break;
	}
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
	{
		log("down");
		break;
	}
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
	{
		log("left");
		break;
	}
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
	{
		log("right");
		break;
	}
	}
}

void TouchEventScene::OnKeyUp(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{
}


#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
bool TouchEventScene::onTouchBegan(Touch * touch, Event * unused_event)
{
	return false;
}

void TouchEventScene::onTouchMoved(Touch * touch, Event * unused_event)
{
}

void TouchEventScene::onTouchCancelled(Touch * touch, Event * unused_event)
{
}

void TouchEventScene::onTouchEnded(Touch * touch, Event * unused_event)
{
}
#endif
TouchEventScene::TouchEventScene()
{
}


TouchEventScene::~TouchEventScene()
{
}
