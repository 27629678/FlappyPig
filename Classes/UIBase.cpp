#include "UIBase.h"
#include "HomeScene.h"

USING_NS_CC;
using namespace std;

CCScene* UIBase::scene () {
	CCScene* pScene = CCScene::create ();
	UIBase* pLayer = UIBase::create ();
	pScene->addChild(pLayer);

	return pScene;
}

bool UIBase::init () {
	if (!CCLayer::init ()) {
		return false;
	}

	CCDirector* pDirector = CCDirector::sharedDirector ();

	CCSize winSize = pDirector->getVisibleSize();

	CCMenuItemImage* returnButton = CCMenuItemImage::create (
		"Return_Nor.png",
		"Return_Hig.png",
		this,
		menu_selector(UIBase::returnButtonAction));
	returnButton->setPosition(
		ccp(
		returnButton->getContentSize().width/2 + 10,
		winSize.height - returnButton->getContentSize().height/2 - 10));
	returnButton->setScale(0.8f,0.8f);

	CCMenu* pMenu = CCMenu::create (returnButton, NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu);

	return true;
}

void UIBase::returnButtonAction (cocos2d::CCObject* pSender) {
	CCLOG("Return Home Scene.");

	CCScene* pHomeScene = HomeScene::scene ();
	CCDirector::sharedDirector()->replaceScene(pHomeScene);
}