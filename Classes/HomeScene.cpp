#include "HomeScene.h"
#include "GameScene.h"

using namespace std;
using namespace cocos2d;

CCScene* HomeScene::scene () {
	CCScene* pScene = CCScene::create ();
	HomeScene* pLayer = HomeScene::create ();
	pScene -> addChild (pLayer);

	return pScene;
}

bool HomeScene::init () {
	if (!CCLayer::init ()) {
		return false;
	}

	CCSize winSize = CCDirector::sharedDirector()->getVisibleSize();

	//	Background
	CCSprite* background = CCSprite::create ("Background_HomeScene.png");
	background->setPosition (ccp(winSize.width/2, winSize.height/2));
	this -> addChild (background);
	
	//	Play Button
	CCMenuItemImage* playButton = CCMenuItemImage::create (
		"Button_Start.png",
		"Button_Start.png",
		this,
		menu_selector(HomeScene::playButtonAction));

	playButton->setPosition(ccp(winSize.width/2, 250));

	//	Menu
	CCMenu* pMenu = CCMenu::create(playButton, NULL);
	pMenu->setPosition(CCPointZero);

	this->addChild(pMenu, 1);

	return true;
}

void HomeScene::playButtonAction (cocos2d::CCObject* pSender) {
	CCLOG("Enter Game Scene.");

	CCScene* pScene = GameScene::scene ();

	if (pScene != NULL) {
		CCDirector::sharedDirector ()-> replaceScene (pScene);
	}
	else
	{
		CCLOG("ERROR: Game Scene Can not be NULL!");
	}
}