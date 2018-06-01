#pragma once
#include "define.h"
class ItemUI
{
private:
	static ItemUI* m_this;
	ui::EditBox*  m_ItemSize;
	ui::Button* m_ItemButton[ITEMSIZE];
	Sprite* m_ItemImg[ITEMSIZE];
	ui::Button* m_ApplyButton;
	int m_iGroupIndex;
	int m_iSelectIndex;
	int m_iItemSize;
	ItemUI();
public:
	static ItemUI* GetInstance()
	{
		if (m_this == NULL)
		{
			m_this = new ItemUI();
		}
		return m_this;
	}
	void Init(Layer* layer);
	void PressButton(int index);
	void SetVisibleList(bool visible);
	void PressApply();
	int GetIndex();
	int GetItemSize();
	~ItemUI();
};

