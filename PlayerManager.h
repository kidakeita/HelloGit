#pragma once
#include "Player.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"
class PlayerManager :public cocos2d::Node
{
private:
	Player** m_players;
	cocos2d::Vec2 m_startTouch;
	Player* m_character;
	cocos2d::Sprite* m_arrow;
	Player* player;
	int PlayerNum = 3;
	
public:
	static PlayerManager* create();

	virtual bool init();
	
	void setPlayers(Player** p);

	bool onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * unusedevent);

	void onTouchMoved(cocos2d::Touch * touch, cocos2d::Event * unusedevent);

	void onTouchEnded(cocos2d::Touch * touch, cocos2d::Event * unusedevent);

	void update(float dt);

	PlayerManager();
	~PlayerManager();
};

