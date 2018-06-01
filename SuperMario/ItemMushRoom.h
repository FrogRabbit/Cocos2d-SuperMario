#pragma once
#include "MItem.h"

class ItemMushRoom : public MItem
{
private:

public:
	virtual void Init(Layer* layer, int index, Vec2 pos);
	virtual void Update(float ElapsedTime);
	virtual void SetHitbox();
	ItemMushRoom();
	~ItemMushRoom();
};

