#include "cocos2d.h"

class GameScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    CREATE_FUNC(GameScene);
    
private:
    int _score;

    int _last;

    cocos2d::Sprite* _spawn;
    
    cocos2d::Label* _scoreLabel;

    cocos2d::Label* _lastLabel;

    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    
    void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);

    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
    
    void showScore();

};
