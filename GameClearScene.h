#pragma once
#ifndef __GAME_CLEAR_SCENE_H__
#define __GAME_CLEAR_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "BackGroundLayer.h"
#include "SimpleAudioEngine.h"
class GameClearScene : public cocos2d::Scene
{
private:
	cocos2d::Label* game_clear;
	BackGroundLayer* backgroundlayer;
public:
	static cocos2d::Scene* create();

	virtual bool init();

	void StageSelectCallback(cocos2d::Ref * sender);

	void TitleCallback(cocos2d::Ref * sender);
};
#endif

