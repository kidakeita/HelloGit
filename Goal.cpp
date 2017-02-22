#include "Goal.h"
USING_NS_CC;

Goal * Goal::create(float x, float y)
{
	Goal *pRet = new(std::nothrow) Goal();
	if (pRet && pRet->init(x, y))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = nullptr;
		return nullptr;
	}
}

bool Goal::init(float x, float y)
{
	if (!Node::init())
	{
		return false;
	}
	m_goal = Sprite::create("hole.png");
	m_goal->setPosition(x, y);
	this->addChild(m_goal);

	m_rad = 100.0f / 2.0f;

	scheduleUpdate();
	return true;
}