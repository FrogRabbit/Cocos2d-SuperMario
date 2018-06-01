#include "UiManager.h"
#include "PlayerManager.h"

UiManager* UiManager::m_this = NULL;

UiManager::UiManager()
{
}


void UiManager::Init(Layer * layer)
{
	m_iStage = 1;

	m_topUI = Layer::create();
	m_topUI->setContentSize(Size(600, 45));
	m_topUI->setAnchorPoint(Vec2(0, 0));
	m_topUI->setPosition(Vec2(0, 448-45));
	layer->addChild(m_topUI, 5);
	
	m_iCoin = 0;;
	m_iScore = 0;
	m_iLife = 2;
	m_iLeftTime = 300;
	m_fTimeCheck = 0;

	Sprite* coinspr = Sprite::create("ui_coin0.png");
	Vector<SpriteFrame*> animationFrame(4);
	for (int i = 0; i < 4; i++)
	{
		char szFileName[256];
		sprintf(szFileName, "ui_coin%d.png", i%3);
		SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(szFileName);
		animationFrame.pushBack(frame);
	}
	Animation* animation = Animation::createWithSpriteFrames(animationFrame, 0.1f);
	Animate* animate = Animate::create(animation);
	coinspr->runAction(RepeatForever::create(animate));
	coinspr->setPosition(Vec2(190, 9));
	coinspr->setScale(2.0f);
	m_topUI->addChild(coinspr);

	m_coinLabel = Label::create();
	char temp[128];
	sprintf(temp, "X %4d", m_iCoin);
	m_coinLabel->setString(temp);
	m_coinLabel->setTextColor(Color4B(255, 255, 255, 255));
	m_coinLabel->setPosition(Vec2(220, 9));
	m_topUI->addChild(m_coinLabel);
	{
		m_scoreLabel = Label::create();
		char temp[128];
		sprintf(temp, "%d", m_iScore);
		m_scoreLabel->setString(temp);
		m_scoreLabel->setTextColor(Color4B(255, 255, 255, 255));
		m_scoreLabel->setPosition(Vec2(100, 9));
		m_topUI->addChild(m_scoreLabel);

		Label* m_scoreTextLabel = Label::create();
		m_scoreTextLabel->setString("SCORE");
		m_scoreTextLabel->setTextColor(Color4B(255, 255, 255, 255));
		m_scoreTextLabel->setPosition(Vec2(100, 27));
		m_topUI->addChild(m_scoreTextLabel);
	}
	{
		m_timeLabel = Label::create();
		char temp[128];
		sprintf(temp, "%d", m_iLeftTime);
		m_timeLabel->setString(temp);
		m_timeLabel->setTextColor(Color4B(255, 255, 255, 255));
		m_timeLabel->setPosition(Vec2(450, 9));
		m_topUI->addChild(m_timeLabel);

		Label* m_timeTextLabel = Label::create();
		m_timeTextLabel->setString("TIME");
		m_timeTextLabel->setTextColor(Color4B(255, 255, 255, 255));
		m_timeTextLabel->setPosition(Vec2(450, 27));
		m_topUI->addChild(m_timeTextLabel);
	}

	m_semiTitle = LayerColor::create();
	m_semiTitle->initWithColor(Color4B(0, 0, 0, 255));
	m_semiTitle->setContentSize(Size(600, 448));
	m_semiTitle->setAnchorPoint(Vec2(0, 0));
	m_semiTitle->setPosition(Vec2(0, 0));
	layer->addChild(m_semiTitle, 4);

	Sprite* mspr = Sprite::create("s_mario_stand.png");
	mspr->setPosition(Vec2(275, 224));
	mspr->setScale(2.0f);
	m_semiTitle->addChild(mspr);
	{
		m_LifeLabel = Label::create();
		char temp[128];
		sprintf(temp, "X %4d", m_iLife);
		m_LifeLabel->setString(temp);
		m_LifeLabel->setSystemFontSize(15);
		m_LifeLabel->setTextColor(Color4B(255, 255, 255, 255));
		m_LifeLabel->setPosition(Vec2(325, 224));
		m_semiTitle->addChild(m_LifeLabel);
	}
	m_semiTitle->setVisible(false);

	{
		Label* stageLabel = Label::create();
		stageLabel->setString("STAGE");
		stageLabel->setTextColor(Color4B(255, 255, 255, 255));
		stageLabel->setPosition(Vec2(330, 27));
		m_topUI->addChild(stageLabel);

		m_stageLabel = Label::create();
		char temp[128];
		sprintf(temp, "%d", m_iStage);
		m_stageLabel->setString(temp);
		m_stageLabel->setTextColor(Color4B(255, 255, 255, 255));
		m_stageLabel->setPosition(Vec2(330, 9));
		m_topUI->addChild(m_stageLabel);
	}
}

void UiManager::Update(float ElapsedTime)
{
	m_fTimeCheck += ElapsedTime;
	if (m_fTimeCheck >= 0.5f)
	{
		m_fTimeCheck = 0;
		m_iLeftTime--;
		char temp[128];
		sprintf(temp, "%d", m_iLeftTime);
		m_timeLabel->setString(temp);
		if (m_iLeftTime < 0)
		{
			m_iLeftTime = 0;
			PlayerManager::GetInstance()->Die();
		}
	}
	
}

void UiManager::AddScore(int score)
{
	m_iScore += score;
	char temp[128];
	sprintf(temp, "%d", m_iScore);
	m_scoreLabel->setString(temp);
}

void UiManager::AddCoin()
{
	m_iCoin++;
	char temp[128];
	sprintf(temp, "X %4d", m_iCoin);
	m_coinLabel->setString(temp);
}

void UiManager::SetSemiTitleVisible(bool visible)
{
	m_semiTitle->setVisible(visible);
}

void UiManager::DecLife()
{
	m_iLife--;
	char temp[128];
	sprintf(temp, "X %4d", m_iLife);
	m_LifeLabel->setString(temp);
}

void UiManager::IncLife()
{
	m_iLife++;
	char temp[128];
	sprintf(temp, "X %4d", m_iLife);
	m_LifeLabel->setString(temp);
}

int UiManager::GetLife()
{
	return m_iLife;
}

void UiManager::ClearTime()
{
	m_iLeftTime = 300;
}

void UiManager::SetStage(int stage)
{
	m_iStage = stage;
	char temp[128];
	sprintf(temp, "%d", m_iStage);
	m_stageLabel->setString(temp);
}

UiManager::~UiManager()
{
}
