#pragma once
#ifndef __GAME_LAYER_H__
#define __GAME_LAYER_H__
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Player.h"
#include "Enemy.h"
#include "PlayerManager.h"
#include "Goal.h"
#include "GameOverScene.h"
#include "GameClearScene.h"
#include "Stage.h"

enum {
	Easy   = 1,
	Normal = 2,
	Hard   = 3
};

enum {
	STAGE1 = 1,
	STAGE2 = 2,
	STAGE3 = 3,
};

class GameLayer :public cocos2d::Layer
{
private:
	PlayerManager* manager;
	Player* player;
	Enemy* enemy[3];
	Goal* goal[4];
	int PlayerNum = 1;
	int GoalNum;
	int EnemyNum;
	int m_posflag;
	int m_nextflag;
	int m_hitcount;
	
	cocos2d::TransitionFade* fade;

public:
	int m_count;

	virtual bool init();

	void update(float dt);

	CREATE_FUNC(GameLayer);
};
#endif

