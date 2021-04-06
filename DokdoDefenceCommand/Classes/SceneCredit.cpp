//
//  SceneCredit.cpp
//  DokdoDefenceCommand
//
//  Created by 김진율 on 2021/04/05.
//

#include "SceneCredit.hpp"
#include "SoundManager.hpp"

Scene* SceneCredit::createScene() {
    Scene* scene = Scene::create();
    scene->setTag(SCENE_TAG_CREDIT);
    SceneCredit* credit = SceneCredit::create();
    credit->setTag(LAYER_TAG_CREDIT);
    
    scene->addChild(credit);
    
    return scene;
}

bool SceneCredit::init() {
    if (!Layer::init()) {
        return false;
    }
    
    Size winSize = Director::getInstance()->getWinSize();
    Sprite* spBK = Sprite::create("CREDIT.png");
    spBK->setPosition(Vec2(winSize.width/2, winSize.height/2));
    addChild(spBK);
    
    mTouchListener = EventListenerTouchAllAtOnce::create();
    mTouchListener->onTouchesEnded = CC_CALLBACK_2(SceneCredit::onTouchesEnded, this);
    getEventDispatcher()->addEventListenerWithFixedPriority(mTouchListener, 1);
    
    setKeypadEnabled(true);
    
    return true;
}

void SceneCredit::onKeyPressed(EventKeyboard::KeyCode keycode, Event* event) {
}

void SceneCredit::onKeyReleased(EventKeyboard::KeyCode keycode, Event* event) {
    if (keycode == EventKeyboard::KeyCode::KEY_BACK) {
        SoundManager::playButton();
        setKeypadEnabled(false);
        getEventDispatcher()->removeEventListener(mTouchListener);
        Director::getInstance()->popSceneWithTransitionSlideInT();
    }
}

void SceneCredit::onTouchesEnded(vector<Touch*> touches, Event* event) {
    SoundManager::playButton();
    setKeypadEnabled(false);
    getEventDispatcher()->removeEventListener(mTouchListener);
    Director::getInstance()->popSceneWithTransitionSlideInT();
}

