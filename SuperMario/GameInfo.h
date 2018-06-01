#pragma once
#include "define.h"

class GameInfo
{
private:
	Layer* m_layer;
	static GameInfo* m_this;
	float m_fTitleTime;
	GAME_STATE m_state;
	bool m_bChangeStage;
	Vec2 m_pDesPoint;
	Vec2 m_pStartPoint;
	std::queue<Vec2> m_queueCheckPoint;
	int m_iStage;
	Vec2 m_pCurCheckPoint;
	GameInfo();
public:
	static GameInfo* GetInstance()
	{
		if (m_this == NULL)
		{
			m_this = new GameInfo();
		}
		return m_this;
	}
	void Init();
	void Update(float ElapsedTime);
	void SetState(GAME_STATE state);
	void SetPosition();
	Vec2 GetDesPos();
	int GetStage();
	void SetStage(int stage);
	~GameInfo();
};

