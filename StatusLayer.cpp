#include "StatusLayer.h"
#include "cocostudio/CocoStudio.h"
#include "GameOverScene.h"
#include "Stage.h"
using namespace CocosDenshion;

USING_NS_CC;

StatusLayer * StatusLayer::create()
{
	StatusLayer *pRet = new(std::nothrow) StatusLayer();
	if (pRet && pRet->init())
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = nullptr;
		return nullptr;
	}
}

bool StatusLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	// 画面サイズ取得
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// ポーズ画像を作成
	m_icon = Sprite::create("OptionNormal.png");
	m_icon->setPosition(Vec2(880.0f, 600.0f));
	this->addChild(m_icon);

	// 時間の枠画像を作成
	m_timeframe = Sprite::create("Timeframe.png");
	m_timeframe->setPosition(Vec2(960.0f / 2.0f, 605.0f));
	this->addChild(m_timeframe);


	// イベントリスナーを作成
	EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
	// イベントリススナーに各コールバック関数をセットする
	listener->onTouchBegan = CC_CALLBACK_2(StatusLayer::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(StatusLayer::onTouchEnded, this);
	// イベントリスナーを登録する
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	
	// 時間初期化
	if (Stage::m_nextflag == 1)
	{
		m_time = 60;
		Stage::m_timeflag = m_time;
	}
	else
	{
		m_time = Stage::m_timeflag;
	}

	sprintf(m_str, "%4.0f", m_time);
	time_label = Label::createWithTTF(m_str, "fonts/uzura.ttf", 50);
	time_label->setColor(Color3B::BLACK);
	time_label->setPosition(Vec2(visibleSize.width / 2.0f - 25.0f, visibleSize.height / 2.0f + 290.0f));
	time_label->enableShadow(Color4B::WHITE, Size(-2, -4), 2);
	this->addChild(time_label, 6);

	// 効果音をプリロードしておく
	SimpleAudioEngine::sharedEngine()->preloadEffect("button.mp3");
	// 音量を設定
	SimpleAudioEngine::sharedEngine()->setEffectsVolume(1.0f);


	// Update関数を呼び出す
	scheduleUpdate();

	return true;
}

bool StatusLayer::onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * unusedevent)
{
	float iconpos = m_icon->getPosition().x;

	Vec2 touchpos = touch->getLocation();

	Vec2 range = m_icon->getPosition() - touch->getLocation();


	if (touchpos.x > 855 && touchpos.x < 905 && touchpos.y > 575 && touchpos.y < 625)
	{
		m_icon->setTexture("OptionSelected.png");
		// 再生する
		SimpleAudioEngine::sharedEngine()->playEffect("button.mp3");
		return true;
	}

	return false;
}

void StatusLayer::onTouchEnded(cocos2d::Touch * touch, cocos2d::Event * unusedevent)
{
	m_icon->setTexture("OptionNormal.png");
	TransitionFade* fade = TransitionFade::create(0.3f, PauseScene::create());
	Director::getInstance()->pushScene(fade);
}

void StatusLayer::update(float dt)
{
	if (m_time > 0)
	{
		m_time -= dt;
	}
	if (m_time < 0)
	{
		m_time = 0;
		TransitionFadeTR* fade = TransitionFadeTR::create(0.5f, GameOverScene::create());
		Director::getInstance()->replaceScene(fade);
	}
	if (m_time < 3)
	{
		time_label->setColor(Color3B::RED);
	}

	sprintf(m_str, "%4.0f", m_time);
	time_label->setString(m_str);

	Stage::m_timeflag = m_time;
}
