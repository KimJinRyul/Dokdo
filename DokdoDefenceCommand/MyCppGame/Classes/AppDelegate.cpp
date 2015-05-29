#include "AppDelegate.h"
#include "SceneMenu.h"
#include "SceneGame.h"
#include "SoundManager.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    Director* director = Director::getInstance();
    GLView* glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::create(APP_NAME);
        director->setOpenGLView(glview);
    }
    
#if(CC_TARGET_PLATFORM == CC_PLATFORM_MAC || CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
    {
        glview->setFrameSize(480, 800);
        //glview->setFrameSize(360, 600);
        //glview->setFrameSize(240, 400);
    }
#endif
    glview->setDesignResolutionSize(DESIGN_RESOLUTION_WIDTH, DESIGN_RESOLUTION_HEIGHT, ResolutionPolicy::SHOW_ALL);

    //director->setDisplayStats(true);
    director->setAnimationInterval(1.0 / 60);
    
    SoundManager::preloadSounds();

    Scene* scene = SceneMenu::createScene();
    //Scene* scene = SceneMenu::createScene(true, 192, 9876543, 1234, 567, 1024, true);
    director->runWithScene(scene);

    return true;
}

void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();
    SoundManager::stopBGM();
}

void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();
    Scene* runningScene = Director::getInstance()->getRunningScene();
    if(SCENE_TAG_GAME == runningScene->getTag())
    {
        SceneGame* game = (SceneGame*)(runningScene->getChildByTag(LAYER_TAG_GAME));
        if(nullptr != game)
        {
            if(false == game->isPaused())
            {
                SoundManager::playBGM();
            }
        }
    }
    else
    {
        SoundManager::playBGM();
    }
}
