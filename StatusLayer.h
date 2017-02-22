#pragma once
#ifndef __STATUS_LAYER_H__
#define __STATUS_LAYER_H__
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "PauseScene.h"
#include "GameLayer.h"


class StatusLayer : public cocos2d::Layer
{
private:
	cocos2d::Sprite* m_icon;
	cocos2d::Sprite* m_timeframe;
	cocos2d::Label* time_label;
	GameLayer* gamelayer;
	float m_time;
	float m_temp;
	char m_str[10];
public:
	static StatusLayer* create();

	virtual bool init();
	
	bool onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * unusedevent);

	void onTouchEnded(cocos2d::Touch * touch, cocos2d::Event * unusedevent);

	void update(float dt);

};
#endif
