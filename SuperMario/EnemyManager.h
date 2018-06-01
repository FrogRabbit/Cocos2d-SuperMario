#pragma once
#include "Enemy.h"

class EnemyTurtle;
class EnemyManager
{
private:
	static EnemyManager* m_this;
	Layer* m_layer;
	std::vector <Enemy*> m_vecEnemy;
	EnemyManager();
public:
	static EnemyManager* GetInstance()
	{
		if (m_this == NULL)
		{
			m_this = new EnemyManager();
		}
		return m_this;
	}
	void Init(Layer* layer);
	void MakeEnemy(int index, Vec2 pos);
	void Update(float ElapsedTime);
	bool CheckCrashBody(Rect hitbox);
	bool CheckCrash(Rect hitbox);
	bool CheckDieCrash(Rect hitbox);
	bool CheckPerfectDie(Rect hitbox);
	bool CheckPerfectDie(Enemy* turtle, Rect hitbox);
	void Release();
	~EnemyManager();
};

