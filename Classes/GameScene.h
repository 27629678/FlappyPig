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
    
private:
    float velocity_x;
    float velocity_y;
    float velocity_y_delta;
    
    bool iscollision;
    bool iscollision_x;
    bool iscollision_uy;
    bool iscollision_dy;
};

