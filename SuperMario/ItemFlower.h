#pragma once
#include "MItem.h"

class ItemFlower : public MItem
{
private:

public:
	virtual void Init(Layer* layer, int index, Vec2 pos);
	virtual void Update(float ElapsedTime);
	virtual void SetHitbox();
	ItemFlower();
	~ItemFlower();
};

