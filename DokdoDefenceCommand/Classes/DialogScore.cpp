//
//  DialogScore.cpp
//  DokdoDefenceCommand
//
//  Created by 김진율 on 2021/04/02.
//

#include "DialogScore.hpp"
#include "SaveManager.hpp"
#include "SceneMenu.hpp"
#include "SoundManager.hpp"

bool DialogScore::init() {
    Size winSize = Director::getInstance()->getWinSize();
    if (!LayerColor::initWithColor(Color4B(0, 0, 0, 180), winSize.width, winSize.height)) {
        return false;
    }
    
    Sprite* spDialog = Sprite::create("highscore.png");
    spDialog->setPosition(Vec2(winSize.width/2, winSize.height/2));
    addChild(spDialog);
    
    char szTEMP[32] = {0, };
    for (int i = 0; i < MAX_LABEL; i++) {
        sprintf(szTEMP, "000000000");
        
        Label* label = LabelCreator::createLabel(szTEMP, "Capsmall.ttf", 24);
        label->setVisible(false);
        label->setPosition(Vec2(175, 545 - (31 * i)));
        addChild(label, 5, TAG_LABEL_BASE + i);
        
        sprintf(szTEMP, "0000-00-00 00:00:00");
        
        Label* label2 = LabelCreator::createLabel(szTEMP, "Capsmall.ttf", 15);
        label2->setVisible(false);
        label2->setPosition(Vec2(315, 545 - (31 * i)));
        addChild(label2, 5, TAG_LABEL_BASE2 + i);
    }
    
    spBack = Sprite::createWithSpriteFrameName("option_back.png");
    spBack->setPosition(Vec2(360, 150));
    addChild(spBack);
    
    return true;
}


void DialogScore::addTouchListener() {
    mTouchListener = EventListenerTouchAllAtOnce::create();
    mTouchListener->onTouchesBegan = CC_CALLBACK_2(DialogScore::onTouchesBegan, this);
    mTouchListener->onTouchesMoved = CC_CALLBACK_2(DialogScore::onTouchesMoved, this);
    mTouchListener->onTouchesEnded = CC_CALLBACK_2(DialogScore::onTouchesEnded, this);
    getEventDispatcher()->addEventListenerWithFixedPriority(mTouchListener, 1);
    setKeypadEnabled(true);
}

void DialogScore::removeTouchListener() {
    if (mTouchListener != NULL) {
        getEventDispatcher()->removeEventListener(mTouchListener);
        mTouchListener = NULL;
    }
    setKeypadEnabled(false);
}

void DialogScore::Show() {
    DDC_SAVE_DATA* save = SaveManager::load();
    
    char szTEMP[32] = {0, };
    for (int i = 0; i < MAX_LABEL; i++) {
        Label* label = (Label*)getChildByTag(TAG_LABEL_BASE + i);
        Label* label2 = (Label*)getChildByTag(TAG_LABEL_BASE2 + i);
        if (save->highscore[i].score > 0) {
            sprintf(szTEMP, "%09lu", save->highscore[i].score);
            label->setString(szTEMP);
            sprintf(szTEMP, "%04d-%02d-%02d %02d:%02d:%02d",
                    save->highscore[i].time.tm_year + 1900,
                    save->highscore[i].time.tm_mon + 1,
                    save->highscore[i].time.tm_mday,
                    save->highscore[i].time.tm_hour,
                    save->highscore[i].time.tm_min,
                    save->highscore[i].time.tm_sec);
            label2->setString(szTEMP);
            
            label->setVisible(true);
            label2->setVisible(true);
        } else {
            label->setVisible(false);
            label2->setVisible(false);
        }
    }

    delete save;
    
    setVisible(true);
    addTouchListener();
    setScale(0);
    ScaleTo* scaleTo = ScaleTo::create(0.5, 1.0);
    ActionInterval* interval = EaseBackOut::create(scaleTo);
    runAction(interval);
}

void DialogScore::Hide() {
    setVisible(false);
    removeTouchListener();
}

void DialogScore::touchHandle(Vec2 pt) {
    if (spBack->getBoundingBox().containsPoint(pt)) {
        spBack->setScale(0.9);
    } else {
        spBack->setScale(1.0);
    }
}

void DialogScore::onKeyPressed(EventKeyboard::KeyCode keycode, Event* event) {
}

void DialogScore::onKeyReleased(EventKeyboard::KeyCode keycode, Event* event)
{
    if (keycode == EventKeyboard::KeyCode::KEY_BACK) {
        SoundManager::playButton();
        SceneMenu* menu = (SceneMenu*)getParent();
        menu->hideDialogScore();
    }
}

void DialogScore::onTouchesBegan(vector<Touch*> touches, Event* event) {
    Touch* touch = touches[0];
    touchHandle(touch->getLocation());
}

void DialogScore::onTouchesMoved(vector<Touch*> touches, Event* event) {
    Touch* touch = touches[0];
    touchHandle(touch->getLocation());
}

void DialogScore::onTouchesEnded(vector<Touch*> touches, Event* event) {
    Touch* touch = touches[0];
    Vec2 pt = touch->getLocation();
    
    spBack->setScale(1.0);
    
    if (spBack->getBoundingBox().containsPoint(pt)) {
        SoundManager::playButton();
        SceneMenu* menu = (SceneMenu*)getParent();
        menu->hideDialogScore();
    }
}
