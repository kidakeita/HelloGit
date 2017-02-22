#include "Enemy.h"
USING_NS_CC;

Enemy * Enemy::create(float x, float y)
{
	Enemy *pRet = new(std::nothrow) Enemy(x, y);
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

bool Enemy::init(float x, float y)
{
	if (!Node::init())
	{
		return false;
	}
	m_enemy = Sprite::create("enemy.png");
	m_enemy->setPosition(x, y);
	this->addChild(m_enemy);

	m_rad = m_enemy->getContentSize().width / 2.0f;

	scheduleUpdate();

	return true;
}



void Enemy::setVelcity(cocos2d::Vec2 velcity)
{
	m_velcity = velcity;
}

void Enemy::update(float dt)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	m_enemy->setPosition(m_enemy->getPosition() + m_velcity);

	m_velcity *= 0.98f;

	float x = m_enemy->getPosition().x;
	float y = m_enemy->getPosition().y;
	
	if (x < m_rad + 40 || x > visibleSize.width - m_rad - 40)
	{
		m_velcity.x *= -0.98f;
	}
	if (y < m_rad + 45 || y > visibleSize.height - m_rad - 55)
	{
		m_velcity.y *= -0.98f;
	}
}

Enemy::Enemy(float x, float y)
{
}
