#include "TitleScene.h"
#include "GameScene.h"

USING_NS_CC;

Scene* TitleScene::createScene()
{
    auto scene = Scene::create();
    auto layer = TitleScene::create();
    scene->addChild(layer);
    return scene;
}

bool TitleScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();

    Sprite* back = Sprite::create("title.png");
    back->setPosition(visibleSize.width / 2, visibleSize.height / 2);
    
    this->addChild(back);

    Label* taptostart = Label::createWithBMFont("hase_toppo.fnt", "タップしてスタート");
    taptostart->setScale(0.7);
    taptostart->setPosition(visibleSize.width / 2, 200);
    
    this->addChild(taptostart, 1);
    

    auto listener = EventListenerTouchOneByOne::create();
   
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(TitleScene::onTouchBegan, this);
    listener->onTouchEnded = CC_CALLBACK_2(TitleScene::onTouchEnded, this);
    
    this->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 100);

    return true;
}

bool TitleScene::onTouchBegan(Touch* touch, Event* event) {
    
    return true;
}

void TitleScene::onTouchEnded(Touch* touch, Event* event) {
    
    // タッチイベントを全て無効化
    this->getEventDispatcher()->removeAllEventListeners();
    
    // シーン切り替え
    Scene* gameScene = GameScene::createScene();
    // FadeIn&Outで切り替え
    TransitionFade* fade = TransitionFade::create(0.5, gameScene);
    
    if (fade) {
        Director::getInstance()->replaceScene(fade);
    }
}