#include "Piece.h"
#include "TopUI.h"
#include "ItemUI.h"
#include "BGUI.h"
#include "BlockUI.h"
#include "EnemyUI.h"


void Piece::Init(Layer * layer, Point pos, bool modifcation)
{
	m_modification = modifcation;
	m_layer = layer;
	m_fPos = pos;
	m_iPos.x = (m_fPos.x - 16) / 32;
	m_iPos.y = (m_fPos.y - 16) / 32;
	//m_pButton = Sprite::create("border.png");
	m_pBack = Sprite::create();
	m_pItem = Sprite::create();
	m_pMulti = Sprite::create(); 

	m_iBack = 0;
	m_iBlock = 0;
	m_iItem = 0;
	m_iEnemy = 0;
	m_iItemSize = 0;
	m_hitbox.setRect(m_fPos.x - 16, m_fPos.y - 16, 32, 32);
	
	m_pItemSize = Label::create();
	m_pItemSize->setPosition(m_fPos);
	m_pItemSize->setSystemFontSize(22);
	m_pItemSize->setTextColor(Color4B::RED);
	
	m_pBack->setPosition(m_fPos);
	m_pItem->setPosition(m_fPos);
	m_pMulti->setPosition(m_fPos);
	//m_pButton->setPosition(m_pos);
	m_pBack->setScale(2.0f);
	m_pItem->setScale(2.0f);
	m_pMulti->setScale(2.0f);
	//m_pButton->setScale(2.0f);

	layer->addChild(m_pItemSize, 3);
	layer->addChild(m_pBack, 0);
	layer->addChild(m_pMulti, 1);
	layer->addChild(m_pItem, 2);
	//layer->addChild(m_pButton, 3);
}

void Piece::Init(Layer * layer, int x, int y, bool modification)
{
	m_modification = modification;
	m_layer = layer;
	m_iPos.x = x;
	m_iPos.y = y;
	m_fPos.set((x * 32) + 16, (y * 32) + 16);
	//m_pButton = Sprite::create("border.png");
	m_pBack = Sprite::create();
	m_pItem = Sprite::create();
	m_pMulti = Sprite::create();

	m_iBack = 0;
	m_iBlock = 0;
	m_iItem = 0;
	m_iEnemy = 0;
	m_iItemSize = 0;
	m_hitbox.setRect(m_fPos.x - 16, m_fPos.y - 16, 32, 32);

	m_pItemSize = Label::create();
	m_pItemSize->setPosition(m_fPos);
	m_pItemSize->setSystemFontSize(22);
	m_pItemSize->setTextColor(Color4B::RED);

	m_pBack->setPosition(m_fPos);
	m_pItem->setPosition(m_fPos);
	m_pMulti->setPosition(m_fPos);
	//m_pButton->setPosition(m_pos);
	m_pBack->setScale(2.0f);
	m_pItem->setScale(2.0f);
	m_pMulti->setScale(2.0f);
	//m_pButton->setScale(2.0f);

	layer->addChild(m_pItemSize, 3);
	layer->addChild(m_pBack, 0);
	layer->addChild(m_pMulti, 1);
	layer->addChild(m_pItem, 2);
	//layer->addChild(m_pButton, 3);
}

void Piece::Init(Layer * layer, int x, int y, int background, int block, int enemy, int item, int itemsize)
{
	m_modification = true;
	m_layer = layer;
	m_iPos.x = x;
	m_iPos.y = y;
	m_fPos.set(x, y);
	//m_pButton = Sprite::create("border.png");
	m_pBack = Sprite::create();
	m_pItem = Sprite::create();
	m_pMulti = Sprite::create();

	m_iBack = background;
	m_iBlock = block;
	m_iItem = item;
	m_iEnemy = enemy;
	m_iItemSize = itemsize;
	m_hitbox.setRect(m_fPos.x - 16, m_fPos.y - 16, 32, 32);

	m_pItemSize = Label::create();
	m_pItemSize->setPosition(m_fPos);
	m_pItemSize->setSystemFontSize(22);
	m_pItemSize->setTextColor(Color4B::RED);

	m_pBack->setPosition(m_fPos);
	m_pItem->setPosition(m_fPos);
	m_pMulti->setPosition(m_fPos);
	//m_pButton->setPosition(m_pos);
	m_pBack->setScale(2.0f);
	m_pItem->setScale(2.0f);
	m_pMulti->setScale(2.0f);
	//m_pButton->setScale(2.0f);
	SetBackground(m_iBack);
	SetEnemy(m_iEnemy);
	SetItem(m_iItem);
	SetBlock(m_iBlock);

	layer->addChild(m_pItemSize, 3);
	layer->addChild(m_pBack, 0);
	layer->addChild(m_pMulti, 1);
	layer->addChild(m_pItem, 2);

	
}

