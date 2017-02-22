#include "PauseLayer.h"
#include "StageSelectScene.h"
using namespace CocosDenshion;

USING_NS_CC;
PauseLayer * PauseLayer::create()
{
	PauseLayer *pRet = new(std::nothrow) PauseLayer();
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

bool PauseLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	// 画面サイズの取得
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// 背景レイヤーを作成
	backgroundlayer = BackGroundLayer::create();
	this->addChild(backgroundlayer);

	// タイトルに戻るボタン作成
	auto title = MenuItemImage::create("TitleNormal.png", "TitleSelected.png", CC_CALLBACK_1(PauseLayer::TitleCallback, this));
	title->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 100));
	auto titlemenu = Menu::create(title, NULL);
	titlemenu->setPosition(Vec2::ZERO);
	this->addChild(titlemenu, 4);

	// 戻るボタンを作成
	auto back = MenuItemImage::create("BackNormal.png", "BackSelected.png", CC_CALLBACK_1(PauseLayer::menuCloseCallback, this));
	back->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 100));
	auto backmenu = Menu::create(back, NULL);
	backmenu->setPosition(Vec2::ZERO);
	this->addChild(backmenu, 4);

	// ステージセレクトに戻るボタン作成
	auto stageback = MenuItemImage::create("StageNormal.png", "StageSelected.png", CC_CALLBACK_1(PauseLayer::StageSelectCallback, this));
	stageback->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	auto stagemenu = Menu::create(stageback, NULL);
	stagemenu->setPosition(Vec2::ZERO);
	this->addChild(stagemenu, 4);

	// ポーズラベル作成
	pause_label = Label::createWithTTF("PAUSE", "fonts/uzura.ttf", 80);
	pause_label->setColor(Color3B::YELLOW);
	pause_label->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 200));
	pause_label->enableShadow(Color4B::BLACK, Size(-2, -4), 2);
	this->addChild(pause_label);

	// 効果音をプリロードしておく
	SimpleAudioEngine::sharedEngine()->preloadEffect("button.mp3");
	// 音量を設定
	SimpleAudioEngine::sharedEngine()->setEffectsVolume(1.0f);


	return true;
}

void PauseLayer::menuCloseCallback(cocos2d::Ref * sender)
{
	Director::getInstance()->popScene();
	// 再生する
	SimpleAudioEngine::sharedEngine()->playEffect("button.mp3");
}

void PauseLayer::StageSelectCallback(cocos2d::Ref * sender)
{
	TransitionFade* fade = TransitionFade::create(1.0f, StageSelectScene::create(), Color3B::WHITE);
	Director::getInstance()->replaceScene(fade);
	// 再生する
	SimpleAudioEngine::sharedEngine()->playEffect("button.mp3");
}

void PauseLayer::TitleCallback(cocos2d::Ref * sender)
{
	TransitionFade* fade = TransitionFade::create(2.0f, TitleScene::create(), Color3B::WHITE);
	Director::getInstance()->replaceScene(fade);
	// 再生する
	SimpleAudioEngine::sharedEngine()->playEffect("button.mp3");
}
