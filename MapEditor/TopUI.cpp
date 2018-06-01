#include "TopUI.h"
#include "BGUI.h"
#include "BlockUI.h"
#include "ItemUI.h"
#include "EnemyUI.h"
#include "ui\UISlider.h"
#include "MapEditor.h"
#include "MapManager.h"
#include "EtcUI.h"

TopUI* TopUI::m_this = NULL;

TopUI::TopUI()
{
}


void TopUI::Init(Layer * layer)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 visibleOrigin = Director::getInstance()->getVisibleOrigin();

	m_iStage = 1;

	m_iGroupIndex = 0;

	std::string pNormalSprite = "editbox.png";
	//width
	m_WidthBox = ui::EditBox::create(Size(64, 32), ui::Scale9Sprite::create(pNormalSprite));
	m_WidthBox->setPosition(Vec2(visibleOrigin.x + visibleSize.width * 3 / 32 + 10, visibleOrigin.y + visibleSize.height * 19 / 20));
	m_WidthBox->setAnchorPoint(Vec2(0, 0.5f));
	m_WidthBox->setFontName("Paint Boy");
	m_WidthBox->setFontSize(15);
	m_WidthBox->setFontColor(Color3B::BLACK);
	m_WidthBox->setPlaceHolder("Width");
	m_WidthBox->setPlaceholderFontColor(Color3B::BLACK);
	m_WidthBox->setMaxLength(8);
	m_WidthBox->setReturnType(ui::EditBox::KeyboardReturnType::DONE);

	m_LifeBox = ui::EditBox::create(Size(64, 32), ui::Scale9Sprite::create(pNormalSprite));
	m_LifeBox->setPosition(Vec2(visibleOrigin.x + visibleSize.width * 11 / 32 + 10, visibleOrigin.y + visibleSize.height * 19 / 20));
	m_LifeBox->setAnchorPoint(Vec2(0, 0.5f));
	m_LifeBox->setFontName("Paint Boy");
	m_LifeBox->setFontSize(15);
	m_LifeBox->setFontColor(Color3B::BLACK);
	m_LifeBox->setPlaceHolder("Life");
	m_LifeBox->setPlaceholderFontColor(Color3B::BLACK);
	m_LifeBox->setMaxLength(8);
	m_LifeBox->setReturnType(ui::EditBox::KeyboardReturnType::DONE);

	m_TimeBox = ui::EditBox::create(Size(64, 32), ui::Scale9Sprite::create(pNormalSprite));
	m_TimeBox->setPosition(Vec2(visibleOrigin.x + visibleSize.width * 16 / 32 + 10, visibleOrigin.y + visibleSize.height * 19 / 20));
	m_TimeBox->setAnchorPoint(Vec2(0, 0.5f));
	m_TimeBox->setFontName("Paint Boy");
	m_TimeBox->setFontSize(15);
	m_TimeBox->setFontColor(Color3B::BLACK);
	m_TimeBox->setPlaceHolder("Time");
	m_TimeBox->setPlaceholderFontColor(Color3B::BLACK);
	m_TimeBox->setMaxLength(8);
	m_TimeBox->setReturnType(ui::EditBox::KeyboardReturnType::DONE);

	Label* label0 = Label::create();
	label0->setString("Width(100~212):");
	label0->setAnchorPoint(Vec2(1, 0.5f));
	label0->setTextColor(Color4B::BLACK);
	label0->setPosition(Vec2(visibleOrigin.x + (visibleSize.width * 3 / 32), visibleOrigin.y + visibleSize.height * 19 / 20));

	Label* label1 = Label::create();
	label1->setString("Life(0~5):");
	label1->setAnchorPoint(Vec2(1, 0.5f));
	label1->setTextColor(Color4B::BLACK);
	label1->setPosition(Vec2(visibleOrigin.x + (visibleSize.width * 11 / 32), visibleOrigin.y + visibleSize.height * 19 / 20));

	Label* label2 = Label::create();
	label2->setString("Time(50~300):");
	label2->setAnchorPoint(Vec2(1, 0.5f));
	label2->setTextColor(Color4B::BLACK);
	label2->setPosition(Vec2(visibleOrigin.x + (visibleSize.width * 16 / 32), visibleOrigin.y + visibleSize.height * 19 / 20));

	m_ApplyButton = ui::Button::create("apply_off.png", "apply_on.png");
	m_ApplyButton->setPosition(Vec2(visibleOrigin.x + visibleSize.width * 7 / 32, visibleOrigin.y + visibleSize.height * 19 / 20));
	m_ApplyButton->addClickEventListener(CC_CALLBACK_0(TopUI::PressApply, this));

	Label* label[5];
	for (int i = 0; i < 5; i++)
	{
		label[i] = Label::create();
		label[i]->setAnchorPoint(Vec2(0.5f, 0.5f));
		label[i]->setTextColor(Color4B::BLACK);
		label[i]->setPosition(Vec2(visibleOrigin.x + visibleSize.width * (21 + (i * 2)) / 32, visibleOrigin.y + visibleSize.height * 19 / 20));
		m_menuButton[i] = ui::Button::create("rbutton_off.png", "rbutton_on.png");
		m_menuButton[i]->setPosition(Vec2(visibleOrigin.x + visibleSize.width * (20 + (i * 2)) / 32, visibleOrigin.y + visibleSize.height * 19 / 20));
		m_menuButton[i]->addClickEventListener(CC_CALLBACK_0(TopUI::PressMenuButton, this, i));
		layer->addChild(label[i]);
		layer->addChild(m_menuButton[i], UI);
	}
	m_menuButton[5] = ui::Button::create("rbutton_off.png", "rbutton_on.png");
	m_menuButton[5]->setPosition(Vec2(visibleOrigin.x + visibleSize.width * (20 + (3 * 3)) / 32, visibleOrigin.y + visibleSize.height * 2 / 20));
	m_menuButton[5]->addClickEventListener(CC_CALLBACK_0(TopUI::PressMenuButton, this, 5));
	
	Label* label3 = Label::create();
	label3->setString("Erase");
	label3->setAnchorPoint(Vec2(1, 0.5f));
	label3->setTextColor(Color4B::BLACK);
	label3->setPosition(Vec2(visibleOrigin.x + visibleSize.width * (22 + (3 * 3)) / 32, visibleOrigin.y + visibleSize.height * 2 / 20));
	
	layer->addChild(label3, UI);
	layer->addChild(m_menuButton[5], UI);

	m_SaveButton = ui::Button::create("save_off.png", "save_on.png");
	m_SaveButton->setPosition(Vec2(visibleOrigin.x + visibleSize.width * 24 / 32, visibleOrigin.y + visibleSize.height * 4 / 20));
	m_SaveButton->addClickEventListener(CC_CALLBACK_0(TopUI::SaveFile, this));
	layer->addChild(m_SaveButton, UI);

	m_ClearButton = ui::Button::create("clear_off.png", "clear_on.png");
	m_ClearButton->setPosition(Vec2(visibleOrigin.x + visibleSize.width * 24 / 32, visibleOrigin.y + visibleSize.height * 2.5 / 20));
	m_ClearButton->addClickEventListener(CC_CALLBACK_0(TopUI::Clear, this));
	layer->addChild(m_ClearButton, UI);

	Label* label4 = Label::create();
	label4->setString("Stage : ");
	label4->setTextColor(Color4B::BLACK);
	label4->setPosition(Vec2(visibleOrigin.x + visibleSize.width * 23 / 32, visibleOrigin.y + visibleSize.height * 8 / 20));

	for (int i = 0; i < 2; i++)
	{
		Label* label = Label::create();
		char temp[16];
		sprintf(temp, "%d stage", i + 1);
		label->setString(temp);
		label->setTextColor(Color4B::BLACK);
		label->setPosition(Vec2(visibleOrigin.x + visibleSize.width * 25 / 32, visibleOrigin.y + visibleSize.height * (8 - i) / 20));
		m_StageButton[i] = ui::Button::create("rbutton_off.png", "rbutton_on.png");
		m_StageButton[i]->setPosition(Vec2(visibleOrigin.x + visibleSize.width * 24 / 32, visibleOrigin.y + visibleSize.height * (8 - i) / 20));
		m_StageButton[i]->addClickEventListener(CC_CALLBACK_0(TopUI::ChangeStage, this, i));
		layer->addChild(label, UI);
		layer->addChild(m_StageButton[i], UI);
	}
	m_StageButton[0]->setHighlighted(true);
	m_menuButton[0]->setHighlighted(true);
	label[0]->setString("Back");
	label[1]->setString("Block");
	label[2]->setString("Item");
	label[3]->setString("Enemy");
	label[4]->setString("Etc");

	layer->addChild(label0, UI);
	layer->addChild(label1, UI);
	layer->addChild(label2, UI);

	layer->addChild(label4, UI);
	layer->addChild(m_ApplyButton, UI);
	layer->addChild(m_LifeBox, UI);
	layer->addChild(m_TimeBox, UI);
	layer->addChild(m_WidthBox, UI);
}

