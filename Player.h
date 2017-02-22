#pragma once
#ifndef __PLAYER_H__
#define __PLAYER_H__


#include "cocos2d.h"
#include "ui/CocosGUI.h"

class Player :public cocos2d::Node
{
private:
	cocos2d::Sprite* m_image;
	cocos2d::Sprite* m_arrow;
	cocos2d::Vec2 m_startTouch;
	cocos2d::Vec2 m_velcity;
	float m_rad;


public:
	static Player* create(float x, float y);

	virtual bool init(float x, float y);

	cocos2d::Sprite* getSprite() { return m_image; }

	float getRadians() { return m_rad; }

	void update(float dt);

	void setVelcity(cocos2d::Vec2 velcity);

	cocos2d::Vec2 getVelcity() { return m_velcity; }

	bool m_touchflag = false;

	//bool onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * unusedevent);

	//void onTouchMoved(cocos2d::Touch * touch, cocos2d::Event * unusedevent);

	//void onTouchEnded(cocos2d::Touch * touch, cocos2d::Event * unusedevent);

	Player(float x,float y);
	~Player();

	

	
};
#endif