void Piece::Release(Layer * layer)
{
	layer->removeChild(m_pBack);
	layer->removeChild(m_pMulti);
	layer->removeChild(m_pItem);
	layer->removeChild(m_pItemSize);
	/*m_pBack->release();
	m_pItem->release();
	m_pMulti->release();*/
}

bool Piece::CheckCursorOn(Point pos)
{
	if (m_hitbox.containsPoint(pos))
	{
		return true;
	}
	return false;
}

SAVE_DATA* Piece::GetData()
{
	SAVE_DATA data;
	data.x = (int)m_fPos.x;
	data.y = (int)m_fPos.y;
	data.background = m_iBack;
	data.block = m_iBlock;
	data.enemy = m_iEnemy;
	data.item = m_iItem;
	data.itemsize = m_iItemSize;
	return &data;
}


void Piece::SetPiece()
{
	if (m_modification)
	{
		switch (TopUI::GetInstance()->GetGroupIndex())
		{
		case GROUP_BACKGROUND:
		{
			m_iBack = BGUI::GetInstance()->GetIndex();
			switch (BGUI::GetInstance()->GetIndex())
			{
			case 1:
				m_pBack->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("background_0.png"));
				break;
			case 2:
				m_pBack->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("background_1.png"));
				break;
			case 3:
				m_pBack->setAnchorPoint(Vec2(0.5f, 0.1f));
				m_pBack->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("castle.png"));
				break;
			}
			break;
		}
		case GROUP_BLOCK:
		{
			m_iEnemy = 0;
			m_iBlock = BlockUI::GetInstance()->GetIndex();
			m_pMulti->setAnchorPoint(Vec2(0.5f, 0.5f));
			switch (BlockUI::GetInstance()->GetIndex())
			{
			case 1:
				m_pMulti->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("block_rock0.png"));
				break;
			case 2:
				m_pMulti->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("block_rock1.png"));
				break;
			case 3:
				m_pMulti->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("block_brick0.png"));
				break;
			case 4:
				m_pMulti->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("block_brick1.png"));
				break;
			case 5:
				m_pMulti->setAnchorPoint(Vec2(0.25f, 0.5f));
				m_pMulti->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("block_pipe0.png"));
				break;
			case 6:
				m_pMulti->setAnchorPoint(Vec2(0.25f, 0.5f));
				m_pMulti->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("block_pipe1.png"));
				break;
			case 7:
				m_pMulti->setAnchorPoint(Vec2(0.16f, 0.25f));
				m_pMulti->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("block_pipe2.png"));
				break;
			case 8:
				m_pMulti->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("block_qst0.png"));
				break;
			case 9:
				m_pMulti->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("jumper0.png"));
				break;
			case 10:
				m_pMulti->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("pole.png"));
				m_pMulti->setAnchorPoint(Vec2(0.5f, 0.05f));
				break;
			}
			break;
		}
		case GROUP_ITEM:
		{
			m_iItemSize = ItemUI::GetInstance()->GetItemSize();
			char temp[256];
			sprintf(temp, "%d", m_iItemSize);

			if (m_iEnemy != 0)
			{
				m_layer->removeChild(m_pMulti);
				m_pMulti->release();
				m_pMulti = Sprite::create();
			}
			m_iEnemy = 0;
			m_iItem = ItemUI::GetInstance()->GetIndex();
			m_pItemSize->setString(temp);
			switch (m_iItem)
			{
			case 1:
				m_pItem->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("item_mush0.png"));
				break;
			case 2:
				m_pItem->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("item_mush1.png"));
				break;
			case 3:
				m_pItem->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("item_mush2.png"));
				break;
			case 4:
				m_pItem->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("item_flower.png"));
				break;
			case 5:
				m_pItem->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("item_star.png"));
				break;
			case 6:
				m_pItem->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("item_coin0.png"));
				break;
			}
			break;
		}
		case GROUP_ENEMY:
		{
			if (m_iItem != 0)
			{
				m_layer->removeChild(m_pItem);
				m_pItem->release();
				m_pItem = Sprite::create();
			}
			m_iItem = 0;
			m_iItemSize = 0;
			m_pMulti->setAnchorPoint(Vec2(0.5f, 0.5f));
			m_iEnemy = EnemyUI::GetInstance()->GetIndex();
			m_iBlock = 0;
			switch (EnemyUI::GetInstance()->GetIndex())
			{
			case 1:
				m_pMulti->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy0_1.png"));
				break;
			case 2:
				m_pMulti->setAnchorPoint(Vec2(0.5f, 0.333f));
				m_pMulti->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy1_0.png"));
				break;
			case 3:
				m_pMulti->setAnchorPoint(Vec2(0.5f, 0.333f));
				m_pMulti->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy2_0.png"));
				break;
			case 4:
				m_pMulti->setAnchorPoint(Vec2(0.5f, 0.333f));
				m_pMulti->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy4_0.png"));
				break;
			}
			break;
		}
		}
	}
}

