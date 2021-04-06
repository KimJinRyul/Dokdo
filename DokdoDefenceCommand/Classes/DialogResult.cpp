//
//  DialogResult.cpp
//  DokdoDefenceCommand
//
//  Created by 김진율 on 2021/04/05.
//

#include "DialogResult.hpp"
#include "SceneMenu.hpp"
#include "SoundManager.hpp"

bool DialogResult::init()
{
    Size winSize = Director::getInstance()->getWinSize();
    if(!LayerColor::initWithColor(Color4B(0, 0, 0, 180), winSize.width, winSize.height))
    {
        return false;
    }
    
    spDlg = Sprite::createWithSpriteFrameName("clear.png");
    spDlg->setPosition(Vec2(winSize.width / 2, winSize.height * 0.45));
    addChild(spDlg, 1);
    
    spBack = Sprite::createWithSpriteFrameName("option_back.png");
    spBack->setPosition(Vec2(360, 210));
    addChild(spBack, 2);

    return true;
}

void DialogResult::addTouchListener()
{
    mTouchListener = EventListenerTouchAllAtOnce::create();
    mTouchListener->onTouchesBegan = CC_CALLBACK_2(DialogResult::onTouchesBegan, this);
    mTouchListener->onTouchesMoved = CC_CALLBACK_2(DialogResult::onTouchesMoved, this);
    mTouchListener->onTouchesEnded = CC_CALLBACK_2(DialogResult::onTouchesEnded, this);
    getEventDispatcher()->addEventListenerWithFixedPriority(mTouchListener, 1);
    setKeypadEnabled(true);
}

void DialogResult::removeTouchListener()
{
    if(mTouchListener != NULL)
    {
        getEventDispatcher()->removeEventListener(mTouchListener);
        mTouchListener = NULL;
    }
    setKeypadEnabled(false);
}

