#pragma once
#include "cocos2d.h"
#include "MapBlock.h"

class BlockManager
{
private:
	Layer* m_layer;
	static BlockManager* m_this;
	std::vector <MapBlock*> m_vecBlock;
	float a = 0;
	BlockManager();
public:
	static BlockManager* GetInstance()
	{
		if (m_this == NULL)
		{
			m_this = new BlockManager();
		}
		return m_this;
	}
	void Init(Layer* layer);
	void MakeBlock(int index, int x, int y, int item, int itemsize);
	void Update(float ElapsedTime);
	bool CheckTopCrash(Rect hitbox);
	bool CheckOnGround(Rect hitbox);
	bool CheckMoveCrash(Rect fhitbox, Rect rhitbox);
	bool CheckFinish(Rect hitbox);
	Point GetBlockPos(Rect hitbox);
	void Release();
	~BlockManager();
};

