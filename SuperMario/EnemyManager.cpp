#include "EnemyManager.h"
#include "EnemyMush.h"
#include "EnemyTurtle.h"

EnemyManager* EnemyManager::m_this = NULL;

EnemyManager::EnemyManager()
{
}


void EnemyManager::Init(Layer * layer)
{
	m_layer = layer;
}

void EnemyManager::MakeEnemy(int index, Vec2 pos)
{
	switch (index)
	{
	case 1:
	{
		EnemyMush* enemy = new EnemyMush();
		enemy->Init(m_layer, index, pos);
		m_vecEnemy.push_back(enemy);
		break;
	}
	case 2:
	case 3:
	{
		EnemyTurtle* enemy = new EnemyTurtle();
		enemy->Init(m_layer, index, pos);
		m_vecEnemy.push_back(enemy);
		break;
	}
	case 4:
	{
		break;
	}
	}
}

void EnemyManager::Update(float ElapsedTime)
{
	/*for (auto iter = m_vecEnemy.begin(); iter != m_vecEnemy.end();)
	{
		Enemy* enemy = *iter;
		enemy->Update(ElapsedTime);
		if (enemy->CheckAlive())
		{
			enemy->Release(m_layer);
			iter = m_vecEnemy.erase(iter);
		}
		else
		{
			iter++;
		}
	}*/
	for (auto iter = m_vecEnemy.begin(); iter != m_vecEnemy.end();iter++)
	{
		Enemy* enemy = *iter;
		enemy->Update(ElapsedTime);	
	}
	for (auto iter = m_vecEnemy.begin(); iter != m_vecEnemy.end();)
	{
		Enemy* enemy = *iter;
		if (enemy->CheckPAlive())
		{
			enemy->PerfecdDie();
			enemy->Release(m_layer);
			iter = m_vecEnemy.erase(iter);
		}
		else if (enemy->CheckAlive())
		{
			enemy->Release(m_layer);
			iter = m_vecEnemy.erase(iter);
		}
		else
		{
			iter++;
		}

	}
}

bool EnemyManager::CheckCrashBody(Rect hitbox)
{
	bool check = false;
	for (auto iter = m_vecEnemy.begin(); iter != m_vecEnemy.end(); iter++)
	{
		Enemy* enemy = *iter;
		if (enemy->CheckCrashBody(hitbox))
		{
			check = true;
		}
	}
	return check;
}

bool EnemyManager::CheckCrash(Rect hitbox)
{
	for (auto iter = m_vecEnemy.begin(); iter != m_vecEnemy.end(); iter++)
	{
		Enemy* enemy = *iter;
		if (enemy->CheckCrashBody(hitbox))
		{
			enemy->Release(m_layer);
			m_vecEnemy.erase(iter);
			return true;
		}
		
	}
	return false;
}

bool EnemyManager::CheckDieCrash(Rect hitbox)
{
	bool check = false;
	for (auto iter = m_vecEnemy.begin(); iter != m_vecEnemy.end(); iter++)
	{
		Enemy* enemy = *iter;
		if (enemy->CheckDieCrash(hitbox))
		{
			check =  true;
		}

	}
	return check;
}

bool EnemyManager::CheckPerfectDie(Rect hitbox)
{
	for (auto iter = m_vecEnemy.begin(); iter != m_vecEnemy.end(); iter++)
	{
		Enemy* enemy = *iter;
		if (enemy->CheckPerfectDie(hitbox))
		{
			enemy->Release(m_layer);
			m_vecEnemy.erase(iter);
			return true;
		}
	}
	return false;
}

bool EnemyManager::CheckPerfectDie(Enemy * turtle, Rect hitbox)
{
	for (auto iter = m_vecEnemy.begin(); iter != m_vecEnemy.end(); iter++)
	{
		Enemy* enemy = *iter;

		if (enemy != turtle)
		{
			if (enemy->CheckPerfectDie(hitbox))
			{
				enemy->SetPerfectDie(true);
				return true;
			}
		}
	}
	return false;
}

void EnemyManager::Release()
{
	for (auto iter = m_vecEnemy.begin(); iter != m_vecEnemy.end(); )
	{
		Enemy* enemy = *iter;
		enemy->Release(m_layer);
		iter = m_vecEnemy.erase(iter);
	}
}



EnemyManager::~EnemyManager()
{
}
