#include "PlayerManager.h"
#include "BlockManager.h"

PlayerManager* PlayerManager::m_this = NULL;

PlayerManager::PlayerManager()
{
}


void PlayerManager::Init(Layer * layer)
{
	m_layer = layer;
	m_pPlayer = new Player();
	m_pPlayer->Init(m_layer, 32 * 3 - 16, 32 * 3 - 16);
	//m_pPlayer->Init(m_layer, 32 * 5 - 16, 32 * 5 - 16);
}

void PlayerManager::Update(float ElapsedTime)
{
	m_pPlayer->Update(ElapsedTime);
}

void PlayerManager::MoveLeft(float ElapsedTime)
{
	m_pPlayer->MoveLeft(ElapsedTime);
}

void PlayerManager::MoveRight(float ElapsedTime)
{
	
	m_pPlayer->MoveRight(ElapsedTime);
	
}

void PlayerManager::Jump(float ElapsedTime)
{
	m_pPlayer->Jump(ElapsedTime);
}

void PlayerManager::CheckJumpTime()
{
	m_pPlayer->CheckJumpTime();
}

void PlayerManager::CheckJumpTime(float ElapsedTime)
{
	m_pPlayer->CheckJumpTime(ElapsedTime);
}

Point PlayerManager::GetPos()
{
	return m_pPlayer->GetPos();
}

float PlayerManager::GetPosX()
{
	return m_pPlayer->GetPosX();
}

void PlayerManager::Stop()
{
	m_pPlayer->Stop();
}

void PlayerManager::Dash()
{
	m_pPlayer->Dash();
}

void PlayerManager::StopDash()
{
	m_pPlayer->StopDash();
}

void PlayerManager::Fire()
{
	m_pPlayer->Fire();
}

void PlayerManager::Duck()
{
	m_pPlayer->Duck();
}

void PlayerManager::Stand()
{
	m_pPlayer->Stand();
}

void PlayerManager::SetPlayerPosition(Vec2 pos)
{
	SetPlayerPosition(pos.x, pos.y);
}

void PlayerManager::SetPlayerPosition(int x, int y)
{
	m_pPlayer->SetPosition(x, y);
}

void PlayerManager::Finish(Vec2 pos)
{
	m_pPlayer->Finish(pos);
}

void PlayerManager::Die()
{
	m_pPlayer->Die();
}

void PlayerManager::Cheat()
{
	m_pPlayer->Cheat();
}

PMOVE_STATE PlayerManager::GetDirection()
{
	return m_pPlayer->GetDirection();
}

PLAYER_STATE PlayerManager::GetState()
{
	return m_pPlayer->GetState();
}

void PlayerManager::Reset()
{
	m_pPlayer->Reset();
}

PlayerManager::~PlayerManager()
{
}
