#pragma once
#include "Player.h"

class PlayerManager
{
private:
	static PlayerManager* m_this;
	Player* m_pPlayer;
	Layer* m_layer;
	PlayerManager();
public:
	static PlayerManager* GetInstance()
	{
		if (m_this == NULL)
		{
			m_this = new PlayerManager();
		}
		return m_this;
	}
	void Init(Layer* layer);
	void Update(float ElapsedTime);
	void MoveLeft(float ElapsedTime);
	void MoveRight(float ElapsedTime);
	void Jump(float ElapsedTime);
	void CheckJumpTime();
	void CheckJumpTime(float ElapsedTime);
	Point GetPos();
	float GetPosX();
	void Stop();
	void Dash();
	void StopDash();
	void Fire();
	void Duck();
	void Stand();
	void SetPlayerPosition(Vec2 pos);
	void SetPlayerPosition(int x, int y);
	void Finish(Vec2 pos);
	void Die();
	void Cheat();
	PMOVE_STATE GetDirection();
	PLAYER_STATE GetState();
	void Reset();
	~PlayerManager();
};

