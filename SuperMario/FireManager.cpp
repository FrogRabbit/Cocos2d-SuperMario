#include "FireManager.h"

FireManager* FireManager::m_this = NULL;

FireManager::FireManager()
{
}


void FireManager::Init(Layer * layer)
{
	m_layer = layer;
}

void FireManager::MakeFire(PMOVE_STATE direction, Vec2 pos)
{
	if (m_vecFire.size() <= 5)
	{
		Fire* fire;
		fire = new Fire();
		fire->Init(m_layer, direction, pos.x, pos.y);
		m_vecFire.push_back(fire);
	}

	
}

void FireManager::MakeFire(PMOVE_STATE direction, int x, int y)
{
	if (m_vecFire.size() <= 5)
	{
		Fire* fire;
		fire = new Fire();
		fire->Init(m_layer, direction, x, y);
		m_vecFire.push_back(fire);
	}
}

void FireManager::Update(float ElapsedTime)
{
	for (auto iter = m_vecFire.begin(); iter != m_vecFire.end();)
	{
		Fire* fire = *iter;
		fire->Update(ElapsedTime);
		if (fire->GetAlive())
		{
			fire->Release(m_layer);
			iter = m_vecFire.erase(iter);
		}
		else
		{
			iter++;
		}
	}
}

void FireManager::Release()
{
	for (auto iter = m_vecFire.begin(); iter != m_vecFire.end();)
	{
		Fire* fire = *iter;
		fire->Release(m_layer);
		iter = m_vecFire.erase(iter);
	}
}

FireManager::~FireManager()
{
}