void Piece::SetPiece(GROUPINDEX gindex, int index)
{
	switch (gindex)
	{
	case GROUP_BACKGROUND:
	{
		m_iBack = index;
		switch (m_iBack)
		{
		case 1:
			m_pBack->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("background_0.png"));
			break;
		case 2:
			m_pBack->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("background_1.png"));
			break;
		}
		break;
	}
	case GROUP_BLOCK:
	{
		m_iEnemy = 0;
		m_iBlock = index;
		m_pMulti->setAnchorPoint(Vec2(0.5f, 0.5f));
		switch (m_iBlock)
		{
		case 1:
			m_pMulti->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("block_rock0.png"));
			break;
		case 2:
			m_pMulti->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("block_rock1.png"));
			break;
		case 3:
			m_pMulti->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("block_brick0.png"));
			break;
		case 4:
			m_pMulti->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("block_brick1.png"));
			break;
		case 5:
			m_pMulti->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("block_pipe0.png"));
			break;
		case 6:
			m_pMulti->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("block_pipe1.png"));
			break;
		case 7:
			m_pMulti->setAnchorPoint(Vec2(0.3f, 0.5f));
			m_pMulti->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("block_pipe2.png"));
			break;
		case 8:
			m_pMulti->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("block_qst0.png"));
			break;
		case 9:
			m_pMulti->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("jumper0.png"));
			break;
		case 10:
			m_pMulti->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("pole0.png"));
			break;
		case 11:
			m_pMulti->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("pole1.png"));
			break;
		case 12:
			m_pBack->setAnchorPoint(Vec2(0.5f, 0.1f));
			m_pBack->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("castle.png"));
			break;
		}
		break;
	}
	case GROUP_ITEM:
	{
		m_iItemSize = ItemUI::GetInstance()->GetItemSize();
		char temp[256];
		sprintf(temp, "%d", m_iItemSize);

		if (m_iEnemy != 0)
		{
			m_iEnemy = 0;
			m_layer->removeChild(m_pMulti);
			m_pMulti->release();
			m_pMulti = Sprite::create();
		}

		m_pItemSize->setString(temp);
		m_iItem = index;
		switch (index)
		{
		case 1:
			m_pItem->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("item_mush0.png"));
			break;
		case 2:
			m_pItem->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("item_mush1.png"));
			break;
		case 3:
			m_pItem->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("item_mush2.png"));
			break;
		case 4:
			m_pItem->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("item_flower.png"));
			break;
		case 5:
			m_pItem->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("item_star.png"));
			break;
		case 6:
			m_pItem->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("item_coin0.png"));
			break;
		}
		break;
	}
	case GROUP_ENEMY:
	{
		m_iItem = 0;
		m_iItemSize = 0;
		m_pMulti->setAnchorPoint(Vec2(0.5f, 0.5f));
		m_layer->removeChild(m_pItem);
		m_pItem->release();
		m_pItem = Sprite::create();

		m_iEnemy = index;
		m_iBlock = 0;
		switch (m_iEnemy)
		{
		case 1:
			m_pMulti->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy0_1.png"));
			break;
		case 2:
			m_pMulti->setAnchorPoint(Vec2(0.5f, 0.333f));
			m_pMulti->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy1_0.png"));
			break;
		case 3:
			m_pMulti->setAnchorPoint(Vec2(0.5f, 0.333f));
			m_pMulti->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy2_0.png"));
			break;
		case 4:
			m_pMulti->setAnchorPoint(Vec2(0.5f, 0.333f));
			m_pMulti->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy4_0.png"));
			break;
		}
		break;
	}
	}
}

