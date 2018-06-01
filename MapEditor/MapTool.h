#pragma once
#include "cocos2d.h"
#include "define.h"

USING_NS_CC;

class MapTool : public cocos2d::LayerColor
{
private:
	
	ui::Button* m_blockButton[BLOCKSIZE];
	Sprite* m_blockImg[BLOCKSIZE];
	ui::Button* m_itemButton[ITEMSIZE];
	Sprite* m_itemImg[ITEMSIZE];
	ui::Button* m_enemyButton[ENEMYSIZE];
	Sprite* m_enemyImg[ENEMYSIZE];
	ui::EditBox* m_itemSize;
	bool m_mouseDown;
	float m_clickTime;
	


public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	void menuCloseCallback(cocos2d::Ref* pSender);

	virtual void OnMouseMove1(cocos2d::Event* event);
	virtual void OnMouseUp1(cocos2d::Event* event);
	virtual void OnMouseDown1(cocos2d::Event* event);
	virtual void OnKeyPress(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	virtual void OnKeyUp(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	
	void PressBlockButton(int index);
	void PressBackgroundButton(int index);
	void PressItemButton(int index);
	void PressEnemyButton(int index);
	void Update(float ElapsedTime);

	CREATE_FUNC(MapTool);
};

