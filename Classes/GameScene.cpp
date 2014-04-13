#include "GameScene.h"

USING_NS_CC;

const float POSITION_Y_SPAWN = 800; // ここでねマンが初期表示されるY座標
const int COUNT_MAN = 5; // ここでねマンの初期残機

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
    
    _score = 0;
    _last = COUNT_MAN;
    
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

    _scoreLabel = Label::createWithBMFont("hase_toppo.fnt", "");
    _scoreLabel->setAnchorPoint(Point(1, 0.5));
    _scoreLabel->setScale(0.7);
    _scoreLabel->setPosition(visibleSize.width - 10, visibleSize.height - 30);
    
    this->addChild(_scoreLabel, 10);
    
    _lastLabel = Label::createWithBMFont("hase_toppo.fnt", "");
    _lastLabel->setAnchorPoint(Point(0, 0.5));
    _lastLabel->setScale(0.7);
    _lastLabel->setPosition(10, visibleSize.height - 30);
    
    this->addChild(_lastLabel, 10);

    auto listener = EventListenerTouchOneByOne::create();
    
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
    
    this->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 100);

    showScore();
    
    return true;
}

bool GameScene::onTouchBegan(Touch* touch, Event* event) {
    
    // seed
    srand((unsigned int) time(NULL));
    // 0〜5の間でランダム値を生成して +1 する
    int manId = (rand() % 5) + 1;
    
    _spawn = Sprite::create(StringUtils::format("man_%d.png", manId));
    _spawn->setPosition(touch->getLocation().x, POSITION_Y_SPAWN);
    PhysicsBody* manBody = PhysicsBody::createBox(_spawn->getBoundingBox().size);
    manBody->setDynamic(false);
    _spawn->setPhysicsBody(manBody);

    RotateTo* rotate = RotateTo::create(1, 90);
    RepeatForever* repeat = RepeatForever::create(rotate);
    _spawn->runAction(repeat);
    
    this->addChild(_spawn, 2);

    return true;
}

void GameScene::onTouchMoved(Touch* touch, Event* event) {

    _spawn->setPosition(touch->getLocation().x, POSITION_Y_SPAWN);
}

void GameScene::onTouchEnded(Touch* touch, Event* event) {

    _spawn->getActionManager()->removeAllActions();
    
    PhysicsBody* manBody = _spawn->getPhysicsBody();
    manBody->setDynamic(true);
    manBody->resetForces();
    
    _score++;
    showScore();
}

void GameScene::showScore() {
    
    _scoreLabel->setString(StringUtils::format("スコア:%d", _score));

    std::string last = "";
    for (int i = 0; i < _last; i++) {
        last += "●";
    }
    _lastLabel->setString(last);
}
