#pragma once
#include "define.h"

class EtcUI
{
private:
	static EtcUI* m_this;
	ui::Button* m_EtcButton[3];
	Sprite* m_EtcImg[3];
	int m_iGroupIndex;
	int m_iSelectIndex;
	EtcUI();
public:
	static EtcUI* GetInstance()
	{
		if (m_this == NULL)
		{
			m_this = new EtcUI();
		}
		return m_this;
	}
	void Init(Layer* layer);
	void PressButton(int index);
	void SetVisibleList(bool visible);
	int GetIndex();
	~EtcUI();	
};

