#include "ItemUI.h"

ItemUI* ItemUI::m_this = NULL;

ItemUI::ItemUI()
{
}


void ItemUI::Init(Layer * layer)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 visibleOrigin = Director::getInstance()->getVisibleOrigin();

	m_iGroupIndex = 2;

	m_iSelectIndex = 1;

	m_iItemSize = 1;

	m_ItemSize = ui::EditBox::create(Size(48, 32), ui::Scale9Sprite::create("editbox.png"));
	m_ItemSize->setPosition(Vec2(visibleOrigin.x + visibleSize.width * 30 / 32, visibleOrigin.y + visibleSize.height * (26 - (6 * 2)) / 30));
	m_ItemSize->setFontName("Paint Boy");
	m_ItemSize->setFontSize(15);
	m_ItemSize->setFontColor(Color3B::BLACK);
	m_ItemSize->setPlaceHolder("1");
	m_ItemSize->setPlaceholderFontColor(Color3B::BLACK);
	m_ItemSize->setMaxLength(8);
	m_ItemSize->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
	m_ItemSize->setVisible(false);

	m_ApplyButton = ui::Button::create("apply_off.png", "apply_on.png");
	m_ApplyButton->setPosition(Vec2(visibleOrigin.x + visibleSize.width * 30 / 32, visibleOrigin.y + visibleSize.height * (26 - (7 * 2)) / 30));
	m_ApplyButton->addClickEventListener(CC_CALLBACK_0(ItemUI::PressApply, this));
	m_ApplyButton->setVisible(false);
	
	layer->addChild(m_ApplyButton, UI);
	layer->addChild(m_ItemSize, UI);

	m_ItemImg[0] = Sprite::createWithSpriteFrameName("item_mush0.png");
	m_ItemImg[1] = Sprite::createWithSpriteFrameName("item_mush1.png");
	m_ItemImg[2] = Sprite::createWithSpriteFrameName("item_mush2.png");
	m_ItemImg[3] = Sprite::createWithSpriteFrameName("item_flower.png");
	m_ItemImg[4] = Sprite::createWithSpriteFrameName("item_star.png");
	m_ItemImg[5] = Sprite::createWithSpriteFrameName("item_coin0.png");


	for (int i = 0; i < ITEMSIZE; i++)
	{
		m_ItemImg[i]->setPosition(Vec2(visibleOrigin.x + visibleSize.width * 31 / 32, visibleOrigin.y + visibleSize.height * (26 - (i * 2)) / 30));
		m_ItemButton[i] = ui::Button::create("rbutton_off.png", "rbutton_on.png");
		m_ItemButton[i]->setPosition(Vec2(visibleOrigin.x + visibleSize.width * 29 / 32, visibleOrigin.y + visibleSize.height * (26 - (i * 2)) / 30));
		m_ItemButton[i]->addClickEventListener(CC_CALLBACK_0(ItemUI::PressButton, this, i));
		layer->addChild(m_ItemButton[i], UI);
		layer->addChild(m_ItemImg[i], UI);
	}
	m_ItemButton[0]->setHighlighted(true);
	SetVisibleList(false);
}

void ItemUI::PressButton(int index)
{
	m_iSelectIndex = index + 1;
	for (int i = 0; i < ITEMSIZE; i++)
	{
		m_ItemButton[i]->setHighlighted(false);
	}
	m_ItemButton[index]->setHighlighted(true);
}

void ItemUI::SetVisibleList(bool visible)
{
	for (int i = 0; i < ITEMSIZE; i++)
	{
		m_ItemButton[i]->setVisible(visible);
		m_ItemImg[i]->setVisible(visible);
	}
	m_ApplyButton->setVisible(visible);
	m_ItemSize->setVisible(visible);
}

void ItemUI::PressApply()
{
	m_iItemSize = atoi(m_ItemSize->getText());
}

int ItemUI::GetIndex()
{
	return m_iSelectIndex;
}

int ItemUI::GetItemSize()
{
	return m_iItemSize;
}

ItemUI::~ItemUI()
{
}
