#include "GameLayer.h"
#include "StageSelectScene.h"
#include "PlayScene.h"
#include "cocostudio/CocoStudio.h"
using namespace CocosDenshion;

USING_NS_CC;

bool GameLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	// 変数初期化
	m_hitcount = 0;

	m_posflag = 0;

	// 画面サイズ取得
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// プレイヤーを作成
	player = Player::create(480.0f, 200.0f);
	this->addChild(player);
	// プレイヤーマネージャーを作成
	manager = PlayerManager::create();
	manager->setPlayers(&player);
	this->addChild(manager);

	switch (Stage::m_flag)
	{
	// Easyステージを作成
	case Easy:
		// エネミーを作成
		EnemyNum = 1;
		switch (Stage::m_nextflag)
		{
		case STAGE1:
			enemy[0] = Enemy::create(540.0f, 400.0f);
			break;
		case STAGE2:
			enemy[0] = Enemy::create(240.0f, 400.0f);
			break;
		case STAGE3:
			enemy[0] = Enemy::create(640.0f, 240.0f);
			break;
		}
		this->addChild(enemy[0]);

		GoalNum = 4;
		for (int k = 0; k < GoalNum; k++)
		{
			m_posflag++;
			switch (m_posflag)
			{
			case 1:
				goal[k] = Goal::create(75.0f, 530.0f);
				break;
			case 2:
				goal[k] = Goal::create(880.0f, 530.0f);
				break;
			case 3:
				goal[k] = Goal::create(75.0f, 100.0f);
				break;
			case 4:
				goal[k] = Goal::create(880.0f, 100.0f);
				break;
			}
			this->addChild(goal[k]);
		}
		break;
	// Normalステージを作成
	case Normal:
		// エネミーを作成
		EnemyNum = 2;
		switch (Stage::m_nextflag)
		{
		case STAGE1:
			enemy[0] = Enemy::create(750.0f, 480.0f);
			enemy[1] = Enemy::create(190.0f, 100.0f);
			break;
		case STAGE2:
			enemy[0] = Enemy::create(320.0f, 400.0f);
			enemy[1] = Enemy::create(680.0f, 200.0f);
			break;
		case STAGE3:
			enemy[0] = Enemy::create(320.0f, 200.0f);
			enemy[1] = Enemy::create(600.0f, 200.0f);
			break;	
		}
		this->addChild(enemy[0]);
		this->addChild(enemy[1]);
			
		// ゴールを作成
		GoalNum = 2;
		for (int i = 0; i < GoalNum; i++)
		{
			if (i % 2)
			{
				goal[i] = Goal::create(880.0f, 530.0f);
				this->addChild(goal[i]);
			}
			else
			{
				goal[i] = Goal::create(75.0f, 100.0f);
				this->addChild(goal[i]);
			}
		}
		break;
	// Hardステージを作成
	case Hard:
		switch (Stage::m_nextflag)
		{
			case STAGE1:
				EnemyNum = 1;
				enemy[0] = Enemy::create(750.0f, 480.0f);
				break;
			case STAGE2:
				EnemyNum = 2;
				enemy[0] = Enemy::create(320.0f, 300.0f);
				enemy[1] = Enemy::create(540.0f, 400.0f);
				this->addChild(enemy[1]);
				break;
			case STAGE3:
				EnemyNum = 3;
				enemy[0] = Enemy::create(370.0f, 300.0f);
				enemy[1] = Enemy::create(630.0f, 400.0f);
				enemy[2] = Enemy::create(500.0f, 500.0f);
				this->addChild(enemy[1]);
				this->addChild(enemy[2]);
				break;
		}
		this->addChild(enemy[0]);
		
		GoalNum = 3;
		for (int k = 0; k < GoalNum; k++)
		{
			m_posflag++;
			switch (m_posflag)
			{
			case 1:
				goal[k] = Goal::create(75.0f, 530.0f);
				break;
			case 2:
				goal[k] = Goal::create(75.0f, 100.0f);
				break;
			case 3:
				goal[k] = Goal::create(880.0f, 100.0f);
				break;
			}
			this->addChild(goal[k]);
		}
		break;
	}
	// BGMをプリロードしておく
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("BGM2.mp3");
	// 音量を設定
	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(1.0f);
	if (Stage::m_nextflag == 1)
	{
		// 再生する
		SimpleAudioEngine::getInstance()->playBackgroundMusic("BGM2.mp3", true);
	}

	// 効果音をプリロードしておく
	SimpleAudioEngine::sharedEngine()->preloadEffect("attack.mp3");
	SimpleAudioEngine::sharedEngine()->preloadEffect("warp.mp3");
	// 音量を設定
	SimpleAudioEngine::sharedEngine()->setEffectsVolume(1.5f);


	// Update関数を呼ぶ
	scheduleUpdate();

	return true;
}

