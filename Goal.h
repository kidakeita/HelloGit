#pragma once
#ifndef __GOAL_H__
#define __GOAL_H__
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Player.h"

class Goal :public cocos2d::Node
{
private:
	cocos2d::Sprite* m_goal;
	Player* player;
	float m_rad;
public:
	static Goal* create(float x, float y);

	virtual bool init(float x, float y);

	float getRadians() { return m_rad; }

	cocos2d::Sprite* getSprite() { return m_goal; }
};
#endif 

