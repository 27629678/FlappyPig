#include "MapBase.h"

USING_NS_CC;
using namespace std;

cocos2d::CCSprite* MapBase::create (cocos2d::CCLayer* layer, const char* spritename, CCRect rect) {
	
	CCSize winSize = CCDirector::sharedDirector()->getVisibleSize ();
	
	CCSprite* pSprite = CCSprite::create (spritename, rect);
	pSprite->setPosition (ccp(winSize.width/2, winSize.height/2));
	
	if (layer != NULL) {
		layer->addChild(pSprite);
	}

	return pSprite;
}