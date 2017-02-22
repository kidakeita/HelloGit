#include "BackGroundLayer.h"
USING_NS_CC;


BackGroundLayer * BackGroundLayer::create()
{
	BackGroundLayer *pRet = new(std::nothrow) BackGroundLayer();
	if (pRet && pRet->init())
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

bool BackGroundLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	// 画面サイズ取得
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	m_background = Sprite::create("frame.png");
	m_background->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(m_background,1);

	ParticleSystemQuad* particle = ParticleSystemQuad::create("particle_texture.plist");
	particle->resetSystem();
	particle->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(particle);

	return true;
}

void BackGroundLayer::setAction()
{
	m_ufo = Sprite::create("ufo.png");
	m_ufo->setPosition(-150, -150);
	this->addChild(m_ufo, 0);

	scheduleUpdate();
}

void BackGroundLayer::update(float dt)
{
	m_x++;
	m_y++;
	m_ufo->setPosition(m_x, m_y);
}
