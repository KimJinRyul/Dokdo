//
//  DialogOption.cpp
//  DokdoDefenceCommand
//
//  Created by 김진율 on 2021/04/02.
//

#include "DialogOption.hpp"
#include "SceneMenu.hpp"
#include "LabelCreator.hpp"
#include "SoundManager.hpp"

bool DialogOption::init()
{
    Size winSize = Director::getInstance()->getWinSize();
    if (!LayerColor::initWithColor(Color4B(0, 0, 0, 180), winSize.width, winSize.height)) {
        return false;
    }
    
    mTouchListener = nullptr;
    
    bResetDlg = false;
    mBatchNode = SpriteBatchNode::create("Menu.png");
    addChild(mBatchNode);
    
    spDlg = Sprite::createWithSpriteFrameName("option.png");
    spDlg->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
    mBatchNode->addChild(spDlg, ZORDER_DIALOG, TAG_DIALOG);
    rtDlg = spDlg->getBoundingBox();
    
    spMusic = Sprite::createWithSpriteFrameName("option_button_00.png");
    if(UserDefault::getInstance()->getBoolForKey(OPTION_KEY_MUSIC, true))
        spMusic->setPosition(Vec2(SLIDE_LEFT, 263));
    else
        spMusic->setPosition(Vec2(SLIDE_RIGHT, 263));
    spDlg->addChild(spMusic, ZORDER_BTN, TAG_MUSIC);
    
    spSound = Sprite::createWithSpriteFrameName("option_button_00.png");
    if(UserDefault::getInstance()->getBoolForKey(OPTION_KEY_SOUND, true))
        spSound->setPosition(Vec2(SLIDE_LEFT, 163));
    else
        spSound->setPosition(Vec2(SLIDE_RIGHT, 163));
    spDlg->addChild(spSound, ZORDER_BTN, TAG_SOUND);
    
    spReset = Sprite::createWithSpriteFrameName("option_button_00.png");
    spReset->setPosition(Vec2(169, 65));
    spDlg->addChild(spReset, ZORDER_BTN, TAG_RESET);
    
    spBack = Sprite::createWithSpriteFrameName("option_back.png");
    spBack->setPosition(Vec2(250, 25));
    spDlg->addChild(spBack, ZORDER_BTN, TAG_BACK);
    
    return true;
}

void DialogOption::addTouchListener() {
    mTouchListener = EventListenerTouchAllAtOnce::create();
    mTouchListener->onTouchesBegan = CC_CALLBACK_2(DialogOption::onTouchesBegan, this);
    mTouchListener->onTouchesMoved = CC_CALLBACK_2(DialogOption::onTouchesMoved, this);
    mTouchListener->onTouchesEnded = CC_CALLBACK_2(DialogOption::onTouchesEnded, this);
    getEventDispatcher()->addEventListenerWithFixedPriority(mTouchListener, 1);
    setKeypadEnabled(true);
}

void DialogOption::removeTouchListener() {
    if(mTouchListener != nullptr) {
        getEventDispatcher()->removeEventListener(mTouchListener);
        mTouchListener = nullptr;
    }
    setKeypadEnabled(false);
}

void DialogOption::Show() {
    setVisible(true);
    addTouchListener();
    setScale(0);
    ScaleTo* scaleTo = ScaleTo::create(0.5, 1.0);
    ActionInterval* interval = EaseBackOut::create(scaleTo);
    runAction(interval);
}

void DialogOption::Hide() {
    setVisible(false);
    removeTouchListener();
}

void DialogOption::setBtnsScale(float scale) {
    spMusic->setScale(scale);
    spSound->setScale(scale);
    spReset->setScale(scale);
    spBack->setScale(scale);
}

void DialogOption::touchHandle(Vec2 pt) {
    pt.x -= rtDlg.origin.x;
    pt.y -= rtDlg.origin.y;
    
    setBtnsScale(1.0);
    
    if (spMusic->getBoundingBox().containsPoint(pt))    spMusic->setScale(0.9);
    if (spSound->getBoundingBox().containsPoint(pt))    spSound->setScale(0.9);
    if (spReset->getBoundingBox().containsPoint(pt))    spReset->setScale(0.9);
    if (spBack->getBoundingBox().containsPoint(pt))     spBack->setScale(0.9);
}

void DialogOption::onKeyPressed(EventKeyboard::KeyCode keycode, Event* event) {
}

void DialogOption::onKeyReleased(EventKeyboard::KeyCode keycode, Event* event)
{
    if (keycode == EventKeyboard::KeyCode::KEY_BACK) {
        SoundManager::playButton();
        if (bResetDlg == true) {
            bResetDlg = false;
            removeChildByTag(MENU_TAG_RESETDLG, true);
        } else {
            SceneMenu* menu = (SceneMenu*)getParent();
            menu->hideDialogOption();
        }
    }
}

