#include "MapEditor.h"
#include "MapManager.h"

MapEditor* MapEditor::m_this = NULL;

MapEditor::MapEditor()
{
}


void MapEditor::Init(Layer * layer)
{
	m_iWidthSize = 212;

	m_layer = LayerColor::create();
	m_layer->initWithColor(Color4B::WHITE);
	m_layer->setContentSize(Size(BLOCKWIDTH * m_iWidthSize, BLOCKWIDTH * 14));
	m_layer->setPosition(Vec2(BLOCKWIDTH * 10, BLOCKWIDTH * 7));

	
	m_background = Sprite::create("background_main.png");
	m_background->setContentSize(Size(BLOCKWIDTH * m_iWidthSize, BLOCKWIDTH * 14));
	m_background->setAnchorPoint(Vec2(0, 0));
	m_background->setPosition(Vec2(0, 0));
	m_layer->addChild(m_background, 0);
	
	m_cursor = Label::create();
	m_cursor->setPosition(850, 60);
	m_cursor->setTextColor(Color4B(0, 0, 0, 255));

	m_label1 = Label::create();
	m_label1->setPosition(850, 40);
	m_label1->setTextColor(Color4B(0, 0, 0, 255));

	m_label2 = Label::create();
	m_label2->setPosition(850, 20);
	m_label2->setTextColor(Color4B(0, 0, 0, 255));
	layer->addChild(m_label1, 1);
	layer->addChild(m_label2, 1);

	layer->addChild(m_cursor, 1);
	
	MapManager::GetInstance()->Init(m_layer);
	/*for (int j = 0; j < 14; j++)
	{
	Sprite** img = new Sprite*[m_iWidthSize];
	for (int i = 0; i < m_iWidthSize; i++)
	{
	img[i] = Sprite::create("border.png");
	img[i]->setPosition(Vec2(32 * i, 32 * j));
	img[i]->setAnchorPoint(Vec2(0, 0));
	img[i]->setScale(2.0f);
	m_layer->addChild(img[i]);
	}
	}*/
	m_scroll = ScrollView::create(Size(BLOCKWIDTH * 20, BLOCKWIDTH * 14), m_layer);
	m_scroll->retain();
	m_scroll->setAnchorPoint(Vec2(0, 0));
	m_scroll->setPosition(50, 50);
	m_scroll->setDirection(ScrollView::Direction::HORIZONTAL);
	m_scroll->setContentOffset(Point::ZERO, false);
	m_scroll->setBounceable(false);

	layer->addChild(m_scroll, 3);
}

void MapEditor::Update(float ElapsedTime)
{
	if (m_pCursor.x >= 0 - m_layer->getPositionX() && m_pCursor.x <= BLOCKWIDTH * 20 - m_layer->getPositionX() && m_pCursor.y >= 0 && m_pCursor.y <= BLOCKWIDTH * 14)
	{
		MapManager::GetInstance()->CheckCursorOn(m_pCursor);
	}
}

void MapEditor::SetCursor(float x, float y)
{
	m_pCursor.set(x - m_layer->getPositionX() - 50, y - 50);
	/*char temp[256];
	sprintf(temp, "cursor - x:%.2f y:%.2f", m_pCursor.x, m_pCursor.y);
	m_cursor->setString(temp);

	char temp1[256];
	sprintf(temp1, "layer - x:%.2f y:%.2f", m_layer->getPositionX(), m_layer->getPositionY());
	m_label1->setString(temp1);
	*/
	
	char temp2[256];
	sprintf(temp2, "pos - x:%.2f y:%.2f", m_pCursor.x, m_pCursor.y);
	m_label2->setString(temp2);

}

void MapEditor::SetWidthSize(int size)
{
	m_iWidthSize = size;
	m_background->setContentSize(Size(BLOCKWIDTH * m_iWidthSize, BLOCKWIDTH * 14));
	m_layer->setContentSize(Size(BLOCKWIDTH * m_iWidthSize, BLOCKWIDTH * 14));
	m_layer->setPositionX(0);
	MapManager::GetInstance()->SetWidthSize(size);
}

void MapEditor::OnMouseDown()
{
	if (m_pCursor.x >= 0 - m_layer->getPositionX() && m_pCursor.x <= BLOCKWIDTH * 20 - m_layer->getPositionX() && m_pCursor.y >= 0 && m_pCursor.y <= BLOCKWIDTH * 14)
	{
		MapManager::GetInstance()->ClickMouse(m_pCursor);
	}
}

MapEditor::~MapEditor()
{
}
