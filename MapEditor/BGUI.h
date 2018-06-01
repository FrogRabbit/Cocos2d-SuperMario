#pragma once
#include "define.h"
class BGUI
{
private:
	static BGUI* m_this;
	ui::Button* m_backgroundButton[BACKGROUNDSIZE];
	Sprite* m_BackImg[BACKGROUNDSIZE];
	int m_iGroupIndex;
	int m_iSelectIndex;
	BGUI();
public:
	static BGUI* GetInstance()
	{
		if (m_this == NULL)
		{
			m_this = new BGUI();
		}
		return m_this;
	}
	void Init(Layer* layer);
	void PressButton(int index);
	void SetVisibleList(bool visible);
	int GetIndex();
	~BGUI();
};

