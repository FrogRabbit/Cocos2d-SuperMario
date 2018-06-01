#pragma once
#include "cocos2d.h"
#include "define.h"

USING_NS_CC;



class Player
{
private:
	Sprite* m_pSpr;
	Vec2 m_pPos;
	bool m_bOnGround;
	bool m_bDash;
	bool m_bJump;
	bool m_bDestroy;
	bool m_bDuck;
	bool m_bChange;
	bool m_bDown;
	bool m_bFire;
	bool m_bStar;
	bool m_bRun;
	bool m_bFinish;
	bool m_bDie;
	int m_iStarCount;
	int m_iRunCount;
	float m_fDieTime;
	float m_fRunTime;
	float m_fRunCountTime;
	float m_fStarCountTime;
	float m_fStarTime;
	float m_fCheckJumpTime;
	float m_fGravityTime;
	float m_fJumpSpeed;
	float m_fLeftSpeed;
	float m_fRightSpeed;
	float m_fLeftAccel;
	float m_fRightAccel;
	Rect m_hitbox;
	Rect m_frontHitbox;
	Rect m_rearHitbox;
	Rect m_topHitbox;
	Rect m_bottomHitbox;
	PMOVE_STATE m_pmoveState;
	PMOVE_STATE m_curMoveState;
	PLAYER_STATE m_pState;
	PLAYER_STATE m_pOldState;
	RepeatForever* m_pSRunAction;
	RepeatForever* m_pBRunAction;
	RepeatForever* m_pFRunAction;

	Animate* m_pStoBAction;
	Animate* m_pBtoFAction;
	Animate* m_pStoFAction;

	Action* m_pCurAction;
	bool m_bAction;
	bool m_bCheckJump;
	float m_fLeftMaxSpeed;
	float m_fRightMaxSpeed;
public:
	void Init(Layer* layer, int x, int y);
	void Update(float ElapsedTime);
	void MoveLeft(float ElapsedTime);
	void MoveRight(float ElapsedTime);
	void CheckJumpTime(float ElapsedTime);
	void Jump(float jumptime);
	void Run();
	void Stop();
	void Dash();
	void Duck();
	void Stand();
	void StopDash();
	void ChangeDuckSprite();
	void ChangeStandSprite();
	void ChangeJumpSprite();
	void ChangeRunSprite();
	void ChangeDashSprite();
	void SetHitbox();
	Rect GetHitbox(int index);
	void CheckJumpTime();
	Point GetPos();
	float GetPosX();
	RepeatForever* hang;
	RepeatForever* walk;
	void SetChange(bool change);
	void SetbAction(bool action);
	void RunAction(Action* action);
	void RunSeq(Sequence* seq);
	PMOVE_STATE GetMState();
	PMOVE_STATE GetDirection();
	PLAYER_STATE GetState();
	void ChangePlayer(PLAYER_STATE state);
	void Die(bool check);
	void Die();
	void Upgrade();
	void Downgrade();
	void Fire();
	void SetPosition(int x, int y);
	void Finish(Vec2 pos);
	void ChangeHangSprite();
	bool GetDestroy();
	void FlipX(bool flip);
	void StopAction(Action* action);
	void RunFinishAction(Action* action);
	void SetVisible(bool visible);
	void Reset();
	void ResetAll();
	void ChangeScene(int index);
	void CheckFinish();
	void Cheat();
	Player();
	~Player();
};

