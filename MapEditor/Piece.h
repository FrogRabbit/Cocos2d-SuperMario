#pragma once
#include "define.h"

class Piece
{
private:
	Sprite* m_pBack;
	Sprite* m_pItem;
	Sprite* m_pMulti;
	int m_iBack;
	int m_iBlock;
	int m_iItem;
	int m_iEnemy;
	int m_iItemSize;
	Label* m_pItemSize;
	POINT m_iPos;
	Point m_fPos;
	Rect m_hitbox;
	Layer* m_layer;
	bool m_modification;
public:
	void Init(Layer* layer, Point pos, bool modification);
	void Init(Layer* layer, int x, int y, bool modification);
	void Init(Layer* layer, int x, int y, int background, int block, int enemy, int item, int itemsize);
	void Release(Layer* layer);
	bool CheckCursorOn(Point pos);
	SAVE_DATA* GetData();
	void SetPiece();
	void SetPiece(GROUPINDEX gindex, int index);
	bool GetModification();
	void SetBackground(int index);
	void SetBlock(int index);
	void SetEnemy(int index);
	void SetItem(int index);
	Piece();
	~Piece();
};

