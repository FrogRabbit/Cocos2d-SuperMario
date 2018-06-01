#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "TouchEventScene.h"
#include "define.h"



class TitleScene : public cocos2d::Scene
{
private:
	Sprite* m_background;
	Sprite* m_title;
	Label* m_Label;
	Label* m_interface;
	
public:
	static cocos2d::Scene* createScene();
	virtual bool init();

	// a selector callback

	void Update(float ElapsedTime);

	void ChangeScene();


	virtual void OnKeyPress(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	virtual void OnKeyUp(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

	// implement the "static create()" method manually
	CREATE_FUNC(TitleScene);
};

#endif // __HELLOWORLD_SCENE_H__
