#pragma once
#include "MItem.h"

class ItemStar : public MItem
{
public:
	virtual void Init(Layer* layer, int index, Vec2 pos);
	virtual void Update(float ElapsedTime);
	virtual void SetHitbox();
	ItemStar();
	~ItemStar();
};

