#pragma once
#include "cocos2d.h"

USING_NS_CC;

class MapCreater : public CCLayer
{
public:
	static MapCreater*  newMap ();

	CCSprite* upSprite;
	CCSprite* downSprite;

	void mapInit (int index);

	void update(float dt);

	virtual void onExit ();
};

