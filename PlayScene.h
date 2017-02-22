#pragma once
#ifndef __PLAY_SCENE_H__
#define __PLAY_SCENE_H__
#include "cocos2d.h"
#include "GameLayer.h"
#include "BackGroundLayer.h"
#include "StatusLayer.h"

class PlayScene : public cocos2d::Scene
{
private:
	BackGroundLayer* backgroundlayer;
	StatusLayer* statuslayer;
	GameLayer* gamelayer;
public:
	static PlayScene* create();

	virtual bool init();
};
#endif // __PLAY_SCENE_H__
