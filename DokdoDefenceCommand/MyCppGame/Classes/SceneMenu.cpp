//
//  SceneMenu.cpp
//  MyCppGame
//
//  Created by Jinryul Kim on 2014. 7. 24..
//
//

#include "SceneMenu.h"
#include "SoundManager.h"

USING_NS_CC;

Scene* SceneMenu::createScene()
{
    Scene* scene = Scene::create();
    scene->setTag(SCENE_TAG_MENU);
    SceneMenu* menu = SceneMenu::create();
    menu->setTag(LAYER_TAG_MENU);
    
    scene->addChild(menu);
    
    return scene;
}

Scene* SceneMenu::createScene(bool clear,
                              float totaltime,
                              int score,
                              int enermyCtn,
                              int forceCtn,
                              int income,
                              bool highscore)
{
    Scene* scene = Scene::create();
    scene->setTag(SCENE_TAG_MENU);
    SceneMenu* menu = SceneMenu::create();
    menu->setTag(LAYER_TAG_MENU);
    menu->setCleanData(clear, totaltime, score, enermyCtn, forceCtn, income, highscore);
    
    scene->addChild(menu);
    
    return scene;
}

void SceneMenu::setCleanData(bool clear,
                             float totaltime,
                             int score,
                             int enermyCtn,
                             int forceCtn,
                             int income,
                             bool highscore)
{
    DialogResult* dialogResult = DialogResult::create();
    addChild(dialogResult, MENU_ZORDER_DIALOG, MENU_TAG_DIALOGRESULT);
    dialogResult->setVisible(false);
    showDialogResult(clear, totaltime, score, enermyCtn, forceCtn, income, highscore);
}

bool SceneMenu::init()
{
    if(!Layer::init())
    {
        return false;
    }
    
    bResult = false;
    bBack = false;
    
    SoundManager::playBGM();
    SaveManager::createSaveIfNotExist();
    
    mWinSize = Director::getInstance()->getWinSize();
    
    Sprite* spBK = Sprite::create("MENU_BK.png");
    spBK->setPosition(Vec2(mWinSize.width / 2, mWinSize.height * 0.485));
    addChild(spBK, MENU_ZORDER_BK, MENU_TAG_BK);
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Menu.plist");
    menuBatchNode = SpriteBatchNode::create("Menu.png");
    addChild(menuBatchNode, MENU_ZORDER_BATCHNODE);
    
    Sprite* spTITLE = Sprite::createWithSpriteFrameName("main_title.png");
    spTITLE->setAnchorPoint(Vec2(0.5, 1));
    spTITLE->setPosition(Vec2(mWinSize.width / 2, mWinSize.height));
    menuBatchNode->addChild(spTITLE);
    
    Sprite* spBOTTOM = Sprite::createWithSpriteFrameName("main_down.png");
    spBOTTOM->setAnchorPoint(Vec2(0.5, 0));
    spBOTTOM->setPosition(Vec2(mWinSize.width / 2, 0));
    menuBatchNode->addChild(spBOTTOM);
    
    MenuItemSprite* menuStart =
        createMenuItemSprite("main_start_00.png", "main_start_01.png", "main_start_02.png", MENU_TAG_START);
    MenuItemSprite* menuUpgrade =
        createMenuItemSprite("main_upgrade_00.png", "main_upgrade_01.png", "main_upgrade_02.png", MENU_TAG_UPGRADE);
    MenuItemSprite* menuScore =
        createMenuItemSprite("main_score_00.png", "main_score_01.png", "main_score_02.png", MENU_TAG_SCORE);
    MenuItemSprite* menuOption =
        createMenuItemSprite("main_option_00.png", "main_option_01.png", "main_option_02.png", MENU_TAG_OPTION);
    
    Menu* menu = Menu::create(menuStart, menuUpgrade, menuScore, menuOption, nullptr);
    menu->setPosition(Vec2(mWinSize.width / 2, mWinSize.height * 0.45));
    menu->alignItemsVerticallyWithPadding(mWinSize.height * 0.02);
    addChild(menu, MENU_ZORDER_MENU, MENU_TAG_MAINMENU);
    
    MenuItemSprite* menuFacebook = createSNSMenu("main_facebook.png", MENU_TAG_FACEBOOK);
    MenuItemSprite* menuTwitter = createSNSMenu("main_twitter.png", MENU_TAG_TWITTER);
    Menu* snsMenu = Menu::create(menuFacebook, menuTwitter, nullptr);
    snsMenu->alignItemsHorizontallyWithPadding(mWinSize.width * 0.01);
    snsMenu->setPosition(Vec2(mWinSize.width * 0.22, mWinSize.height * 0.05));
    addChild(snsMenu, MENU_ZORDER_MENU, MENU_TAG_SNSMENU);
    
    MenuItemSprite* menuCredit = createSNSMenu("main_credit.png", MENU_TAG_CREDIT);
    Menu* creditMenu = Menu::create(menuCredit, nullptr);
    creditMenu->setPosition(Vec2(mWinSize.width * 0.8, mWinSize.height * 0.045));
    addChild(creditMenu, MENU_ZORDER_CREDIT, MENU_TAG_CREDITMENU);
    
    DialogLevel* dialogLevel = DialogLevel::create();
    addChild(dialogLevel, MENU_ZORDER_DIALOG, MENU_TAG_DIALOGLEVEL);
    dialogLevel->setVisible(false);
    
    DialogOption* dialogOption = DialogOption::create();
    addChild(dialogOption, MENU_ZORDER_DIALOG, MENU_TAG_DIALOGOPTION);
    dialogOption->setVisible(false);
    
    DialogScore* dialogScore = DialogScore::create();
    addChild(dialogScore, MENU_ZORDER_DIALOG, MENU_TAG_DIALOGSCORE);
    dialogScore->setVisible(false);
    
    return true;
}

