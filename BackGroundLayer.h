#pragma once
#ifndef __BACK_GROUND_LAYER_H__
#define __BACK_GROUND_LAYER_H__
#include "cocos2d.h"
#include "ui/CocosGUI.h"

class BackGroundLayer :public cocos2d::Layer
{
private:
	cocos2d::Sprite* m_background;
	cocos2d::Sprite* m_ufo;
	float m_x;
	float m_y;

	int usako = 0;

public:
	static BackGroundLayer* create();
	
	virtual bool init();

	void setAction();

	void update(float dt);
};
#endif

