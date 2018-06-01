#pragma once
#include "cocos2d.h"
#include "define.h"

USING_NS_CC;

class MapBlock
{
private:
	bool m_bAlive;
	bool m_bItem;
	int m_iIndex;
	int m_iItemIndex;
	int m_iItemSize;
	bool m_bMoveUp;
	bool m_bBreak;
	bool m_bAction;
	Rect m_hitbox;
	Sprite* m_pBlock;
	Sprite* m_pFlag;
	RepeatForever* m_pRepeat;
public:
	void Init(Layer* layer, int index, int x, int y, int item, int itemsize);
	void Break();
	void MoveUp();
	void MakeItem();
	void ChangeBlock();
	bool CheckOnGround(Rect hitbox);
	void TopCrash();
	void SetbAction(bool action);
	bool CheckAlive();
	void Release(Layer* layer);
	Point GetPos();
	bool CheckFinish(Rect hitbox);
	MapBlock();
	~MapBlock();
};

