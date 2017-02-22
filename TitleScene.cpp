#include "TitleScene.h"
#include "StageSelectScene.h"
using namespace CocosDenshion;
USING_NS_CC;


TitleScene * TitleScene::create()
{
	TitleScene *pRet = new(std::nothrow) TitleScene();
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

bool TitleScene::init()
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
	this->addChild(backgroundlayer);

	// イベントリスナーを作成
	EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
	// イベントリススナーに各コールバック関数をセットする
	listener->onTouchBegan = CC_CALLBACK_2(TitleScene::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(TitleScene::onTouchEnded, this);
	// イベントリスナーを登録する
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	// スタートラベル作成
	touch_label = Label::createWithTTF("TOUCH to START", "fonts/uzura.ttf", 80);
	touch_label->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 230));
	touch_label->enableShadow(Color4B::BLACK, Size(-2, -4), 2);
	this->addChild(touch_label);

	// ラベルフェードアウト処理
	FadeOut* action1 = FadeOut::create(1.0f);
	FadeIn* action2 = FadeIn::create(1.0f);
	Sequence* seq = Sequence::create(action1, action2, nullptr);
	RepeatForever* rep = RepeatForever::create(seq);
	touch_label->runAction(rep);

	m_logo = Sprite::create("Titlelogo.png");
	m_logo->setPosition(visibleSize.width / 2, visibleSize.height / 2 - 50);
	this->addChild(m_logo);

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

	return true;
}

bool TitleScene::onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * unusedevent)
{
	TransitionFade* fade = TransitionFade::create(1.0f, StageSelectScene::create(), Color3B::WHITE);
	Director::getInstance()->replaceScene(fade);
	// 再生する
	SimpleAudioEngine::sharedEngine()->playEffect("button.mp3");
	return true;
}

void TitleScene::onTouchEnded(cocos2d::Touch * touch, cocos2d::Event * unusedevent)
{
}
