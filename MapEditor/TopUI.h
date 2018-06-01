#pragma once
#include "define.h"

class TopUI
{
private:
	int m_iGroupIndex;
	static TopUI* m_this;
	ui::EditBox* m_WidthBox;
	ui::EditBox* m_LifeBox;
	ui::EditBox* m_TimeBox;

	ui::Button* m_StageButton[2];

	ui::Button* m_ApplyButton;
	ui::Button* m_menuButton[6];
	ui::Button* m_SaveButton;
	ui::Button* m_ClearButton;

	int m_iStage;
	TopUI();
public:
	static TopUI* GetInstance()
	{
		if (m_this == NULL)
		{
			m_this = new TopUI();
		}
		return m_this;
	}
	void Init(Layer* layer);
	void PressMenuButton(int index);
	void PressApply();
	int GetGroupIndex();
	void sliderEvent();
	void SaveFile();
	void Clear();
	void ChangeStage(int stage);
	SAVE_HEADER GetData();
	~TopUI();
};

