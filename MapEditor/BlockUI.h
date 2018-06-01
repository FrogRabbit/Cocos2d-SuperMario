#pragma once
#include "define.h"

class BlockUI
{
private:
	static BlockUI* m_this;
	ui::Button* m_BlockButton[BLOCKSIZE];
	Sprite* m_BlockImg[BLOCKSIZE];
	int m_iGroupIndex;
	int m_iSelectIndex;
	BlockUI();
public:
	static BlockUI* GetInstance()
	{
		if (m_this == NULL)
		{
			m_this = new BlockUI();
		}
		return m_this;
	}
	void Init(Layer* layer);
	void PressButton(int index);
	void SetVisibleList(bool visible);
	int GetIndex();
	~BlockUI();
};