void GameLayer::update(float dt)
{
	// プレイヤーのポジション取得
	float x = player->getPosition().x;
	float y = player->getPosition().y;
	//	プレイヤーとエネミーの当たり判定
	for (int i = 0; i < EnemyNum; i++)
	{
		// エネミーのポジション取得
		float x2 = enemy[i]->getSprite()->getPosition().x;
		float y2 = enemy[i]->getSprite()->getPosition().y;

		// プレイヤーとエネミーの二つの距離を測る
		float distance = (float)(sqrt((x2 - x)*(x2 - x) + (y2 - y)*(y2 - y)));

		// その距離がプレイヤーの半径とエネミーの半径を足して大きかったら当たる
		if (distance <= player->getRadians() + enemy[i]->getRadians())
		{
			player->setVelcity(player->getVelcity() * -0.98f);
			enemy[i]->setVelcity(player->getVelcity() * -0.98f);
			// 再生する
			SimpleAudioEngine::sharedEngine()->playEffect("attack.mp3");
		}
		// エネミーと別エネミーの当たり判定
		for (int j = 0; j < EnemyNum; j++)
		{
			// 別エネミーとの区別
			if (enemy[i] != enemy[j])
			{
				// 別エネミーのポジション取得
				float x3 = enemy[j]->getSprite()->getPosition().x;
				float y3 = enemy[j]->getSprite()->getPosition().y;

				// エネミーと別エネミーの二つの距離を測る
				float distance2 = (float)(sqrt((x3 - x2)*(x3 - x2) + (y3 - y2)*(y3 - y2)));

				// その距離がエネミーの半径と別エネミーの半径を足して大きかったら当たる
				if (distance2 <= enemy[i]->getRadians() + enemy[j]->getRadians())
				{
					enemy[i]->setVelcity(enemy[i]->getVelcity() * -0.98f);
					enemy[j]->setVelcity(player->getVelcity() * -0.98f);
					// 再生する
					SimpleAudioEngine::sharedEngine()->playEffect("attack.mp3");
				}
			}
		}

		// プレイヤー、エネミーとゴールの当たり判定
		for (int k = 0; k < GoalNum; k++)
		{
			// ゴールのポジション取得
			float x4 = goal[k]->getSprite()->getPosition().x;
			float y4 = goal[k]->getSprite()->getPosition().y;

			// プレイヤーとゴールの二つの距離を測る
			float distance3 = (float)(sqrt((x4 - x)*(x4 - x) + (y4 - y)*(y4 - y)));
			
			// その距離がプレイヤーの半径とゴールの半径を足して大きかったら当たる
			if (distance3 <= player->getRadians() + goal[k]->getRadians())
			{
				if (m_count == 0)
				{
					player->setPosition(-1000, -1000);
					TransitionFadeTR* fade = TransitionFadeTR::create(1.0f, GameOverScene::create());
					Director::getInstance()->replaceScene(fade);
					Stage::m_nextflag = 1;
					// 再生する
					SimpleAudioEngine::sharedEngine()->playEffect("warp.mp3");
					m_count = 1;
				}
			}
			// エネミーとプレイヤーの二つの距離を測る
			float distance4 = (float)(sqrt((x4 - x2)*(x4 - x2) + (y4 - y2)*(y4 - y2)));

			// その距離がエネミーの半径とゴールの半径を足して大きかったら当たる
			if (distance4 <= enemy[i]->getRadians() + goal[k]->getRadians())
			{
				m_hitcount++;
				enemy[i]->getSprite()->setPosition(random(-1000, -500), random(-1000, -300));
				// 再生する
				SimpleAudioEngine::sharedEngine()->playEffect("warp.mp3");
				switch (Stage::m_flag)
				{
				case Easy:
					if (m_count == 0)
					{
						Stage::m_nextflag += 1;
						if (Stage::m_nextflag != 4)
						{
							TransitionFade* fade = TransitionFade::create(0.5f, PlayScene::create(), Color3B::WHITE);
							Director::getInstance()->replaceScene(fade);
							player->setVelcity(player->getVelcity() * 0);
						}
						else
						{
							TransitionFade* fade = TransitionFade::create(0.5f, GameClearScene::create(), Color3B::WHITE);
							Director::getInstance()->replaceScene(fade);
							Stage::m_nextflag = 1;
						}
						m_count = 1;
					}
					break;
				case Normal:
					if (m_hitcount == 2)
					{
						if (m_count == 0)
						{
							Stage::m_nextflag += 1;
							if (Stage::m_nextflag != 4)
							{
								TransitionFade* fade = TransitionFade::create(0.5f, PlayScene::create(), Color3B::WHITE);
								Director::getInstance()->replaceScene(fade);
								player->setVelcity(player->getVelcity() * 0);
							}
							else
							{
								TransitionFade* fade = TransitionFade::create(0.5f, GameClearScene::create(), Color3B::WHITE);
								Director::getInstance()->replaceScene(fade);
								Stage::m_nextflag = 1;
							}
							m_count = 1;
						}
					}
					break;
				case Hard:
					switch (Stage::m_nextflag)
					{
					case STAGE1:
						if (m_count == 0)
						{
							Stage::m_nextflag += 1;
							fade = TransitionFade::create(0.5f, PlayScene::create(), Color3B::WHITE);
							Director::getInstance()->replaceScene(fade);
							player->setVelcity(player->getVelcity() * 0);
							m_count = 1;
						}
						break;
					case STAGE2:
						if (m_hitcount == 2)
						{
							Stage::m_nextflag += 1;
							TransitionFade* fade = TransitionFade::create(0.5f, PlayScene::create(), Color3B::WHITE);
							Director::getInstance()->replaceScene(fade);
							player->setVelcity(player->getVelcity() * 0);
						}
						break;
					case STAGE3:
						if (m_hitcount == 3)
						{
							Stage::m_nextflag += 1;
							TransitionFade* fade = TransitionFade::create(0.5f, GameClearScene::create(), Color3B::WHITE);
							Director::getInstance()->replaceScene(fade);
							player->setVelcity(player->getVelcity() * 0);
							Stage::m_nextflag = 1;
						}
						break;
					}
					break;
				}
			}
		}
	}
}