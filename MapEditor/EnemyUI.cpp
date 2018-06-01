#include "EnemyUI.h"

EnemyUI* EnemyUI::m_this = NULL;

EnemyUI::EnemyUI()
{
}


void EnemyUI::Init(Layer * layer)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 visibleOrigin = Director::getInstance()->getVisibleOrigin();

	m_iGroupIndex = 3;

	m_iSelectIndex = 1;

	m_EnemyImg[0] = Sprite::createWithSpriteFrameName("enemy0_0.png");
	m_EnemyImg[1] = Sprite::createWithSpriteFrameName("enemy1_0.png");
	m_EnemyImg[2] = Sprite::createWithSpriteFrameName("enemy2_0.png");
	m_EnemyImg[3] = Sprite::createWithSpriteFrameName("enemy4_0.png");


	for (int i = 0; i < ENEMYSIZE; i++)
	{
		m_EnemyImg[i]->setPosition(Vec2(visibleOrigin.x + visibleSize.width * 31 / 32, visibleOrigin.y + visibleSize.height * (26 - (i * 2)) / 30));
		m_EnemyButton[i] = ui::Button::create("rbutton_off.png", "rbutton_on.png");
		m_EnemyButton[i]->setPosition(Vec2(visibleOrigin.x + visibleSize.width * 29 / 32, visibleOrigin.y + visibleSize.height * (26 - (i * 2)) / 30));
		m_EnemyButton[i]->addClickEventListener(CC_CALLBACK_0(EnemyUI::PressButton, this, i));
		layer->addChild(m_EnemyButton[i], UI);
		layer->addChild(m_EnemyImg[i], UI);
	}
	m_EnemyButton[0]->setHighlighted(true);
	SetVisibleList(false);
}

void EnemyUI::PressButton(int index)
{
	m_iSelectIndex = index + 1;
	for (int i = 0; i < ENEMYSIZE; i++)
	{
		m_EnemyButton[i]->setHighlighted(false);
	}
	m_EnemyButton[index]->setHighlighted(true);
}

void EnemyUI::SetVisibleList(bool visible)
{
	for (int i = 0; i < ENEMYSIZE; i++)
	{
		m_EnemyButton[i]->setVisible(visible);
		m_EnemyImg[i]->setVisible(visible);
	}
}

int EnemyUI::GetIndex()
{
	return m_iSelectIndex;
}

EnemyUI::~EnemyUI()
{
}
