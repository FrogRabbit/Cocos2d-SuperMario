#pragma once
#include "define.h"
#include "MItem.h"

class ItemManager
{
private:
	static ItemManager* m_this;
	Layer* m_layer;
	std::vector<MItem*> m_vecItem;
	ItemManager();
public:
	static ItemManager* GetInstance()
	{
		if (m_this == NULL)
		{
			m_this = new ItemManager();
		}
		return m_this;
	}
	void Init(Layer* layer);
	void MakeItem(int index, Vec2 pos);
	void Update(float ElapsedTime);
	int CheckCrash(Rect hitbox);
	void Release();
	
	~ItemManager();
};

