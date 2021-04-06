//
//  DialogLevel.cpp
//  DokdoDefenceCommand
//
//  Created by 김진율 on 2021/04/05.
//

#include "DialogLevel.hpp"
#include "SceneGame.hpp"
#include "SceneMenu.hpp"
#include "SoundManager.hpp"

bool DialogLevel::init() {
    Size winSize = Director::getInstance()->getWinSize();
    if (!LayerColor::initWithColor(Color4B(0, 0, 0, 180), winSize.width, winSize.height)) {
        return false;
    }
    
    DDC_CLEAR_DATA* clearData = SaveManager::loadClear();
    
    MenuItemSprite* menuVERYEASY = createMenuItemSprite("main_level_00.png", "main_level_01.png", MENU_TAG_VERYEASY, clearData->veryeasy);
    MenuItemSprite* menuEASY = createMenuItemSprite("main_level_10.png", "main_level_11.png", MENU_TAG_EASY, clearData->easy);
    MenuItemSprite* menuNORMAL = createMenuItemSprite("main_level_20.png", "main_level_21.png", MENU_TAG_NORMAL, clearData->normal);
    MenuItemSprite* menuHARD = createMenuItemSprite("main_level_30.png", "main_level_31.png", MENU_TAG_HARD, clearData->hard);
    MenuItemSprite* menuVERYHARD = createMenuItemSprite("main_level_40.png", "main_level_41.png", MENU_TAG_VERYHARD, clearData->veryhard);
    MenuItemSprite* menuIMPOSSIBLE = createMenuItemSprite("main_level_50.png", "main_level_51.png", MENU_TAG_IMPOSSIBLE, clearData->impossible);
    MenuItemSprite* menuENDLESS = createMenuItemSprite("main_level_60.png", "main_level_61.png", MENU_TAG_ENDLESS, false);

    delete clearData;
    
    Sprite* spBack = Sprite::createWithSpriteFrameName("option_back.png");
    Sprite* spBackS = Sprite::createWithSpriteFrameName("option_back.png");
    spBackS->setAnchorPoint(Vec2(0.5, 0.5));
    spBackS->setScale(0.9);
    MenuItemSprite* menuBack = MenuItemSprite::create(spBack, spBackS, CC_CALLBACK_1(DialogLevel::onMenu, this));
    menuBack->setTag(MENU_TAG_BACK);
    
    Menu* menu = Menu::create(menuVERYEASY,
                              menuEASY,
                              menuNORMAL,
                              menuHARD,
                              menuVERYHARD,
                              menuIMPOSSIBLE,
                              menuENDLESS,
                              menuBack,
                              nullptr);
    
    menu->alignItemsVertically();
    addChild(menu, 10, MENU_TAG_LEVELMENU);
    
    return true;
}

MenuItemSprite* DialogLevel::createMenuItemSprite(const char* text, const char* han, int tag, bool cleared) {
    MenuItemSprite* menuItem;
    
    Sprite* normal = Sprite::createWithSpriteFrameName("main_selectbar.png");
    normal->setOpacity(0);
    Sprite* normalText = Sprite::createWithSpriteFrameName(text);
    normalText->setPosition(Vec2(normal->getContentSize().width / 2, normal->getContentSize().height / 2));
    normal->addChild(normalText);
    if (cleared) {
        Sprite* spClear = Sprite::createWithSpriteFrameName("clear_missionclear.png");
        spClear->setPosition(Vec2(normal->getContentSize().width / 2, normal->getContentSize().height / 2));
        spClear->setScale(0.7);
        normal->addChild(spClear);
    }
    
    Sprite* selected = Sprite::createWithSpriteFrameName("main_selectbar.png");
    Sprite* selectedText = Sprite::createWithSpriteFrameName(text);
    selectedText->setPosition(Vec2(selected->getContentSize().width/2, selected->getContentSize().height/2));
    selected->addChild(selectedText);
    Sprite* selHan = Sprite::createWithSpriteFrameName(han);
    selHan->setAnchorPoint(Vec2(1, 0.5));
    selHan->setPosition(Vec2(selected->getContentSize().width * 0.98, selected->getContentSize().height * 0.5));
    selected->addChild(selHan);
    if (cleared) {
        Sprite* spClear = Sprite::createWithSpriteFrameName("clear_missionclear.png");
        spClear->setPosition(Vec2(selected->getContentSize().width / 2, selected->getContentSize().height / 2));
        spClear->setScale(0.7);
        spClear->setOpacity(120);
        selected->addChild(spClear);
    }
    
    menuItem = MenuItemSprite::create(normal, selected, CC_CALLBACK_1(DialogLevel::onMenu, this));
    menuItem->setTag(tag);
    
    return menuItem;
}

void DialogLevel::onMenu(Ref* sender) {
    SoundManager::playButton();
    int tag = ((Node*)sender)->getTag();
    switch (tag) {
        case MENU_TAG_VERYEASY:
        case MENU_TAG_EASY:
        case MENU_TAG_NORMAL:
        case MENU_TAG_HARD:
        case MENU_TAG_VERYHARD:
        case MENU_TAG_IMPOSSIBLE:
        case MENU_TAG_ENDLESS:
            Director::getInstance()->replaceScene(SceneGame::createScene(tag));
            break;
            
        case MENU_TAG_BACK:
            {
                SceneMenu* sceneMenu = (SceneMenu*)getParent();
                sceneMenu->hideDialogLevel();
            }
            break;
    }
}

void DialogLevel::onKeyPressed(EventKeyboard::KeyCode keycode, Event* event) {
}

void DialogLevel::onKeyReleased(EventKeyboard::KeyCode keycode, Event* event) {
    if (keycode == EventKeyboard::KeyCode::KEY_BACK) {
        SoundManager::playButton();
        SceneMenu* sceneMenu = (SceneMenu*)getParent();
        sceneMenu->hideDialogLevel();
    }
}

void DialogLevel::Show() {
    setVisible(true);
    setScale(0);
    ScaleTo* scaleTo = ScaleTo::create(0.5, 1.0);
    ActionInterval* interval = EaseBackOut::create(scaleTo);
    runAction(interval);
    setKeypadEnabled(true);
}

void DialogLevel::Hide() {
    setVisible(false);
    setKeypadEnabled(false);
}
