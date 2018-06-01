#pragma once
#include "define.h"

class EnemyUI
{
private:
	static EnemyUI* m_this;
	ui::Button* m_EnemyButton[ENEMYSIZE];
	Sprite* m_EnemyImg[ENEMYSIZE];
	int m_iGroupIndex;
	int m_iSelectIndex;
	EnemyUI();
public:
	static EnemyUI* GetInstance()
	{
		if (m_this == NULL)
		{
			m_this = new EnemyUI();
		}
		return m_this;
	}
	void Init(Layer* layer);
	void PressButton(int index);
	void SetVisibleList(bool visible);
	int GetIndex();
	~EnemyUI();
};

