#pragma once
#include "define.h"
#include "BlockManager.h"
#include "UiManager.h"

class MItem
{
protected:
	MOVE_STATE m_MoveState;
	Sprite* m_pItem;
	Vec2 m_pPos;
	int m_iIndex;
	bool m_bMove;
	bool m_bBlock;
	bool m_bAlive;
	float m_fSpeed;
	float m_fJumpSpeed;
	float m_fGravityTime;
	Rect m_bodyHitbox;
	Rect m_bottomHitbox;
	Rect m_rearHitbox;
	Rect m_frontHitbox;
	Rect m_topHitbox;

public:
	virtual void Init(Layer* layer, int index, Vec2 pos);
	virtual void Update(float ElapsedTime);
	void MoveUpItem();
	void SetMove(bool move);
	virtual void SetHitbox();
	int GetIndex();
	void Jump();
	bool CheckBodyCrash(Rect hitbox);
	void Release(Layer* layer);
	bool GetAlive();

	MItem();
	~MItem();
};

