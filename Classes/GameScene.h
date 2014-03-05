#pragma once
#include "cocos2d.h"

USING_NS_CC;

class GameScene : public CCLayer
{
public:
	virtual bool init ();
	static CCScene* scene ();
	static GameScene* sharedGameManager();

	CREATE_FUNC (GameScene);

	CCArray* arrayPost;

	CCSprite* player;
	bool isPresingScreen;

	void myUpdate(float dt);
	void createPost (float dt);

	virtual bool ccTouchBegan (CCTouch* touch, CCEvent* touchevent);
	virtual void ccTouchMoved (CCTouch* touch, CCEvent* touchevent);
	virtual void ccTouchEnded (CCTouch* touch, CCEvent* touchevent);

	virtual void onEnter ();
	virtual void onExit ();
	void update(float dt);
};