void DialogResult::Show(bool clear,
                        float totaltime,
                        int score,
                        int enermyCtn,
                        int forceCtn,
                        int income,
                        bool highscore)
{
    Sprite* spTitle = nullptr;
    Sprite* spTitle2 = nullptr;
    if(clear)
    {
        spTitle = Sprite::createWithSpriteFrameName("clear_missionclear.png");
        spTitle->setPosition(Vec2(spDlg->getContentSize().width * 0.35, spDlg->getContentSize().height * 0.95));
        spTitle2 = Sprite::createWithSpriteFrameName("clear_clear.png");
    }
    else
    {
        spTitle = Sprite::createWithSpriteFrameName("clear_missionfail.png");
        spTitle->setPosition(Vec2(spDlg->getContentSize().width * 0.3, spDlg->getContentSize().height * 0.95));
        spTitle2 = Sprite::createWithSpriteFrameName("clear_fail.png");
    }
    
    spTitle->setOpacity(0);
    spTitle->setScale(6.0);
    DelayTime* delayTime = DelayTime::create(0.5);
    FadeIn* fadeIn = FadeIn::create(0);
    EaseBackOut* easeBack = EaseBackOut::create(ScaleTo::create(0.4, 1.0));
    spTitle->runAction(Sequence::create(delayTime, fadeIn, easeBack, nullptr));
    
    spTitle2->setAnchorPoint(Vec2(0.5, 1));
    spTitle2->setPosition(Vec2(spDlg->getContentSize().width / 2, spDlg->getContentSize().height - 28));
    
    spDlg->addChild(spTitle);
    spDlg->addChild(spTitle2);
    
    int titleLeft = 65;
    int titleRight = spDlg->getContentSize().width - 70;
    int fontSize = 24;
    char szTemp[32] = {0, };
    
    Label* timeTitle = LabelCreator::createLabel("Time", "Capsmall.ttf", fontSize);
    timeTitle->setAnchorPoint(Vec2(0, 0));
    timeTitle->setPosition(Vec2(titleLeft, 218));
    spDlg->addChild(timeTitle);
    
    int nMinute = 0, nSecond = 0;
    int temp = totaltime;
    while(temp >= 60)
    {
        temp -= 60;
        nMinute++;
    }
    nSecond = temp;
    sprintf(szTemp, "%02d:%02d", nMinute, nSecond);
    Label* timeLabel = LabelCreator::createLabel(szTemp, "Capsmall.ttf", fontSize);
    timeLabel->setAnchorPoint(Vec2(1, 0));
    timeLabel->setPosition(Vec2(titleRight, 218));
    spDlg->addChild(timeLabel);
    
    Label* enermyTitle = LabelCreator::createLabel("Enermies", "Capsmall.ttf", fontSize);
    enermyTitle->setAnchorPoint(Vec2(0, 0));
    enermyTitle->setPosition(Vec2(titleLeft, 183));
    spDlg->addChild(enermyTitle);
    
    sprintf(szTemp, "%09d", enermyCtn);
    Label* enermyLabel = LabelCreator::createLabel(szTemp, "Capsmall.ttf", fontSize);
    enermyLabel->setAnchorPoint(Vec2(1, 0));
    enermyLabel->setPosition(Vec2(titleRight, 183));
    spDlg->addChild(enermyLabel);
    
    Label* ourTitle = LabelCreator::createLabel("Our troops", "Capsmall.ttf", fontSize);
    ourTitle->setAnchorPoint(Vec2(0, 0));
    ourTitle->setPosition(Vec2(titleLeft, 147));
    spDlg->addChild(ourTitle);
    
    sprintf(szTemp, "%09d", forceCtn);
    Label* ourLabel = LabelCreator::createLabel(szTemp, "Capsmall.ttf", fontSize);
    ourLabel->setAnchorPoint(Vec2(1, 0));
    ourLabel->setPosition(Vec2(titleRight, 147));
    spDlg->addChild(ourLabel);
    
    Label* scoreTitle = LabelCreator::createLabel("Score", "Capsmall.ttf", fontSize);
    scoreTitle->setAnchorPoint(Vec2(0, 0));
    scoreTitle->setPosition(Vec2(titleLeft, 112));
    spDlg->addChild(scoreTitle);
    
    sprintf(szTemp, "%09d", score);
    Label* scoreLabel = LabelCreator::createLabel(szTemp, "Capsmall.ttf", fontSize);
    scoreLabel->setAnchorPoint(Vec2(1, 0));
    scoreLabel->setPosition(Vec2(titleRight, 112));
    spDlg->addChild(scoreLabel);
    
    if(highscore)
    {
        Sprite* high = Sprite::createWithSpriteFrameName("clear_high.png");
        high->setAnchorPoint(Vec2(0, 0));
        high->setPosition(Vec2(titleRight, 104));
        spDlg->addChild(high);
        
        Sprite* hilight = Sprite::createWithSpriteFrameName("clear_high_01.png");
        hilight->setAnchorPoint(Vec2(0, 0));
        high->addChild(hilight);
        
        SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();
        Animation* animation = Animation::create();
        char szTemp[16] = {0, };
        for(int i = 0; i < 6; i++)
        {
            sprintf(szTemp, "clear_high_%02d.png", i);
            SpriteFrame* frame = frameCache->getSpriteFrameByName(szTemp);
            if(frame != nullptr)
            {
                animation->addSpriteFrame(frame);
            }
        }
        animation->setDelayPerUnit(0.05);
        hilight->runAction(RepeatForever::create(Sequence::create(Animate::create(animation), DelayTime::create(0.5), nullptr)));
    }
    
    Label* revenueTitle = LabelCreator::createLabel("Revenue", "Capsmall.ttf", fontSize);
    revenueTitle->setAnchorPoint(Vec2(0, 0));
    revenueTitle->setPosition(Vec2(titleLeft, 75));
    spDlg->addChild(revenueTitle);
    
    sprintf(szTemp, "%09d", income);
    Label* revenueLabel = LabelCreator::createLabel(szTemp, "Capsmall.ttf", fontSize);
    revenueLabel->setAnchorPoint(Vec2(1, 0));
    revenueLabel->setPosition(Vec2(titleRight, 75));
    spDlg->addChild(revenueLabel);
    
    setVisible(true);
    addTouchListener();
    setScale(0);
    runAction(EaseBackOut::create(ScaleTo::create(0.5, 1.0)));
}

void DialogResult::Hide()
{
    setVisible(false);
    removeTouchListener();
}

void DialogResult::touchHandle(Vec2 pt)
{
    if(spBack->getBoundingBox().containsPoint(pt))
    {
        spBack->setScale(0.9);
    }
    else
    {
        spBack->setScale(1.0);
    }
}

void DialogResult::onKeyPressed(EventKeyboard::KeyCode keycode, Event* event)
{
}

void DialogResult::onKeyReleased(EventKeyboard::KeyCode keycode, Event* event)
{
    if(keycode == EventKeyboard::KeyCode::KEY_BACK)
    {
        SoundManager::playButton();
        SceneMenu* menu = (SceneMenu*)getParent();
        menu->hideDialogResult();
    }
}

void DialogResult::onTouchesBegan(vector<Touch*> touches, Event* event)
{
    Touch* touch = touches[0];
    touchHandle(touch->getLocation());
}

void DialogResult::onTouchesMoved(vector<Touch*> touches, Event* event)
{
    Touch* touch = touches[0];
    touchHandle(touch->getLocation());
}

void DialogResult::onTouchesEnded(vector<Touch*> touches, Event* event)
{
    Touch* touch = touches[0];
    Vec2 pt = touch->getLocation();
    
    spBack->setScale(1.0);
    if(spBack->getBoundingBox().containsPoint(pt))
    {
        SoundManager::playButton();
        SceneMenu* menu = (SceneMenu*)getParent();
        menu->hideDialogResult();
    }
}
