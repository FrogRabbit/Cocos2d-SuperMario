#pragma once
#include "MItem.h"

class ItemCoin : public MItem
{
public:
	virtual void Init(Layer* layer, int index, Vec2 pos);
	virtual void Update(float ElapsedTime);
	void Jump(Layer* layer);
	virtual void SetHitbox();
	ItemCoin();
	~ItemCoin();
};

