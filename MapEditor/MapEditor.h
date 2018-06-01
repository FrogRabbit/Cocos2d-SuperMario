#pragma once
#include "define.h"

class MapEditor : public LayerColor, public ScrollViewDelegate
{
private:
	static MapEditor* m_this;
	LayerColor* m_layer;
	ScrollView* m_scroll;
	Point m_pCursor;
	Sprite* m_background;
	int m_iWidthSize;
	Label* m_cursor;
	Label* m_label1;
	Label* m_label2;
	MapEditor();
public:
	static MapEditor* GetInstance()
	{
		if (m_this == NULL)
		{
			m_this = new MapEditor();
		}
		return m_this;
	}
	void Init(Layer* layer);
	void Update(float ElapsedTime);
	void SetCursor(float x, float y);
	void SetWidthSize(int size);
	void OnMouseDown();
	~MapEditor();
};

