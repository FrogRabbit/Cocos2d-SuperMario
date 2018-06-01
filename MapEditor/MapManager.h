#pragma once
#include "define.h"

class Piece;
class MapManager
{
private:
	Point m_start;
	Point m_destination;
	std::vector <Point> m_vecCheck;
	static MapManager* m_this;
	std::vector<Piece*> m_vecMap;
	Sprite* m_borderon;
	Vec2 m_borderonPosition;
	Sprite** m_border;
	Layer* m_layer;
	int m_iWidth;
	FILE* m_fp;
	MapManager();
public:
	static MapManager* GetInstance()
	{
		if (m_this == NULL)
		{
			m_this = new MapManager();
		}
		return m_this;
	}
	void Init(Layer* layer);
	void SetWidthSize(int size);
	void CheckCursorOn(Point pos);
	bool ClickMouse(Point pos);
	void SaveFile(int stage);
	void LoadFile(int index);
	void Release();
	void ErasePiece(Piece* erase);
	void AddStartEndPoint(int size);
	//void CreatePiece();
	Piece* CheckExist(Point pos);
	void SetStartPoint(Point pos);
	void SetDestinationPoint(Point pos);
	void AddCheckPoint(Point pos);
	~MapManager();
};

