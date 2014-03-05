#pragma once
#include "cocos2d.h"

USING_NS_CC;

class MapBase : public CCSprite
{
public:
	static CCSprite* create (CCLayer* layer, const char* spritename, CCRect rect = CCRect(0, 0, 960, 640));
};

