#include "BlockManager.h"

BlockManager* BlockManager::m_this = NULL;

BlockManager::BlockManager()
{
}


void BlockManager::Init(Layer * layer)
{
	m_layer = layer;
}

void BlockManager::MakeBlock(int index, int x ,int y, int item, int itemsize)
{
	MapBlock* block = new MapBlock();
	block->Init(m_layer, index, x, y, item, itemsize);
	m_vecBlock.push_back(block);
}

void BlockManager::Update(float ElapsedTime)
{
	for (auto iter = m_vecBlock.begin(); iter != m_vecBlock.end();)
	{
		MapBlock* block = *iter;
		if (block->CheckAlive())
		{
			block->Release(m_layer);
			CC_SAFE_DELETE(block);
			iter = m_vecBlock.erase(iter);
		}
		else
		{
			iter++;
		}
		
	}
}

bool BlockManager::CheckTopCrash(Rect hitbox)
{
	for (auto iter = m_vecBlock.begin(); iter != m_vecBlock.end(); iter++)
	{
		MapBlock* block = *iter;
		if (block->CheckOnGround(hitbox))
		{
			block->TopCrash();
			return true;
		}
	}
	return false;
}

bool BlockManager::CheckOnGround(Rect hitbox)
{
	for (auto iter = m_vecBlock.begin(); iter != m_vecBlock.end(); iter++)
	{
		MapBlock* block = *iter;
		if (block->CheckOnGround(hitbox))
		{
			return true;
		}
	}
	return false;
}

bool BlockManager::CheckMoveCrash(Rect fhitbox, Rect rhitbox)
{
	for (auto iter = m_vecBlock.begin(); iter != m_vecBlock.end(); iter++)
	{
		MapBlock* block = *iter;
		if (block->CheckOnGround(fhitbox))
		{
			return true;
		}
		if (block->CheckOnGround(rhitbox))
		{
			return true;
		}
	}
	return false;
}

bool BlockManager::CheckFinish(Rect hitbox)
{
	for (auto iter = m_vecBlock.begin(); iter != m_vecBlock.end(); iter++)
	{
		MapBlock* block = *iter;
		if (block->CheckFinish(hitbox))
		{
			return true;
		}
		
	}
	return false;
}

Point BlockManager::GetBlockPos(Rect hitbox)
{
	for (auto iter = m_vecBlock.begin(); iter != m_vecBlock.end(); iter++)
	{
		MapBlock* block = *iter;
		if (block->CheckOnGround(hitbox))
		{
			return block->GetPos();
		}
	}
}

void BlockManager::Release()
{
	for (auto iter = m_vecBlock.begin(); iter != m_vecBlock.end();)
	{
		MapBlock* block = *iter;
		block->Release(m_layer);
		iter = m_vecBlock.erase(iter);
	}
}

BlockManager::~BlockManager()
{
}
