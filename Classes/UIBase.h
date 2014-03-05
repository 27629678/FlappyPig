#pragma once
#include "cocos2d.h"

USING_NS_CC;

class UIBase : public CCLayer
{
public:
	virtual bool init ();
	static CCScene* scene ();

	void returnButtonAction (cocos2d::CCObject* pSender);

	CREATE_FUNC (UIBase);
};

