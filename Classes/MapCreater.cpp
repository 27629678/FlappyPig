#include "MapCreater.h"
#include "GameScene.h"

USING_NS_CC;
using namespace std;

MapCreater* MapCreater::newMap() {
	MapCreater* pMap = new MapCreater();

	if (pMap && pMap->init()) {
		int index = rand()%4;
		pMap->mapInit(index);

		return pMap;
	}

	CC_SAFE_DELETE(pMap);
	return NULL;
}

void MapCreater::mapInit (int index) {

	CCSize winSize = CCDirector::sharedDirector()->getVisibleSize();

	switch (index)
	{
	case 0:
		upSprite = CCSprite::create ("post_1.png");
		downSprite = CCSprite::create ("post_4.png");
		break;
	case 1:
		upSprite = CCSprite::create ("post_2.png");
		downSprite = CCSprite::create ("post_3.png");
		break;
	case 2:
		upSprite = CCSprite::create ("post_3.png");
		downSprite = CCSprite::create ("post_2.png");
		break;
	default:
		upSprite = CCSprite::create ("post_4.png");
		downSprite = CCSprite::create ("post_1.png");
		break;
	}
	

	upSprite->setPosition(ccp(0, winSize.height - upSprite->getContentSize().height/2));
	this->addChild(upSprite);

	
	downSprite->setPosition(ccp(0, downSprite->getContentSize().height/2));
	this->addChild(downSprite);

	this->scheduleUpdate ();
}

void MapCreater::update (float dt) {
    int framerate = 1/CCDirector::sharedDirector()->getSecondsPerFrame();
    framerate = 60;
    
	this->setPosition(ccpAdd(this->getPosition(), ccp(-200/framerate, 0)));

//	if (this->getPosition().x < - 200) {
//        CCLog("Remove Chile Item.");
//		GameScene::sharedGameManager()->removeChild(this, true);
//	}
}

void MapCreater::onExit () {
	this->unscheduleUpdate ();
	CCLayer::onExit ();
}