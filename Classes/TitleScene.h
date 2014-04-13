#include "cocos2d.h"

class TitleScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    CREATE_FUNC(TitleScene);

private:
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

};