void DialogOption::onTouchesBegan(vector<Touch*> touches, Event* event) {
    if (bResetDlg == false) {
        Touch* touch = touches[0];
        touchHandle(touch->getLocation());
    }
}

void DialogOption::onTouchesMoved(vector<Touch*> touches, Event* event) {
    if (bResetDlg == false) {
        Touch* touch = touches[0];
        touchHandle(touch->getLocation());
    }
}

void DialogOption::onTouchesEnded(vector<Touch*> touches, Event* event) {
    Touch* touch = touches[0];
    Vec2 pt = touch->getLocation();
    
    if (bResetDlg == true) {
        if (getChildByTag(MENU_TAG_RESETDLG)->getBoundingBox().containsPoint(pt)) {
            SoundManager::playButton();
            Size winSize = Director::getInstance()->getWinSize();
            if (pt.x < winSize.width / 2) {
                DDC_SAVE_DATA* saveData = new DDC_SAVE_DATA();
                SaveManager::save(saveData);
                delete saveData;
                DDC_CLEAR_DATA* clearData = new DDC_CLEAR_DATA();;
                SaveManager::saveClear(clearData);
                delete clearData;
            }
            bResetDlg = false;
            removeChildByTag(MENU_TAG_RESETDLG, true);
        }
    } else {
        pt.x -= rtDlg.origin.x;
        pt.y -= rtDlg.origin.y;
        
        setBtnsScale(1.0);
        
        if (spMusic->getBoundingBox().containsPoint(pt)) {
            spMusic->stopAllActions();
            if (UserDefault::getInstance()->getBoolForKey(OPTION_KEY_MUSIC, true)) {
                UserDefault::getInstance()->setBoolForKey(OPTION_KEY_MUSIC, false);
                spMusic->runAction(MoveTo::create(0.1, Vec2(SLIDE_RIGHT, 263)));
                SoundManager::stopBGM();
            } else {
                UserDefault::getInstance()->setBoolForKey(OPTION_KEY_MUSIC, true);
                spMusic->runAction(MoveTo::create(0.1, Vec2(SLIDE_LEFT, 263)));
                SoundManager::playBGM();
            }
            SoundManager::playButton();
        } else if (spSound->getBoundingBox().containsPoint(pt)) {
            spSound->stopAllActions();
            if (UserDefault::getInstance()->getBoolForKey(OPTION_KEY_SOUND, true)) {
                UserDefault::getInstance()->setBoolForKey(OPTION_KEY_SOUND, false);
                spSound->runAction(MoveTo::create(0.1, Vec2(SLIDE_RIGHT, 163)));
            } else {
                UserDefault::getInstance()->setBoolForKey(OPTION_KEY_SOUND, true);
                spSound->runAction(MoveTo::create(0.1, Vec2(SLIDE_LEFT, 163)));
            }
            SoundManager::playButton();
        } else if (spReset->getBoundingBox().containsPoint(pt)) {
            bResetDlg = true;
            Size winSize = Director::getInstance()->getWinSize();
            Sprite* spDlg = Sprite::create("reset.png", Rect(0, 0, 404, 168));
            spDlg->setPosition(Vec2(winSize.width / 2, winSize.height * 0.46));
            addChild(spDlg, 5, MENU_TAG_RESETDLG);
            
            Sprite* spOK = Sprite::create("reset.png", Rect(0, 169, 152, 38));
            spOK->setPosition(Vec2(spDlg->getContentSize().width * 0.3, spDlg->getContentSize().height * 0.39));
            spDlg->addChild(spOK);
            
            Sprite* spCANCEL = Sprite::create("reset.png", Rect(306, 169, 152, 38));
            spCANCEL->setPosition(Vec2(spDlg->getContentSize().width * 0.7, spDlg->getContentSize().height * 0.39));
            spDlg->addChild(spCANCEL);
            
            Label* label = nullptr;
            if (LanguageType::KOREAN == Application::getInstance()->getCurrentLanguage())
                label = LabelCreator::createLabel("게임 데이타가 초기화 됩니다", "JejuHallasan.ttf", 26);
            else
                label = LabelCreator::createLabel("Data initialization in progress", "JejuHallasan.ttf", 22);
            label->setPosition(Vec2(spDlg->getContentSize().width / 2, spDlg->getContentSize().height * 0.67));
            spDlg->addChild(label);
            SoundManager::playButton();
            
        } else if(spBack->getBoundingBox().containsPoint(pt)) {
            SceneMenu* menu = (SceneMenu*)getParent();
            menu->hideDialogOption();
            SoundManager::playButton();
        }
    }
}