bool Piece::GetModification()
{
	return m_modification;
}

void Piece::SetBackground(int index)
{
	switch (index)
	{
	case 1:
		m_pBack->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("background_0.png"));
		break;
	case 2:
		m_pBack->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("background_1.png"));
		break;
	case 3:
		m_pBack->setAnchorPoint(Vec2(0.5f, 0.1f));
		m_pBack->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("castle.png"));
		break;
	}
}

void Piece::SetBlock(int index)
{
	switch (index)
	{
	case 1:
		m_pMulti->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("block_rock0.png"));
		break;
	case 2:
		m_pMulti->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("block_rock1.png"));
		break;
	case 3:
		m_pMulti->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("block_brick0.png"));
		break;
	case 4:
		m_pMulti->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("block_brick1.png"));
		break;
	case 5:
		m_pMulti->setAnchorPoint(Vec2(0.25f, 0.5f));
		m_pMulti->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("block_pipe0.png"));
		break;
	case 6:
		m_pMulti->setAnchorPoint(Vec2(0.25f, 0.5f));
		m_pMulti->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("block_pipe1.png"));
		break;
	case 7:
		m_pMulti->setAnchorPoint(Vec2(0.16f, 0.25f));
		m_pMulti->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("block_pipe2.png"));
		break;
	case 8:
		m_pMulti->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("block_qst0.png"));
		break;
	case 9:
		m_pMulti->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("jumper0.png"));
		break;
	case 10:
		m_pMulti->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("pole.png"));
		m_pMulti->setAnchorPoint(Vec2(0.5f, 0.05f));
		break;
	}
}

void Piece::SetEnemy(int index)
{
	switch (index)
	{
	case 1:
		m_pMulti->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy0_1.png"));
		break;
	case 2:
		m_pMulti->setAnchorPoint(Vec2(0.5f, 0.333f));
		m_pMulti->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy1_0.png"));
		break;
	case 3:
		m_pMulti->setAnchorPoint(Vec2(0.5f, 0.333f));
		m_pMulti->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy2_0.png"));
		break;
	case 4:
		m_pMulti->setAnchorPoint(Vec2(0.5f, 0.333f));
		m_pMulti->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy4_0.png"));
		break;
	}
}

void Piece::SetItem(int index)
{
	if (m_iItemSize != 0)
	{
		char temp[256];
		sprintf(temp, "%d", m_iItemSize);
		m_pItemSize->setString(temp);
	}
	switch (index)
	{
	case 1:
		m_pItem->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("item_mush0.png"));
		break;
	case 2:
		m_pItem->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("item_mush1.png"));
		break;
	case 3:
		m_pItem->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("item_mush2.png"));
		break;
	case 4:
		m_pItem->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("item_flower.png"));
		break;
	case 5:
		m_pItem->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("item_star.png"));
		break;
	case 6:
		m_pItem->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("item_coin0.png"));
		break;
	}
}

Piece::Piece()
{
}


Piece::~Piece()
{
}
