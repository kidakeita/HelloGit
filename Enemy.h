#pragma once
#ifndef __ENEMY_H__
#define __ENEMY_H__


#include "cocos2d.h"
#include "ui/CocosGUI.h"

class Enemy :public cocos2d::Node
{
private:
	cocos2d::Sprite* m_enemy;
	
	float m_rad;


public:
	static Enemy* create(float x, float y);

	virtual bool init(float x, float y);

	cocos2d::Sprite* getSprite() { return m_enemy; }

	float getRadians() { return m_rad; }

	void setVelcity(cocos2d::Vec2 velcity);

	cocos2d::Vec2 getVelcity() { return m_velcity; }

	void update(float dt);

	//void setVelcity(cocos2d::Vec2 vel);


	Enemy(float x, float y);

	cocos2d::Vec2 m_velcity;
};
#endif

