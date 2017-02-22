#pragma once
#ifndef __TITLE_SECEN_H__
#define __TITLE_SCENE_H__
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "BackGroundLayer.h"
#include "SimpleAudioEngine.h"

class TitleScene : public cocos2d::Scene
{
private:
	BackGroundLayer* backgroundlayer;
	cocos2d::Label* touch_label;
	cocos2d::Sprite* m_logo;

public:
	static TitleScene* create();

	virtual bool init();

	bool onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * unusedevent);

	void onTouchEnded(cocos2d::Touch * touch, cocos2d::Event * unusedevent);
};
#endif

