#include "GameScene.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
    auto scene = Scene::createWithPhysics();
    auto layer = GameScene::create();
    scene->addChild(layer);
    return scene;
}

bool GameScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();

    Sprite* back = Sprite::create("bg.jpg");
    back->setPosition(visibleSize.width / 2, visibleSize.height / 2);
    back->setScale(2);
    
    this->addChild(back, -2);

    Sprite* blue = Sprite::create("blue.png");
    blue->setAnchorPoint(Point(0.5, 1));
    blue->setPosition(visibleSize.width / 2, 195);
    blue->setScale(10, 10);
    
    this->addChild(blue, -1);
    
    Sprite* tree = Sprite::create("tree.png");
    tree->setPosition(visibleSize.width / 2, 200);
    tree->setScale(1.5, 1);
    PhysicsBody* treeBody = PhysicsBody::createBox(tree->getBoundingBox().size);
    treeBody->setDynamic(false);
    tree->setPhysicsBody(treeBody);
    
    this->addChild(tree, 0);

    Label* nami = Label::create("時代の波", "Arial", 32);
    nami->setPosition(visibleSize.width / 2, 100);
    this->addChild(nami, 1);

    
    auto listener = EventListenerTouchOneByOne::create();
    
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
    listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
    
    this->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 100);
    
    return true;
}

bool GameScene::onTouchBegan(Touch* touch, Event* event) {
    
    return true;
}

void GameScene::onTouchEnded(Touch* touch, Event* event) {
    
    Sprite* man = Sprite::create("man_6.png");
    man->setScale(1.2);
    man->setPosition(touch->getLocation().x, 800);
    PhysicsBody* manBody = PhysicsBody::createBox(man->getBoundingBox().size);
    man->setPhysicsBody(manBody);
    
    this->addChild(man, 2);
}