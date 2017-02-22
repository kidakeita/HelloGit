#pragma once
#ifndef __PAUSE_LAYER_H__
#define __PAUSE_LAYER_H__
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "BackGroundLayer.h"
#include "Stage.h" 
#include "TitleScene.h"
#include "SimpleAudioEngine.h"

class PauseLayer : public cocos2d::Layer
{
private:
	BackGroundLayer* backgroundlayer;
	cocos2d::Label* pause_label;
public:
	static PauseLayer* create();

	virtual bool init();

	void menuCloseCallback(cocos2d::Ref * sender);

	void StageSelectCallback(cocos2d::Ref * sender);

	void TitleCallback(cocos2d::Ref * sender);
};
#endif

