#include "PlayerManager.h"
USING_NS_CC;
#define PI 3.14f

PlayerManager * PlayerManager::create()
{
	PlayerManager *pRet = new(std::nothrow) PlayerManager();
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

bool PlayerManager::init()
{
	if (!Node::init())
	{
		return false;
	}

	//for (int i = 0; i < 3; i++)
	//{
	//	// プレイヤーを作る
	//	player[i] = Player::create(random(0, 600), random(0, 600));
	//	this->addChild(player[i]);
	//}
	//this->setPlayers(&player[0]);

	// イベントリスナーを作成
	EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
	// イベントリススナーに各コールバック関数をセットする
	listener->onTouchBegan = CC_CALLBACK_2(PlayerManager::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(PlayerManager::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(PlayerManager::onTouchEnded, this);
	// イベントリスナーを登録する
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	m_arrow = Sprite::create("arrow.png");
	m_arrow->setOpacity(0);
	this->addChild(m_arrow);

	//for (int i = 0; i < PlayerNum; i++)
	//{
	//	p = m_players[i];
	//}

	scheduleUpdate();


	return true;
}

void PlayerManager::setPlayers(Player ** p)
{
	m_players = p;
}

bool PlayerManager::onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * unusedevent)
{

		for (int i = 0; i < PlayerNum; i++)
		{
			m_character = m_players[0];

			// プレイヤーの画像の半径をとってくる
			float r = m_character->getRadians();

			// 二つのポジションの差を出す
			Vec2 range = m_character->getPosition() - touch->getLocation();

			// 差を二乗したものと半径を二乗したものを比べる
			if (range.x * range.x + range.y * range.y <= r * r )
			{
				return true;
			}
		}
	
	
	return false;


}

void PlayerManager::onTouchMoved(cocos2d::Touch * touch, cocos2d::Event * unusedevent)
{
	//p->getSprite()->setPosition(touch->getLocation().x, touch->getLocation().y);

	m_arrow->setOpacity(255);
	m_arrow->setPosition(m_character->getPosition());
	m_arrow->setAnchorPoint(Vec2(0.5f, 0));

	float angle = atan2(m_character->getPosition().x - touch->getLocation().x, m_character->getPosition().y - touch->getLocation().y);
	angle = angle * 180 / PI;
	m_arrow->setRotation(angle);
	m_character->setRotation(angle);

	Vec2 range = m_character->getPosition() - touch->getLocation();

	float distance = range.x * range.x + range.y * range.y;

	m_arrow->setScaleY(distance*0.00006f);

}

void PlayerManager::onTouchEnded(cocos2d::Touch * touch, cocos2d::Event * unusedevent)
{
	// タッチしたキャラからタッチしている位置を引いて、タッチしている位置からタッチされたキャラに向かうベクトルを出している
	Vec2 vel = (m_character->getPosition() - touch->getLocation()) * 0.1f;
	m_character->setVelcity(vel);
	m_arrow->setOpacity(0);
	
}

void PlayerManager::update(float dt)
{	
	

}


PlayerManager::PlayerManager()
{
	

}


PlayerManager::~PlayerManager()
{
}
