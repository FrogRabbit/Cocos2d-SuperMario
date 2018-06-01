#include "GameInfo.h"
#include "MapManager.h"
#include "EffectManager.h"
#include "BlockManager.h"
#include "PlayerManager.h"
#include "ItemManager.h"
#include "EnemyManager.h"
#include "FireManager.h"
#include "UiManager.h"

GameInfo* GameInfo::m_this = NULL;

GameInfo::GameInfo()
{
}


void GameInfo::Init()
{
	m_bChangeStage = false;
	m_state = GAME_STATE_SEMITITLE;
	m_fTitleTime = 0;
	m_iStage = 1;
	int x;
	int y;
	char filename[128];
	sprintf(filename, "etc%d.bin", m_iStage);
	FILE* fp = fopen(filename, "r");
	fscanf(fp, "%d, %d\n", &x, &y);
	m_pCurCheckPoint.set(x, y);
	PlayerManager::GetInstance()->SetPlayerPosition(m_pCurCheckPoint);
	fscanf(fp, "%d, %d\n", &x, &y);
	m_pDesPoint.set(x, y);
	int size = 0;
	fscanf(fp, "%d\n", &size);
	for (int i = 0; i < size; i++)
	{
		Vec2 check;
		int x, y;
		fscanf(fp, "%d, %d\n", &x, &y);
		check.set(x, y);
		m_queueCheckPoint.push(check);
	}
	fclose(fp);
}

void GameInfo::Update(float ElapsedTime)
{
	switch (m_state)
	{
	case GAME_STATE_PLAY:
	{
		PlayerManager::GetInstance()->Update(ElapsedTime);
		BlockManager::GetInstance()->Update(ElapsedTime);
		ItemManager::GetInstance()->Update(ElapsedTime);
		EnemyManager::GetInstance()->Update(ElapsedTime);
		EffectManager::GetInstance()->Update(ElapsedTime);
		FireManager::GetInstance()->Update(ElapsedTime);
		UiManager::GetInstance()->Update(ElapsedTime);
		UiManager::GetInstance()->SetSemiTitleVisible(false);
		break;
	}
	case GAME_STATE_SEMITITLE:
	{
		UiManager::GetInstance()->SetSemiTitleVisible(true);
		m_fTitleTime += ElapsedTime;
		if (m_fTitleTime >= 2.0f)
		{
			m_fTitleTime = 0;
			m_state = GAME_STATE_PLAY;
			SetPosition();
		}
		break;
	}
	}
	if (m_queueCheckPoint.size() > 0)
	{
		float x = PlayerManager::GetInstance()->GetPosX();
		Vec2 check = m_queueCheckPoint.front();
		if (x > check.x)
		{
			m_pCurCheckPoint = m_queueCheckPoint.front();
			m_queueCheckPoint.pop();
		}
	}
}

void GameInfo::SetState(GAME_STATE state)
{
	m_state = state;
}

void GameInfo::SetPosition()
{
	PlayerManager::GetInstance()->Reset();
	MapManager::GetInstance()->Release();
	MapManager::GetInstance()->MakeMap();
	PlayerManager::GetInstance()->SetPlayerPosition(m_pCurCheckPoint);
	//if (!m_bChangeStage)
	{
		MapManager::GetInstance()->SetPos(m_pCurCheckPoint);
	}
	/*else
	{
		MapManager::GetInstance()->SetPos(Vec2(0,0));
		m_bChangeStage = false;
	}*/
}

Vec2 GameInfo::GetDesPos()
{
	return m_pDesPoint;
}

int GameInfo::GetStage()
{
	return m_iStage;
}

void GameInfo::SetStage(int stage)
{
	while (!m_queueCheckPoint.empty())
	{
		m_queueCheckPoint.pop();
	}
	m_iStage = stage;
	char filename[128];
	sprintf(filename, "etc%d.bin", m_iStage);
	int x, y;
	FILE* fp = fopen(filename, "r");
	fscanf(fp, "%d, %d\n", &x, &y);
	m_pCurCheckPoint.set(x, y);
	PlayerManager::GetInstance()->SetPlayerPosition(m_pCurCheckPoint);
	fscanf(fp, "%d, %d\n", &x, &y);
	m_pDesPoint.set(x, y);
	int size = 0;
	fscanf(fp, "%d\n", &size);
	for (int i = 0; i < size; i++)
	{
		Vec2 check;
		int x, y;
		fscanf(fp, "%d, %d\n", &x, &y);
		check.set(x, y);
		m_queueCheckPoint.push(check);
	}
	MapManager::GetInstance()->SetPos(Vec2(0, 0));
	UiManager::GetInstance()->SetStage(m_iStage);
	UiManager::GetInstance()->ClearTime();
	m_bChangeStage = true;
	fclose(fp);

}

GameInfo::~GameInfo()
{
}
