#pragma once
#ifndef __STAGE_SELECT_SCENE_H__
#define __STAGE_SELECT_SCENE_H__


#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "PlayScene.h"
#include "Stage.h"
#include "BackGroundLayer.h"


class StageSelectScene : public cocos2d::Scene
{
private:
	cocos2d::Sprite* m_easy;
	cocos2d::Sprite* m_normal;
	cocos2d::Sprite* m_hard;
	cocos2d::Label* select_label;
	int m_flag;
	int m_touchflag;
	BackGroundLayer* backgroundlayer;

public:

	static StageSelectScene* create();

	virtual bool init();

	//void TouchEvent(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType type);

	bool onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * unusedevent);
	
	void onTouchEnded(cocos2d::Touch * touch, cocos2d::Event * unusedevent);

};
#endif

