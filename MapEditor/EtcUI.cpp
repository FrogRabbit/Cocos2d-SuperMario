#include "EtcUI.h"

EtcUI* EtcUI::m_this = NULL;

EtcUI::EtcUI()
{
}


void EtcUI::Init(Layer * layer)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 visibleOrigin = Director::getInstance()->getVisibleOrigin();

	m_iGroupIndex = 1;

	m_iSelectIndex = 1;

	m_EtcImg[0] = Sprite::createWithSpriteFrameName("start.png");
	m_EtcImg[1] = Sprite::createWithSpriteFrameName("check.png");
	m_EtcImg[2] = Sprite::createWithSpriteFrameName("destination.png");


	for (int i = 0; i < 3; i++)
	{
		m_EtcImg[i]->setPosition(Vec2(visibleOrigin.x + visibleSize.width * 31 / 32, visibleOrigin.y + visibleSize.height * (26 - (i * 2)) / 30));
		m_EtcButton[i] = ui::Button::create("rbutton_off.png", "rbutton_on.png");
		m_EtcButton[i]->setPosition(Vec2(visibleOrigin.x + visibleSize.width * 29 / 32, visibleOrigin.y + visibleSize.height * (26 - (i * 2)) / 30));
		m_EtcButton[i]->addClickEventListener(CC_CALLBACK_0(EtcUI::PressButton, this, i));
		layer->addChild(m_EtcButton[i], UI);
		layer->addChild(m_EtcImg[i], UI);
	}
	m_EtcButton[0]->setHighlighted(true);
	SetVisibleList(false);
}

void EtcUI::PressButton(int index)
{
	m_iSelectIndex = index + 1;
	for (int i = 0; i < 3; i++)
	{
		m_EtcButton[i]->setHighlighted(false);
	}
	m_EtcButton[index]->setHighlighted(true);
}

void EtcUI::SetVisibleList(bool visible)
{
	for (int i = 0; i < 3; i++)
	{
		m_EtcButton[i]->setVisible(visible);
		m_EtcImg[i]->setVisible(visible);
	}
}

int EtcUI::GetIndex()
{
	return m_iSelectIndex;
}

EtcUI::~EtcUI()
{
}
