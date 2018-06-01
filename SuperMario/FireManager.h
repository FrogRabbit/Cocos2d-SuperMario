#pragma once
#include "Fire.h"

class FireManager
{
private:
	Layer* m_layer;
	std::vector<Fire*> m_vecFire;
	static FireManager* m_this;
	FireManager();
public:
	static FireManager* GetInstance()
	{
		if (m_this == NULL)
		{
			m_this = new FireManager();
		}
		return m_this;
	}
	void Init(Layer* layer);
	void MakeFire(PMOVE_STATE direction, Vec2 pos);
	void MakeFire(PMOVE_STATE direction, int x, int y);
	void Update(float ElapsedTime);
	void Release();
	~FireManager();
};

