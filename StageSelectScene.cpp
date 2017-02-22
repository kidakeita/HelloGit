#include "StageSelectScene.h"
#include "cocostudio/CocoStudio.h"
using namespace CocosDenshion;
USING_NS_CC;

StageSelectScene * StageSelectScene::create()
{
	StageSelectScene *pRet = new(std::nothrow) StageSelectScene();
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

bool StageSelectScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	// 画面サイズの取得
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// 背景レイヤーを作成
	backgroundlayer = BackGroundLayer::create();
	backgroundlayer->setAction();
	this->addChild(backgroundlayer);

	// イベントリスナーを作成
	EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
	// イベントリススナーに各コールバック関数をセットする
	listener->onTouchBegan = CC_CALLBACK_2(StageSelectScene::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(StageSelectScene::onTouchEnded, this);
	// イベントリスナーを登録する
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	m_easy = Sprite::create("stage_button1_normal.png");
	m_easy->setPosition(Vec2(480.0f, 400.0f));
	this->addChild(m_easy);

	m_normal = Sprite::create("stage_button2_normal.png");
	m_normal->setPosition(Vec2(480.0f, 250.0f));
	this->addChild(m_normal);

	m_hard = Sprite::create("stage_button3_normal.png");
	m_hard->setPosition(Vec2(480.0f, 100.0f));
	this->addChild(m_hard);

	// 変数初期化
	m_flag = 0;
	Stage::m_nextflag = 1;

	// セレクトラベル作成
	select_label = Label::createWithTTF("STAGE SELECT", "fonts/uzura.ttf", 80);
	select_label->setColor(Color3B::YELLOW);
	select_label->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 200));
	select_label->enableShadow(Color4B::BLACK, Size(-2, -4), 2);
	this->addChild(select_label);

	// BGMをプリロードしておく
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("BGM.mp3");
	// 音量を設定
	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(1.0f);
	// 再生する
	SimpleAudioEngine::getInstance()->playBackgroundMusic("BGM.mp3", true);


	// 効果音をプリロードしておく
	SimpleAudioEngine::sharedEngine()->preloadEffect("button.mp3");
	// 音量を設定
	SimpleAudioEngine::sharedEngine()->setEffectsVolume(1.0f);
	
	/*m_normal = ui::Button::create("stage_button1_normal.png", "stage_button1_selected.png");
	m_normal->addTouchEventListener(CC_CALLBACK_2(StageSelectScene::TouchEvent, this));
	m_normal->setPosition(Vec2(400.0f, 300.0f));
	this->addChild(m_normal);

	m_hard = ui::Button::create("stage_button1_normal.png", "stage_button1_selected.png");
	m_hard->addTouchEventListener(CC_CALLBACK_2(StageSelectScene::TouchEvent, this));
	m_hard->setPosition(Vec2(400.0f, 100.0f));
	this->addChild(m_hard);*/

	return true;
}

//void StageSelectScene::TouchEvent(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType type)
//{
//	switch (type)
//	{
//	case cocos2d::ui::Widget::TouchEventType::BEGAN:
//		break;
//	case cocos2d::ui::Widget::TouchEventType::ENDED:
//		break;
//
//}

bool StageSelectScene::onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * unusedevent)
{
	float easyposX = m_easy->getPosition().x;
	float normalposX = m_normal->getPosition().x;
	float hardposX = m_hard->getPosition().x;

	Vec2 touchpos = touch->getLocation();

	Vec2 easyrange = m_easy->getPosition() - touch->getLocation();
	Vec2 normalrange = m_normal->getPosition() - touch->getLocation();
	Vec2 hardrange = m_hard->getPosition() - touch->getLocation();

	if (touchpos.x > 330 && touchpos.x < 620 && touchpos.y > 350 && touchpos.y < 450)
	{
		m_easy->setTexture("stage_button1_selected.png");
		m_flag = 1;
		return true;
	}



	if (touchpos.x > 330 && touchpos.x < 620 && touchpos.y > 200 && touchpos.y < 300)
	{
		m_normal->setTexture("stage_button2_selected.png");
		m_flag = 2;
		return true;
	}
	

	if (touchpos.x > 330 && touchpos.x < 620 && touchpos.y > 50 && touchpos.y < 150)
	{
		m_hard->setTexture("stage_button3_selected.png");
		m_flag = 3;
		return true;
	}
	

	return false;

}

void StageSelectScene::onTouchEnded(cocos2d::Touch * touch, cocos2d::Event * unusedevent)
{
	m_easy->setTexture("stage_button1_normal.png");
	m_normal->setTexture("stage_button2_normal.png");
	m_hard->setTexture("stage_button3_normal.png");
	Stage::m_flag = m_flag;
	TransitionFade* fade = TransitionFade::create(0.5f, PlayScene::create(), Color3B::WHITE);
	Director::getInstance()->replaceScene(fade);
	// 再生する
	SimpleAudioEngine::sharedEngine()->playEffect("button.mp3");
}