void TopUI::PressMenuButton(int index)
{
	for (int i = 0; i < 6; i++)
	{
		m_menuButton[i]->setHighlighted(false);
	}
	m_menuButton[index]->setHighlighted(true);

	EtcUI::GetInstance()->SetVisibleList(false);
	BGUI::GetInstance()->SetVisibleList(false);
	BlockUI::GetInstance()->SetVisibleList(false);
	ItemUI::GetInstance()->SetVisibleList(false);
	EnemyUI::GetInstance()->SetVisibleList(false);
	switch (index)
	{
	case 0:
		BGUI::GetInstance()->SetVisibleList(true);
		m_iGroupIndex = 0;
		break;
	case 1:
		BlockUI::GetInstance()->SetVisibleList(true);
		m_iGroupIndex = 1;
		break;
	case 2:
		ItemUI::GetInstance()->SetVisibleList(true);
		m_iGroupIndex = 2;
		break;
	case 3:
		EnemyUI::GetInstance()->SetVisibleList(true);
		m_iGroupIndex = 3;
		break;
	case 4:
		EtcUI::GetInstance()->SetVisibleList(true);
		m_iGroupIndex = 4;
		break;
	case 5:
		m_iGroupIndex = 5;
		break;
	default:
		break;
	}
}

void TopUI::PressApply()
{
	int width = atoi(m_WidthBox->getText());
	if (width >= 50 && width <= 212)
	{
		MapEditor::GetInstance()->SetWidthSize(width);
	}
}

int TopUI::GetGroupIndex()
{
	return m_iGroupIndex;
}

void TopUI::sliderEvent()
{
}

void TopUI::SaveFile()
{
	MapManager::GetInstance()->SaveFile(m_iStage);
}

void TopUI::Clear()
{
	MapManager::GetInstance()->Release();
}

void TopUI::ChangeStage(int stage)
{
	for (int i = 0; i < 2; i++)
	{
		m_StageButton[i]->setHighlighted(false);
	}
	m_iStage = stage + 1;
	m_StageButton[stage]->setHighlighted(true);
	MapManager::GetInstance()->Release();
	MapManager::GetInstance()->LoadFile(m_iStage);
}

SAVE_HEADER TopUI::GetData()
{
	return SAVE_HEADER();
}

TopUI::~TopUI()
{
}
