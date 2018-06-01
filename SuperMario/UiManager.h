#pragma once
#include "define.h"

class UiManager
{
private:
	static UiManager* m_this;
	Layer* m_topUI;
	LayerColor* m_semiTitle;
	int m_iCoin;
	int m_iScore;
	int m_iLife;
	int m_iLeftTime;
	int m_iStage;
	float m_fTimeCheck;
	Label* m_LifeLabel;
	Label* m_coinLabel;
	Label* m_scoreLabel;
	Label* m_timeLabel;

	Label* m_stageLabel;
	UiManager();
public:
	static UiManager* GetInstance()
	{
		if (m_this == NULL)
		{
			m_this = new UiManager();
		}
		return m_this;
	}
	void Init(Layer* layer);
	void Update(float ElapsedTime);
	void AddScore(int score);
	void AddCoin();
	void SetSemiTitleVisible(bool visible);
	void DecLife();
	void IncLife();
	int GetLife();
	void ClearTime();
	void SetStage(int stage);
	~UiManager();
};

