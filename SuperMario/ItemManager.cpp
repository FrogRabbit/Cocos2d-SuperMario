#include "ItemManager.h"
#include "ItemMushRoom.h"
#include "ItemStar.h"
#include "PlayerManager.h"
#include "ItemCoin.h"
#include "ItemFlower.h"

ItemManager* ItemManager::m_this = NULL;

ItemManager::ItemManager()
{
}


void ItemManager::Init(Layer * layer)
{
	m_layer = layer;
}

void ItemManager::MakeItem(int index, Vec2 pos)
{
	switch (index)
	{
	case 1:
	case 4:
	{
		if (PlayerManager::GetInstance()->GetState() == PLAYER_STATE_SMALL)
		{
			ItemMushRoom* mush = new ItemMushRoom();
			mush->Init(m_layer, 1, pos);
			m_vecItem.push_back(mush);
		}
		else
		{		
			ItemFlower* flower = new ItemFlower();
			flower->Init(m_layer, 4, pos);
			m_vecItem.push_back(flower);
		}
		break;
	}
	case 2:
	case 3:
	{
		ItemMushRoom* mush = new ItemMushRoom();
		mush->Init(m_layer, index, pos);
		m_vecItem.push_back(mush);
		break;
	}
	case 5:
	{
		ItemStar* star = new ItemStar();
		star->Init(m_layer, index, pos);
		m_vecItem.push_back(star);
		//m_pItem->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("item_star.png"));
		break;
	}
	case 6: // block coin
	{
		ItemCoin* coin = new ItemCoin();
		coin->Init(m_layer, 1, pos);
		m_vecItem.push_back(coin);
		//m_pItem->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("item_coin0.png"));
		break;
	}
	case 7: // no block coin
	{

		//m_pItem->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("item_coin0.png"));
		break;
	}
	}
}

void ItemManager::Update(float ElapsedTime)
{
	for (auto iter = m_vecItem.begin(); iter != m_vecItem.end();)
	{
		MItem* item = *iter;
		item->Update(ElapsedTime);
		if (item->GetAlive())
		{
			item->Release(m_layer);
			iter = m_vecItem.erase(iter);
		}
		else
		{
			iter++;
		}
	}
}

int ItemManager::CheckCrash(Rect hitbox)
{
	for (auto iter = m_vecItem.begin(); iter != m_vecItem.end(); iter++)
	{
		MItem* item = *iter;
		if (item->CheckBodyCrash(hitbox))
		{
			int index = item->GetIndex();
			item->Release(m_layer);
			m_vecItem.erase(iter);
			return index;
		}
	}
	return 0;
}

void ItemManager::Release()
{
	for (auto iter = m_vecItem.begin(); iter != m_vecItem.end();)
	{
		MItem* item = *iter;
		item->Release(m_layer);
		iter = m_vecItem.erase(iter);
	}
}

ItemManager::~ItemManager()
{
}
