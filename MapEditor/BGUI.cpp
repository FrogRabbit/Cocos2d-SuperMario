#include "BGUI.h"

BGUI* BGUI::m_this = NULL;

BGUI::BGUI()
{
}


void BGUI::Init(Layer * layer)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 visibleOrigin = Director::getInstance()->getVisibleOrigin();

	m_iGroupIndex = 0;

	m_iSelectIndex = 1;

	for (int i = 0; i < 2; i++)
	{
		char szTemp[256];
		sprintf(szTemp, "background_%d.png", i);
		m_BackImg[i] = Sprite::createWithSpriteFrameName(szTemp);
		m_BackImg[i]->setPosition(Vec2(visibleOrigin.x + visibleSize.width * 31 / 32, visibleOrigin.y + visibleSize.height * (26 - (i * 2)) / 30));
		m_backgroundButton[i] = ui::Button::create("rbutton_off.png", "rbutton_on.png");
		m_backgroundButton[i]->setPosition(Vec2(visibleOrigin.x + visibleSize.width * 29 / 32, visibleOrigin.y + visibleSize.height * (26 - ( i * 2 )) / 30));
		m_backgroundButton[i]->addClickEventListener(CC_CALLBACK_0(BGUI::PressButton, this, i));
		layer->addChild(m_backgroundButton[i], UI);
		layer->addChild(m_BackImg[i], UI);
	}
	m_BackImg[2] = Sprite::createWithSpriteFrameName("castle.png");
	m_BackImg[2]->setPosition(Vec2(visibleOrigin.x + visibleSize.width * 31 / 32, visibleOrigin.y + visibleSize.height * (26 - (2 * 2)) / 30));
	m_BackImg[2]->setScale(0.5f);
	m_backgroundButton[2] = ui::Button::create("rbutton_off.png", "rbutton_on.png");
	m_backgroundButton[2]->setPosition(Vec2(visibleOrigin.x + visibleSize.width * 29 / 32, visibleOrigin.y + visibleSize.height * (26 - (2 * 2)) / 30));
	m_backgroundButton[2]->addClickEventListener(CC_CALLBACK_0(BGUI::PressButton, this, 2));
	layer->addChild(m_backgroundButton[2], UI);
	layer->addChild(m_BackImg[2], UI);
	m_backgroundButton[0]->setHighlighted(true);
}

void BGUI::PressButton(int index)
{
	m_iSelectIndex = index + 1;
	for (int i = 0; i < BACKGROUNDSIZE; i++)
	{
		m_backgroundButton[i]->setHighlighted(false);
	}
	m_backgroundButton[index]->setHighlighted(true);
}

void BGUI::SetVisibleList(bool visible)
{
	for (int i = 0; i < BACKGROUNDSIZE; i++)
	{
		m_backgroundButton[i]->setVisible(visible);
		m_BackImg[i]->setVisible(visible);
	}
}

int BGUI::GetIndex()
{
	return m_iSelectIndex;
}

BGUI::~BGUI()
{
}
