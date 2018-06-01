#include "MapManager.h"
#include "MapEditor.h"
#include "TopUI.h"
#include "Piece.h"
#include "EtcUI.h"

MapManager* MapManager::m_this = NULL;

MapManager::MapManager()
{
}


void MapManager::Init(Layer * layer)
{
	m_borderon = Sprite::create("border_on.png");
	m_borderonPosition.set(16, 16);
	m_borderon->setPosition(m_borderonPosition);
	m_iWidth = 212;
	m_layer = layer;
	m_border = new Sprite*[m_iWidth];

	m_layer->addChild(m_borderon, 5);
	for (int j = 0; j < m_iWidth; j++)
	{
		m_border[j] = Sprite::create("border_vertical.png");
		m_border[j]->setAnchorPoint(Vec2(0, 0));
		m_border[j]->setPosition(Vec2(j * 32, 0));
		m_border[j]->retain();
		m_layer->addChild(m_border[j], 4);
	}
	//AddStartEndPoint(m_iWidth);
	/*for (int i = 0; i < 14; i++)
	{
		for (int j = 0; j < m_iWidth; j++)
		{
			m_border[j] = Sprite::create("border_vertical.png");
			m_border[j]->setAnchorPoint(Vec2(0, 0));
			m_border[j]->setPosition(Vec2(j * 32, 0));
			m_layer->addChild(m_border[j], 4);
			Piece* piece = new Piece();
			piece->Init(m_layer, Point((j * 32) + 16, (i * 32) + 16));
			m_vecMap.push_back(piece);
		}
	}*/
	//LoadFile(1);
}

void MapManager::SetWidthSize(int size)
{
	for (int i = 0; i < m_iWidth; i++)
	{
		m_layer->removeChild(m_border[i]);
		m_border[i]->release();
	}
	SAFE_DELETE_ARRAY(m_border);
	for (auto iter = m_vecMap.begin(); iter != m_vecMap.end();)
	{
		Piece* piece = *iter;
		piece->Release(m_layer);
		iter = m_vecMap.erase(iter);
	}
	m_vecMap.clear();
	m_iWidth = size;
	m_border = new Sprite*[m_iWidth];
	for (int j = 0; j < m_iWidth; j++)
	{
		m_border[j] = Sprite::create("border_vertical.png");
		m_border[j]->retain();
		m_border[j]->setAnchorPoint(Vec2(0, 0));
		m_border[j]->setPosition(Vec2(j * 32, 0));
		m_layer->addChild(m_border[j], 4);
	}
	//AddStartEndPoint(m_iWidth);
	/*for (int i = 0; i < 14; i++)
	{
		for (int j = 0; j < m_iWidth; j++)
		{
			m_border[j] = Sprite::create("border_vertical.png");
			m_border[j]->setAnchorPoint(Vec2(0, 0));
			m_border[j]->setPosition(Vec2(j * 32, 0));
			m_layer->addChild(m_border[j], 4);
			Piece* piece = new Piece();
			piece->Init(m_layer, Point((j * 32) + 16, (i * 32) + 16));
			m_vecMap.push_back(piece);
		}
	}*/
}

void MapManager::CheckCursorOn(Point pos)
{
	int x;
	int y;
	x = pos.x / 32;
	y = pos.y / 32;
	m_borderonPosition.set(x * 32 + 16, y * 32 + 16);
	m_borderon->setPosition(m_borderonPosition);
}

bool MapManager::ClickMouse(Point pos)
{
	Piece* piece;
	piece = CheckExist(pos);
	if (piece == NULL)
	{
		if (TopUI::GetInstance()->GetGroupIndex() == 4)
		{
			switch (EtcUI::GetInstance()->GetIndex())
			{
			case 1:
				SetStartPoint(m_borderonPosition);
				break;
			case 2:
				AddCheckPoint(m_borderonPosition);
				break;
			case 3:
				SetDestinationPoint(m_borderonPosition);
				break;
			}
		}
		else if (TopUI::GetInstance()->GetGroupIndex() != 5)
		{
			piece = new Piece();
			piece->Init(m_layer, m_borderonPosition, true);
			piece->SetPiece();
			m_vecMap.push_back(piece);
		}
	}
	else
	{
		if (TopUI::GetInstance()->GetGroupIndex() == 4)
		{
			switch (EtcUI::GetInstance()->GetIndex())
			{
			case 1:
				SetStartPoint(m_borderonPosition);
				break;
			case 2:
				AddCheckPoint(m_borderonPosition);
				break;
			case 3:
				SetDestinationPoint(m_borderonPosition);
				break;
			}
		}
		else if (TopUI::GetInstance()->GetGroupIndex() != 5)
		{
			piece->SetPiece();
		}
		else
		{
			ErasePiece(piece);
		}
	}
	/*for (auto iter = m_vecMap.begin(); iter != m_vecMap.end(); iter++)
	{
		Piece* piece = *iter;
		if (piece->CheckCursorOn(pos))
		{
			piece->SetPiece();
			return true;
		}
	}*/
	return false;
}

