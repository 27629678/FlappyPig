#pragma once
#include "cocos2d.h"

USING_NS_CC;

class HomeScene : public CCLayer
{
public:
	virtual bool init ();
	static CCScene* scene ();

	void playButtonAction (CCObject* pSender);

	CREATE_FUNC(HomeScene);
};

