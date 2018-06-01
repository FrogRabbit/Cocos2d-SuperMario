#include "Enemy.h"



void Enemy::Init(Layer * layer, int index, Vec2 pos)
{
	m_bInvincible = false;
	m_fInvincible = 0;
	m_bPerfectAlive = false;
	m_bAlive = false;
	m_iIndex = index;
	m_pPos.x = pos.x;
	m_pPos.y = pos.y - 16;
	m_pEnemy = Sprite::create();
	m_pEnemy->setAnchorPoint(Vec2(0.5f, 0));
	m_pEnemy->setScale(2.0f);
	m_pEnemy->setPosition(m_pPos);
	m_bMove = false;
	m_fJumpSpeed = 0;
	m_fSpeed = 0;
	m_fGravityTime = 0;
	layer->addChild(m_pEnemy, 1);
}

void Enemy::Update(float ElapsedTime)
{
}

void Enemy::Release(Layer * layer)
{
	layer->removeChild(m_pEnemy);
}

void Enemy::PerfecdDie()
{
}

bool Enemy::CheckPerfectDie(Rect hitbox)
{
	return false;
}

bool Enemy::CheckAlive()
{
	return m_bAlive;
}

bool Enemy::CheckPAlive()
{
	return m_bPerfectAlive;
}

void Enemy::SetPerfectDie(bool alive)
{
	m_bPerfectAlive = alive;
}

void Enemy::SetHitbox()
{
}

bool Enemy::CheckDieCrash(Rect hitbox)
{
	return false;
}

bool Enemy::CheckCrashBody(Rect hitbox)
{
	return m_bodyHitbox.intersectsRect(hitbox);
}

Enemy::Enemy()
{
}


Enemy::~Enemy()
{
}
