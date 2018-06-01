#include "BlockUI.h"

BlockUI* BlockUI::m_this = NULL;

BlockUI::BlockUI()
{
}


void BlockUI::Init(Layer * layer)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 visibleOrigin = Director::getInstance()->getVisibleOrigin();

	m_iGroupIndex = 1;

	m_iSelectIndex = 1;

	m_BlockImg[0] = Sprite::createWithSpriteFrameName("block_rock0.png");
	m_BlockImg[1] = Sprite::createWithSpriteFrameName("block_rock1.png");
	m_BlockImg[2] = Sprite::createWithSpriteFrameName("block_brick0.png");
	m_BlockImg[3] = Sprite::createWithSpriteFrameName("block_brick1.png");
	m_BlockImg[4] = Sprite::createWithSpriteFrameName("block_pipe0.png");
	m_BlockImg[5] = Sprite::createWithSpriteFrameName("block_pipe1.png");
	m_BlockImg[6] = Sprite::createWithSpriteFrameName("block_pipe2.png");
	m_BlockImg[7] = Sprite::createWithSpriteFrameName("block_qst0.png");
	m_BlockImg[8] = Sprite::createWithSpriteFrameName("jumper0.png");
	m_BlockImg[9] = Sprite::createWithSpriteFrameName("pole.png");


	for (int i = 0; i < BLOCKSIZE; i++)
	{
		m_BlockImg[i]->setPosition(Vec2(visibleOrigin.x + visibleSize.width * 31 / 32, visibleOrigin.y + visibleSize.height * (26 - (i * 2)) / 30));
		m_BlockButton[i] = ui::Button::create("rbutton_off.png", "rbutton_on.png");
		m_BlockButton[i]->setPosition(Vec2(visibleOrigin.x + visibleSize.width * 29 / 32, visibleOrigin.y + visibleSize.height * (26 - (i * 2)) / 30));
		m_BlockButton[i]->addClickEventListener(CC_CALLBACK_0(BlockUI::PressButton, this, i));
		layer->addChild(m_BlockButton[i], UI);
		layer->addChild(m_BlockImg[i], UI);
	}
	m_BlockButton[0]->setHighlighted(true);
	m_BlockImg[9]->setScale(0.3f);
	SetVisibleList(false);
}

void BlockUI::PressButton(int index)
{
	m_iSelectIndex = index + 1;
	for (int i = 0; i < BLOCKSIZE; i++)
	{
		m_BlockButton[i]->setHighlighted(false);
	}
	m_BlockButton[index]->setHighlighted(true);
}

void BlockUI::SetVisibleList(bool visible)
{
	for (int i = 0; i < BLOCKSIZE; i++)
	{
		m_BlockButton[i]->setVisible(visible);
		m_BlockImg[i]->setVisible(visible);
	}
}

int BlockUI::GetIndex()
{
	return m_iSelectIndex;
}



BlockUI::~BlockUI()
{
}
