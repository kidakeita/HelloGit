#include "PlayScene.h"

PlayScene * PlayScene::create()
{
	PlayScene *pRet = new(std::nothrow) PlayScene();
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

bool PlayScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	// たぬきレイヤーを作成
	backgroundlayer = BackGroundLayer::create();
	this->addChild(backgroundlayer);
	// ステータスレイヤーを作成
	statuslayer = StatusLayer::create();
	this->addChild(statuslayer);
	// ゲームレイヤーを作成
	gamelayer = GameLayer::create();
	this->addChild(gamelayer);

	return true;
}
