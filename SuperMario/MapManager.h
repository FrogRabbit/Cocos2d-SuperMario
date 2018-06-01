#pragma once
#include "cocos2d.h"
#include "define.h"

USING_NS_CC;

class MapManager
{
private:
	Layer* m_sceneLayer;
	float m_x;
	int m_iWidth;
	static MapManager* m_this;
	Sprite* m_pBackground;
	std::vector <Sprite*> m_vecBack;
	std::queue <Vec2> m_queueCheck;
	Point m_destination;
	Layer* m_layer;
	MapManager();
public:
	static MapManager* GetInstance()
	{
		if (m_this == NULL)
		{
			m_this = new MapManager();
		}
		return m_this;
	}
	void Init(Layer* layer);
	void MakeMap();
	void MoveLeft(float ElapsedTime);
	void MoveLeft(float ElapsedTime, float speed);
	void MoveRight(float ElapsedTime);
	Vec2 GetDesPos();
	Layer* GetLayer();
	float GetPosX();
	void Finish();
	void SetPos(Vec2 pos);
	void Release();
	~MapManager();
};

