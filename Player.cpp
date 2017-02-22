#include "Player.h"
USING_NS_CC;


Player * Player::create(float x, float y)
{
	Player *pRet = new(std::nothrow) Player(x, y);
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

bool Player::init(float x, float y)
{
	if (!Node::init())
	{
		return false;
	}

	m_image = Sprite::create("Rocket2.png");
	//this->setScale(0.5f);
	this->setPosition(x, y);
	this->addChild(m_image);

	/*m_arrow = Sprite::create("arrow.png");
	m_arrow->setOpacity(0);
	this->addChild(m_arrow);*/

	// 画像の半径
	m_rad = 80.0f / 2.0f;

	//// イベントリスナーを作成
	//EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
	//// イベントリススナーに各コールバック関数をセットする
	//listener->onTouchBegan = CC_CALLBACK_2(Player::onTouchBegan, this);
	//listener->onTouchMoved = CC_CALLBACK_2(Player::onTouchMoved, this);
	//listener->onTouchEnded = CC_CALLBACK_2(Player::onTouchEnded, this);
	//// イベントリスナーを登録する
	//this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	scheduleUpdate();


	return true;
}

void Player::update(float dt)
{

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->setPosition(this->getPosition() + m_velcity);

	m_velcity *= 0.98f;

	float x = this->getPosition().x;
	float y = this->getPosition().y;

	if (x < m_rad + 40  || x > visibleSize.width - m_rad - 40)
	{
		m_velcity.x *= -0.98f;
	}
	if (y < m_rad + 45  || y >visibleSize.height - m_rad - 55)
	{
		m_velcity.y *= -0.98f;
	}

	m_touchflag = true;

}

void Player::setVelcity(Vec2 velcity)
{
	m_velcity = velcity;
}



//bool Player::onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * unusedevent)
//{
//	// プレイヤーの画像の半径をとってくる
//	float r = m_rad;
//
//	// 二つのポジションの差を出す
//	Vec2 range = m_image->getPosition() - touch->getLocation();
//
//	// 差を二乗したものと半径を二乗したものを比べる
//	if (range.x * range.x + range.y * range.y <= r * r)
//	{
//		return true;
//	}
//	
//	return false;
//
//}
//
//void Player::onTouchMoved(cocos2d::Touch * touch, cocos2d::Event * unusedevent)
//{
//	m_arrow->setOpacity(255);
//	m_arrow->setPosition(m_image->getPosition());
//	m_arrow->setAnchorPoint(Vec2(0.5f, 0));
//
//	float angle = atan2(m_image->getPosition().x - touch->getLocation().x, m_image->getPosition().y - touch->getLocation().y);
//	angle = angle * 180 / 3.14f;
//	m_arrow->setRotation(angle);
//}
//
//void Player::onTouchEnded(cocos2d::Touch * touch, cocos2d::Event * unusedevent)
//{
//	// タッチしたキャラからタッチしている位置を引いて、タッチしている位置からタッチされたキャラに向かうベクトルを出している
//	m_velcity = (m_image->getPosition() - touch->getLocation()) * 0.1f;
//	m_arrow->setOpacity(0);
//}

Player::Player(float x, float y)
{

}


Player::~Player()
{
}