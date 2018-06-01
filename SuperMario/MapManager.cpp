#include "MapManager.h"
#include "BlockManager.h"
#include "EffectManager.h"
#include "PlayerManager.h"
#include "ItemManager.h"
#include "EnemyManager.h"
#include "FireManager.h"
#include "GameInfo.h"

MapManager* MapManager::m_this = NULL;

MapManager::MapManager()
{
}

void MapManager::Init(Layer * layer)
{

	m_x = 0;
	m_layer = Layer::create();
	m_layer->setAnchorPoint(Vec2(0, 0));
	m_layer->setPosition(Vec2(m_x, 0));
	layer->addChild(m_layer, 0);

	m_pBackground = Sprite::create("background_main.png");
	m_pBackground->setAnchorPoint(Vec2(0, 0));
	m_pBackground->setPosition(Vec2(0, 0));
	m_layer->addChild(m_pBackground, 0);
	
	
	/*int x;
	int y;
	fp = fopen("etc.bin", "r");
	fscanf(fp, "%d, %d\n", &x, &y);
	PlayerManager::GetInstance()->SetPlayerPosition(150,150);
	fscanf(fp, "%d, %d\n", &x, &y);
	m_destination.set(x, y);
	int size = 0;
	fscanf(fp, "%d\n", &size);
	for (int i = 0; i < size; i++)
	{
		Vec2 check;
		int x, y;
		fscanf(fp, "%d, %d\n", &x, &y);
		check.set(x, y);
		m_queueCheck.push(check);
	}
	PlayerManager::GetInstance()->SetPlayerPosition(m_queueCheck.front());
	fclose(fp);*/
}

void MapManager::MakeMap()
{
	char filename[128];
	sprintf(filename, "map%d.bin", GameInfo::GetInstance()->GetStage());
	FILE* fp = fopen(filename, "r");
	fscanf(fp, "%d", &m_iWidth);
	m_layer->setContentSize(Size(32 * m_iWidth, 32 * 14));
	m_pBackground->setContentSize(Size(32 * m_iWidth, 32 * 14));
	int i = 0;
	while (true)
	{
		if (feof(fp))
		{
			break;
		}
		int x;
		int y;
		int background;
		int enemy;
		int item;
		int block;
		int itemsize;
		fscanf(fp, "%d,%d,%d,%d,%d,%d,%d\n", &x, &y, &background, &block, &enemy, &item, &itemsize);
		i++;
		if (block != 0)
		{
			BlockManager::GetInstance()->MakeBlock(block, x, y, item, itemsize);
		}
		if (background != 0)
		{
			Sprite* spr;
			switch (background)
			{
			case 1:
				spr = Sprite::create("background_0.png");
				break;
			case 2:
				spr = Sprite::create("background_1.png");
				break;
			case 3:
				spr = Sprite::create("castle.png");
				spr->setAnchorPoint(Vec2(0.5f, 0.1f));
				break;
			}
			spr->setPosition(Vec2(x, y));
			spr->setScale(2.0f);
			m_vecBack.push_back(spr);
			m_layer->addChild(spr, 0);
		}
		if (enemy != 0)
		{
			Vec2 pos;
			pos.set(x, y);
			EnemyManager::GetInstance()->MakeEnemy(enemy, pos);
		}
	}
	fclose(fp);
}

void MapManager::MoveLeft(float ElapsedTime)
{
	if (m_x > -(32 * m_iWidth) + 600)
	{
		m_x = m_x - (300 * ElapsedTime);
		m_layer->setPosition(Vec2(m_x, 0));
	}
}

void MapManager::MoveLeft(float ElapsedTime, float speed)
{
	if (PlayerManager::GetInstance()->GetPosX() + m_x >= 224 && -m_x < (m_iWidth * 32) - 600)
	{
		m_x = m_x - (speed * ElapsedTime);
		m_layer->setPosition(Vec2(m_x, 0));
	}
}

void MapManager::MoveRight(float ElapsedTime)
{
	if (m_x < 0)
	{
		m_x = m_x + (300 * ElapsedTime);
		m_layer->setPosition(Vec2(m_x, 0));
	}
}

Vec2 MapManager::GetDesPos()
{
	return m_destination;
}

Layer * MapManager::GetLayer()
{
	return m_layer;
}

float MapManager::GetPosX()
{
	return m_layer->getPositionX();
}

void MapManager::Finish()
{
	Vec2 des = GameInfo::GetInstance()->GetDesPos();
	MoveTo* move = MoveTo::create(1.5f, Vec2(600 - (des.x + 300), 0));
	m_layer->runAction(move);
}

void MapManager::SetPos(Vec2 pos)
{
	m_x = -pos.x + 80;
	m_layer->setPositionX(m_x);
}

void MapManager::Release()
{
	for (auto iter = m_vecBack.begin(); iter != m_vecBack.end(); iter++)
	{
		Sprite* spr = *iter;
		m_layer->removeChild(spr);
		spr->release();
	}
	m_vecBack.clear();
	BlockManager::GetInstance()->Release();
	EffectManager::GetInstance()->Release();
	ItemManager::GetInstance()->Release();
	EnemyManager::GetInstance()->Release();
	FireManager::GetInstance()->Release();
}

MapManager::~MapManager()
{
}
