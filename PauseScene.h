#pragma once
#ifndef __PAUSE_SECEN_H__
#define __PAUSE_SCENE_H__
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "PauseLayer.h"

class PauseScene : public cocos2d::Scene
{
private:
	PauseLayer* pauselayer;
public:
	static PauseScene* create();

	virtual bool init();
};
#endif

