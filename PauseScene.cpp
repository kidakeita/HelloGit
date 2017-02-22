#include "PauseScene.h"

USING_NS_CC;
PauseScene * PauseScene::create()
{
	PauseScene *pRet = new(std::nothrow) PauseScene();
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

bool PauseScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	pauselayer = PauseLayer::create();
	this->addChild(pauselayer);
	return true;
}