MenuItemSprite* SceneMenu::createSNSMenu(const char* image, int tag)
{
    MenuItemSprite* menuItem;
    
    Sprite* normal = Sprite::createWithSpriteFrameName(image);
    Sprite* small = Sprite::createWithSpriteFrameName(image);
    small->setAnchorPoint(Vec2(0.5, 0.5));
    small->setScale(0.95);
    
    menuItem = MenuItemSprite::create(normal, small, CC_CALLBACK_1(SceneMenu::onMenu, this));
    menuItem->setTag(tag);
    
    return menuItem;
}

MenuItemSprite* SceneMenu::createMenuItemSprite(const char* text, const char* hilight, const char* han, int tag)
{
    MenuItemSprite* menuItem;
    
    Sprite* normal = Sprite::createWithSpriteFrameName("main_selectbar.png");
    normal->setOpacity(0);
    Sprite* normalText = Sprite::createWithSpriteFrameName(text);
    normalText->setPosition(Vec2(normal->getContentSize().width / 2, normal->getContentSize().height/2));
    normal->addChild(normalText);
    
    Sprite* selected = Sprite::createWithSpriteFrameName("main_selectbar.png");
    Sprite* selText = Sprite::createWithSpriteFrameName(text);
    selText->setPosition(Vec2(selected->getContentSize().width / 2, selected->getContentSize().height/2));
    Sprite* selHilight = Sprite::createWithSpriteFrameName(hilight);
    selHilight->setPosition(Vec2(selText->getContentSize().width / 2, selText->getContentSize().height/2));
    
    selText->addChild(selHilight);
    selected->addChild(selText);
    
    Sprite* selHan = Sprite::createWithSpriteFrameName(han);
    selHan->setAnchorPoint(Point(1, 0.5));
    selHan->setPosition(Vec2(selected->getContentSize().width * 0.98, selected->getContentSize().height * 0.5));
    selected->addChild(selHan);
    
    ScaleTo* scaleToBig = ScaleTo::create(0.3, 1.1);
    ScaleTo* scaleToSmall = ScaleTo::create(0.3, 0.9);
    Sequence* sequence = Sequence::create(scaleToBig, scaleToSmall, nullptr);
    RepeatForever* repeatForever = RepeatForever::create(sequence);
    selHan->runAction(repeatForever);
    
    menuItem = MenuItemSprite::create(normal, selected, CC_CALLBACK_1(SceneMenu::onMenu, this));
    menuItem->setTag(tag);
    
    return menuItem;
}

void SceneMenu::onMenu(Ref* sender)
{
	SoundManager::playButton();
    switch(((Node*)sender)->getTag())
    {
        case MENU_TAG_START:
            showDialogLevel();
            break;
        case MENU_TAG_UPGRADE:
            {
                Scene* upgrade = SceneUpgrade::createScene();
                TransitionScene* transition = TransitionSlideInR::create(0.5f, upgrade);
                Director::getInstance()->pushScene(transition);
            }
            break;
        case MENU_TAG_SCORE:
            showDialogScore();
            break;
        case MENU_TAG_OPTION:
            showDialogOption();
            break;
        case MENU_TAG_FACEBOOK:
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        	Application::getInstance()->openURL("http://m.facebook.com/DokdoDefenceCommand/");
#endif
            break;
        case MENU_TAG_TWITTER:
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        	Application::getInstance()->openURL("http://mobile.twitter.com/DokdoDefenceCom/");
#endif
        	break;
        case MENU_TAG_CREDIT:
            {
                Scene* credit = SceneCredit::createScene();
                TransitionScene* transition = TransitionSlideInB::create(0.5f, credit);
                Director::getInstance()->pushScene(transition);
            }
            break;
    }
}

