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
	this->addChild(pUIScene, 100);

    iscollision     = false;
    iscollision_x   = false;
    iscollision_uy  = false;
    iscollision_dy  = false;
    
    velocity_y_delta = 50.0f/60;
    
	this->createPost(0);
    
    scheduleUpdate();
	schedule(schedule_selector(GameScene::createPost), 2);

	return true;
}

bool GameScene::ccTouchBegan (CCTouch* touch, CCEvent* touchEvent) {
	isPresingScreen = true;
    velocity_y = 4 * 1.0f/60 * PLAYER_VERTICAL_VELOCITY;
	return true;
}

void GameScene::ccTouchMoved (CCTouch* touch, CCEvent* touchEvent) {
    velocity_y = 4 * 1.0f/60 * PLAYER_VERTICAL_VELOCITY;
	isPresingScreen = true;
}

void GameScene::ccTouchEnded (CCTouch* touch, CCEvent* touchEvent) {
    velocity_y = 1.0f/60 * PLAYER_VERTICAL_VELOCITY;
	isPresingScreen = false;
}

void GameScene::update(float dt) {
    int framerate = 60;
    
	if (arrayPost == NULL) return;
    
    velocity_x = 1.0f/framerate * PLAYER_HORIZONTAL_VELOCITY;
    
    float player_speed_x = velocity_x;
    float player_speed_y = velocity_y;
    
    CCSize winSize = CCDirector::sharedDirector()->getVisibleSize();
    
    if (arrayPost->count() > 0) {
        for (int i = 0; i != arrayPost->count(); i ++) {
            if (arrayPost->objectAtIndex(i) != NULL) {
                MapCreater* pMap = (MapCreater*)arrayPost->objectAtIndex(i);
                
                if (pMap->getPosition().x < - 200) {
                    arrayPost->removeObjectAtIndex(i);
                    
                    this->removeChild(pMap);
                    CCLog("Remove Chile Item.");
                    
                    i --;
                    CC_SAFE_DELETE(pMap);
                    continue;
                }
                
                iscollision     = false;
                iscollision_x   = false;
                iscollision_uy  = false;
                iscollision_dy  = false;
                
                CCRect upRect   = CCRect(pMap->getPosition().x - 90, winSize.height - pMap->upSprite->getContentSize().height, pMap->upSprite->getContentSize().width, pMap->upSprite->getContentSize().height);
                CCRect downRect = CCRect(pMap->getPosition().x - 90, 0, pMap->upSprite->getContentSize().width, pMap->downSprite->getContentSize().height);
                
                CCRect playerRect = player->boundingBox();
                
                if (playerRect.intersectsRect(upRect)) {
                    iscollision = true;
                    
                    float point_x = playerRect.origin.x + playerRect.size.width;
                    float point_uy = playerRect.origin.x + playerRect.size.height;
                    
                    if (point_x <= upRect.origin.x + 30) {
                        iscollision_x = true;
                    }
                    else
                    {
                        if (point_uy >= upRect.origin.y) {
                            
                            iscollision_uy = true;
                        }
                    }
                    
                    break;
                }
                
                if (player->boundingBox().intersectsRect(downRect)) {
                    iscollision = true;
                    
                    float point_x = playerRect.origin.x + playerRect.size.width;
                    float point_dy = playerRect.origin.y;
                    
                    if (point_x <= downRect.origin.x + 30) {
                        iscollision_x = true;
                    }
                    else
                    {
                        if (point_dy <= downRect.origin.y + downRect.size.height) {
                            iscollision_dy = true;
                        }
                    }
                    
                    break;
                }
            }
            else {
                arrayPost->removeObjectAtIndex(i);
            }
        }
    }
    
    if (iscollision_x) {
        player_speed_x = - 1.0f/framerate * PLAYER_HORIZONTAL_VELOCITY;
    }
    
    if (iscollision_uy) {
        player_speed_y = 0;
    }
    
    if (iscollision_dy) {
        player_speed_y = 0;
    }
    
    if (isPresingScreen == true)
    {
		if (player->getPosition ().x < 960 - player->getContentSize().width/2) {
            //  主角不能飞出屏幕高度以外
			if (player->getPosition().y >= 640 - player->getContentSize().height/2) {
				player_speed_y = 0;
			}
            
            if (iscollision_dy && !iscollision_uy) {
                player_speed_y = velocity_y;
            }
            
			player->setPosition(ccpAdd(player->getPosition(), ccp(player_speed_x, player_speed_y)));
		}
		else {
            if (!iscollision) {
                player->setPosition(ccp(900 - player->getContentSize().width/2, player->getPosition().y));
            }
		}
	}
	else
	{
        player_speed_x = 0;
        
        if (iscollision) {
            player_speed_x = - 1.0f/framerate * PLAYER_HORIZONTAL_VELOCITY;
        }
        
        if (!iscollision_dy) {
            velocity_y += velocity_y_delta;
            player_speed_y = velocity_y;
        }
        
		if (player->getPosition().y - 2 <= player->getContentSize().height/2) {
			player_speed_y = 0;
		}
        
		player->setPosition(ccpAdd(player->getPosition(), ccp(player_speed_x, -player_speed_y)));
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
