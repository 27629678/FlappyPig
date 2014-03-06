#include "GameScene.h"
#include "MapBase.h"
#include "UIBase.h"
#include "MapCreater.h"
#include "UtilsMacro.h"

USING_NS_CC;
using namespace std;

static GameScene* sInstance;

GameScene* GameScene::sharedGameManager () {
	if (sInstance != NULL)
	{
		return sInstance;
	}

	return NULL;
}

CCScene* GameScene::scene () {
	CCScene* pScene = CCScene::create ();
	GameScene* pLayer = GameScene::create ();
	pScene->addChild(pLayer);

	return pScene;
}

void GameScene::onEnter () {
	isPresingScreen = false;
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, false);
	CCLayer::onEnter();
}

bool GameScene::init () {
	if (!CCLayer::init ()) {
		return false;
	}

	sInstance = this;
	arrayPost = CCArray::create();
	CC_SAFE_RETAIN(arrayPost);

	//	Background
	MapBase::create (this, "background.png", CCRect(0, 0, 960, 640));

	//	Player
	player = CCSprite::create("Play_Nor.png");
	player->setPosition(ccp(ORIGINAL_POSITION_X, ORIGINAL_POSITION_Y));
	this->addChild(player);

	CCScene* pUIScene = UIBase::scene ();
	this->addChild(pUIScene);

	this->createPost(0);
	
	schedule(schedule_selector(GameScene::myUpdate));
	//schedule(schedule_selector(GameScene::createPost), 6);
	scheduleUpdate();

	return true;
}

bool GameScene::ccTouchBegan (CCTouch* touch, CCEvent* touchEvent) {
	isPresingScreen = true;
	return true;
}

void GameScene::ccTouchMoved (CCTouch* touch, CCEvent* touchEvent) {
	isPresingScreen = true;
}

void GameScene::ccTouchEnded (CCTouch* touch, CCEvent* touchEvent) {
	isPresingScreen = false;
}

void GameScene::update(float dt) {
	if (arrayPost == NULL) return;

	for (int i = 0; i != arrayPost->count(); i ++) {
		if (arrayPost->objectAtIndex(i) != NULL) {
			MapCreater* pMap = (MapCreater*)arrayPost->objectAtIndex(i);
			if (player->boundingBox().intersectsRect(pMap->upSprite->boundingBox())
				|| player->boundingBox().intersectsRect(pMap->downSprite->boundingBox())) {
				CCLOG("Touch,%d",i);
				CCLOG("(%f,%f)&(%f,%f)-(%f,%f)",player->getPosition().x, player->getPosition().y, pMap->upSprite->getPosition().x,pMap->upSprite->getPosition().y, pMap->downSprite->getPosition().x, pMap->downSprite->getPosition().y);
				return;
			}
		}
		else
		{
			arrayPost->removeObjectAtIndex(i);
		}
	}
}

void GameScene::myUpdate(float dt) {
	if (isPresingScreen == true) {
		if (player->getPosition ().x < 960 - player->getContentSize().width/2) {
			float velocity_x = 100.0f/60, velocity_y = 100.0f/60;
			if (player->getPosition().y >= 640 - player->getContentSize().height/2) {
				velocity_y = 0;
			}
			player->setPosition(ccpAdd(player->getPosition(), ccp(velocity_x,velocity_y)));
		}
		else
		{
			player->setPosition(ccp(player->getContentSize().width/2, 320));
		}
	}
	else
	{
		float velocity_x = 0, velocity_y = 100.0f/60;
		if (player->getPosition().y <= player->getContentSize().height/2) {
            velocity_x = 0;
			velocity_y = 0;
		}
		player->setPosition(ccpAdd(player->getPosition(), ccp(0, -velocity_y)));
	}
}

void GameScene::createPost (float dt) {
	MapCreater* pMap = MapCreater::newMap();
	pMap->setPosition(ccp(960 + 80, 0));
	arrayPost->addObject(pMap);
	this->addChild(pMap);
}

void GameScene::onExit () {
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	CCLayer::onExit();
}