void SceneMenu::onExit()
{
    Layer::onExit();
    setKeypadEnabled(false);
}

void SceneMenu::onEnterTransitionDidFinish()
{
    Layer::onEnterTransitionDidFinish();
    if(bResult == false)
    {
        setKeypadEnabled(true);
    }
}

void SceneMenu::hideDefaultMenus()
{
    ((Menu*)getChildByTag(MENU_TAG_MAINMENU))->setVisible(false);
    ((Menu*)getChildByTag(MENU_TAG_SNSMENU))->setVisible(false);
    ((Menu*)getChildByTag(MENU_TAG_CREDITMENU))->setVisible(false);
}

void SceneMenu::showDefaultMenus()
{
    ((Menu*)getChildByTag(MENU_TAG_MAINMENU))->setVisible(true);
    ((Menu*)getChildByTag(MENU_TAG_SNSMENU))->setVisible(true);
    ((Menu*)getChildByTag(MENU_TAG_CREDITMENU))->setVisible(true);
}

void SceneMenu::showDialogLevel()
{
    setKeypadEnabled(false);
    hideDefaultMenus();
    ((DialogLevel*)getChildByTag(MENU_TAG_DIALOGLEVEL))->Show();
}

void SceneMenu::hideDialogLevel()
{
    ((DialogLevel*)getChildByTag(MENU_TAG_DIALOGLEVEL))->Hide();
    showDefaultMenus();
    setKeypadEnabled(true);
}

void SceneMenu::showDialogOption()
{
    setKeypadEnabled(false);
    hideDefaultMenus();
    ((DialogOption*)getChildByTag(MENU_TAG_DIALOGOPTION))->Show();
}

void SceneMenu::hideDialogOption()
{
    ((DialogOption*)getChildByTag(MENU_TAG_DIALOGOPTION))->Hide();
    showDefaultMenus();
    setKeypadEnabled(true);
}

void SceneMenu::showDialogScore()
{
    setKeypadEnabled(false);
    hideDefaultMenus();
    ((DialogScore*)getChildByTag(MENU_TAG_DIALOGSCORE))->Show();
}

void SceneMenu::hideDialogScore()
{
    ((DialogScore*)getChildByTag(MENU_TAG_DIALOGSCORE))->Hide();
    showDefaultMenus();
    setKeypadEnabled(true);
}

void SceneMenu::showDialogResult(bool clear,
                                 float totaltime,
                                 int score,
                                 int enermyCtn,
                                 int forceCtn,
                                 int income,
                                 bool highscore)
{
    bResult = true;
    setKeypadEnabled(false);
    hideDefaultMenus();
    ((DialogResult*)getChildByTag(MENU_TAG_DIALOGRESULT))->Show(clear,
                                                                totaltime,
                                                                score,
                                                                enermyCtn,
                                                                forceCtn,
                                                                income,
                                                                highscore);
}

void SceneMenu::hideDialogResult()
{
	log("hideDialogResult");
    ((DialogResult*)getChildByTag(MENU_TAG_DIALOGRESULT))->Hide();
    showDefaultMenus();
    bResult = false;
    setKeypadEnabled(true);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    log("hideDialogResult -> showAD");
    Application::getInstance()->showAD();
#endif
}

void SceneMenu::onKeyPressed(EventKeyboard::KeyCode keycode, Event* event)
{
}

void SceneMenu::onKeyReleased(EventKeyboard::KeyCode keycode, Event* event)
{
    if(keycode == EventKeyboard::KeyCode::KEY_BACK)
    {
    	SoundManager::playButton();
        if(bBack == false)
        {
            bBack = true;
            hideDefaultMenus();
            getChildByTag(MENU_TAG_BK)->setOpacity(120);
            Label* label = nullptr;
            if(Application::getInstance()->getCurrentLanguage() == LanguageType::KOREAN)
            {
                label = LabelCreater::createLabel("Back 버튼을 한 번 더 누르면 종료합니다.", "JejuHallasan.ttf", 25);
            }
            else
            {
                label = LabelCreater::createLabel("Press back one more time to quit.", "JejuHallasan.ttf", 25);
            }
            label->setPosition(Vec2(mWinSize.width / 2, mWinSize.height / 2));
            addChild(label, 6, MENU_TAG_BACKTXT);
            
            scheduleOnce(schedule_selector(SceneMenu::onBACK), 1.5f);
        }
        else
        {
            Director::getInstance()->end();
        }
    }
}

void SceneMenu::onBACK(float dt)
{
    getChildByTag(MENU_TAG_BK)->setOpacity(255);
    showDefaultMenus();
    removeChildByTag(MENU_TAG_BACKTXT, true);
    bBack = false;
}
