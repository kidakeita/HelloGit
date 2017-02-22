#include "GameClearScene.h"
#include "StageSelectScene.h"
#include "TitleScene.h"
using namespace CocosDenshion;
USING_NS_CC;

cocos2d::Scene * GameClearScene::create()
{
	GameClearScene *pRet = new(std::nothrow) GameClearScene();
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

bool GameClearScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	// 画面サイズ取得
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// 背景レイヤーを作成
	backgroundlayer = BackGroundLayer::create();
	this->addChild(backgroundlayer);

	// タイトルに戻るボタン作成
	auto title = MenuItemImage::create("TitleNormal.png", "TitleSelected.png", CC_CALLBACK_1(GameClearScene::TitleCallback, this));
	title->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 100));
	auto titlemenu = Menu::create(title, NULL);
	titlemenu->setPosition(Vec2::ZERO);
	this->addChild(titlemenu, 4);

	// ステージセレクトに戻るボタン作成
	auto stageback = MenuItemImage::create("StageNormal.png", "StageSelected.png", CC_CALLBACK_1(GameClearScene::StageSelectCallback, this));
	stageback->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	auto stagemenu = Menu::create(stageback, NULL);
	stagemenu->setPosition(Vec2::ZERO);
	this->addChild(stagemenu, 4);

	// ゲームクリアラベル作成
	game_clear = Label::createWithTTF("GAME CLEAR", "fonts/uzura.ttf", 100);
	game_clear->setColor(Color3B::YELLOW);
	game_clear->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 200));
	game_clear->enableShadow(Color4B::BLACK, Size(-2, -4), 2);
	this->addChild(game_clear);

	// 効果音をプリロードしておく
	SimpleAudioEngine::sharedEngine()->preloadEffect("button.mp3");
	// 音量を設定
	SimpleAudioEngine::sharedEngine()->setEffectsVolume(1.0f);
	return true;
}

void GameClearScene::StageSelectCallback(cocos2d::Ref * sender)
{
	TransitionFade* fade = TransitionFade::create(1.0f, StageSelectScene::create(), Color3B::WHITE);
	Director::getInstance()->replaceScene(fade);
	// 再生する
	SimpleAudioEngine::sharedEngine()->playEffect("button.mp3");
}

void GameClearScene::TitleCallback(cocos2d::Ref * sender)
{
	TransitionFade* fade = TransitionFade::create(1.0f, TitleScene::create(), Color3B::WHITE);
	Director::getInstance()->replaceScene(fade);
	// 再生する
	SimpleAudioEngine::sharedEngine()->playEffect("button.mp3");
}