void MapManager::SaveFile(int stage)
{
	char mapfilename[128];
	sprintf(mapfilename, "map%d.bin", stage);
	m_fp = fopen(mapfilename, "w+b");
	if (m_fp != NULL)
	{
		/*SAVE_HEADER header = TopUI::
		fprintf(m_fp, "%s%s%s", );*/
		fprintf(m_fp, "%d\n", m_iWidth);
		for (auto iter = m_vecMap.begin(); iter != m_vecMap.end(); iter++)
		{
			Piece* piece = *iter;
			SAVE_DATA* data = piece->GetData();
			fprintf(m_fp, "%d,%d,%d,%d,%d,%d,%d\n", data->x, data->y, data->background, data->block, data->enemy, data->item, data->itemsize);
			/*SAVE_DATA data = piece->GetData();
			fprintf(m_fp, "%s%s%s%s%s%s%s\n", data.x, data.y, data.background, data.block, data.enemy, data.item, data.itemsize);*/
		}
		
	}
	fclose(m_fp);
	char etcfilename[128];
	sprintf(etcfilename, "etc%d.bin", stage);
	m_fp = fopen(etcfilename, "w+b");
	if (m_fp != NULL)
	{
		fprintf(m_fp, "%d, %d\n", (int)m_start.x, (int)m_start.y);
		fprintf(m_fp, "%d, %d\n", (int)m_destination.x, (int)m_destination.y);
		fprintf(m_fp, "%d\n", m_vecCheck.size());
		for (int i = 0; i < m_vecCheck.size(); i++)
		{

			fprintf(m_fp, "%d, %d\n", (int)m_vecCheck[i].x, (int)m_vecCheck[i].y);
		}
		
	}
	fclose(m_fp);
}

void MapManager::LoadFile(int stage)
{
	char mapfilename[128];
	sprintf(mapfilename, "map%d.bin", stage);
	m_fp = fopen(mapfilename, "r");
	if (m_fp != NULL)
	{
		int width;
		fscanf(m_fp, "%d\n", &width);
		MapEditor::GetInstance()->SetWidthSize(width);
		//SetWidthSize(m_iWidth);
		while (true)
		{
			if (feof(m_fp))
			{
				break;
			}
			int x;
			int y;
			int background;
			int block;
			int enemy;
			int item;
			int itemsize;
			fscanf(m_fp, "%d,%d,%d,%d,%d,%d,%d\n", &x, &y, &background, &block, &enemy, &item, &itemsize);
			Piece* piece = new Piece();
			piece->Init(m_layer, x, y, background, block, enemy, item, itemsize);
			m_vecMap.push_back(piece);
		}
	}
	fclose(m_fp);
}

void MapManager::Release()
{
	for (auto iter = m_vecMap.begin(); iter != m_vecMap.end();)
	{
		Piece* piece = *iter;
		piece->Release(m_layer);
		iter = m_vecMap.erase(iter);
	}
	m_vecMap.clear();
}

void MapManager::ErasePiece(Piece * erase)
{
	for (auto iter = m_vecMap.begin(); iter != m_vecMap.end(); iter++)
	{
		Piece* piece = *iter;
		if (piece == erase)
		{
			if (piece->GetModification())
			{
				piece->Release(m_layer);
				m_vecMap.erase(iter);
			}
			break;
		}
	}
}

void MapManager::AddStartEndPoint(int size)
{
	//startpoint
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			Piece* piece;
			piece = new Piece();
			piece->Init(m_layer, i, j, false);
			piece->SetPiece(GROUP_BLOCK, 1);
			m_vecMap.push_back(piece);
		}
	}
	//endpoint
	for (int i = size - 16; i < size; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			Piece* piece;
			piece = new Piece();
			piece->Init(m_layer, i, j, false);
			piece->SetPiece(GROUP_BLOCK, 1);
			m_vecMap.push_back(piece);
		}
	}
	Piece* piece;
	piece = new Piece();
	piece->Init(m_layer, size - 14, 2, false);
	piece->SetPiece(GROUP_BLOCK, 2);
	m_vecMap.push_back(piece);
	//pole
	{
		for (int i = 3; i < 12; i++)
		{
			Piece* piece;
			piece = new Piece();
			piece->Init(m_layer, size - 14, i, false);
			piece->SetPiece(GROUP_BLOCK, 11);
			m_vecMap.push_back(piece);
		}
		Piece* piece;
		piece = new Piece();
		piece->Init(m_layer, size - 14, 12, false);
		piece->SetPiece(GROUP_BLOCK, 10);
		m_vecMap.push_back(piece);
	}
	//castle
	{
		Piece* piece;
		piece = new Piece();
		piece->Init(m_layer, size - 7, 2, false);
		piece->SetPiece(GROUP_BLOCK, 12);
		m_vecMap.push_back(piece);
	}
}

Piece * MapManager::CheckExist(Point pos)
{
	for (auto iter = m_vecMap.begin(); iter != m_vecMap.end(); iter++)
	{
		Piece* piece = *iter;
		if (piece->CheckCursorOn(pos))
		{
			//piece->SetPiece();
			return piece;
		}
	}
	return NULL;
}

void MapManager::SetStartPoint(Point pos)
{
	m_start = pos;
}

void MapManager::SetDestinationPoint(Point pos)
{
	m_destination = pos;
}

void MapManager::AddCheckPoint(Point pos)
{
	m_vecCheck.push_back(pos);
}

MapManager::~MapManager()
{
}
