#include "SoundManager.h"
#include "DialogOption.h"

USING_NS_CC;
using namespace CocosDenshion;

void SoundManager::preloadSounds()
{
    SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(1.0);
    SimpleAudioEngine::getInstance()->setEffectsVolume(1.0);
    SimpleAudioEngine::getInstance()->preloadBackgroundMusic("bgm.mp3");

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    	SimpleAudioEngine::getInstance()->preloadEffect("button.ogg");
    	SimpleAudioEngine::getInstance()->preloadEffect("cannonshot01.ogg");
    	SimpleAudioEngine::getInstance()->preloadEffect("enermygunshot01.ogg");
    	SimpleAudioEngine::getInstance()->preloadEffect("explosion01.ogg");
    	SimpleAudioEngine::getInstance()->preloadEffect("explosion02.ogg");
    	SimpleAudioEngine::getInstance()->preloadEffect("gun01.ogg");
    	SimpleAudioEngine::getInstance()->preloadEffect("gunshot01.ogg");
    	SimpleAudioEngine::getInstance()->preloadEffect("missile01.ogg");
#else
    	SimpleAudioEngine::getInstance()->preloadEffect("button.wav");
    	SimpleAudioEngine::getInstance()->preloadEffect("cannonshot01.wav");
    	SimpleAudioEngine::getInstance()->preloadEffect("enermygunshot01.wav");
    	SimpleAudioEngine::getInstance()->preloadEffect("explosion01.wav");
    	SimpleAudioEngine::getInstance()->preloadEffect("explosion02.wav");
    	SimpleAudioEngine::getInstance()->preloadEffect("gun01.wav");
    	SimpleAudioEngine::getInstance()->preloadEffect("gunshot01.wav");
    	SimpleAudioEngine::getInstance()->preloadEffect("missile01.wav");
#endif
}

void SoundManager::playBGM()
{
	if(UserDefault::getInstance()->getBoolForKey(OPTION_KEY_MUSIC, true) &&
	   !SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
	{
		SimpleAudioEngine::getInstance()->playBackgroundMusic("bgm.mp3", true);
	}
}

void SoundManager::stopBGM()
{
	SimpleAudioEngine::getInstance()->stopBackgroundMusic(false);
}

void SoundManager::playButton()
{
	if(UserDefault::getInstance()->getBoolForKey(OPTION_KEY_SOUND, true))
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		SimpleAudioEngine::getInstance()->playEffect("button.ogg");
#else
		SimpleAudioEngine::getInstance()->playEffect("button.wav");
#endif
	}
}

void SoundManager::playEnermyGun()
{
	if(UserDefault::getInstance()->getBoolForKey(OPTION_KEY_SOUND, true))
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	SimpleAudioEngine::getInstance()->playEffect("enermygunshot01.ogg");
#else
	SimpleAudioEngine::getInstance()->playEffect("enermygunshot01.wav");
#endif
	}
}

void SoundManager::playGun1()
{
	if(UserDefault::getInstance()->getBoolForKey(OPTION_KEY_SOUND, true))
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		SimpleAudioEngine::getInstance()->playEffect("gun01.ogg");
#else
		SimpleAudioEngine::getInstance()->playEffect("gun01.wav");
#endif
	}
}

void SoundManager::playGun2()
{
	if(UserDefault::getInstance()->getBoolForKey(OPTION_KEY_SOUND, true))
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		SimpleAudioEngine::getInstance()->playEffect("gunshot01.ogg");
#else
		SimpleAudioEngine::getInstance()->playEffect("gunshot01.wav");
#endif
	}
}

void SoundManager::playCannon()
{
	if(UserDefault::getInstance()->getBoolForKey(OPTION_KEY_SOUND, true))
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		SimpleAudioEngine::getInstance()->playEffect("cannonshot01.ogg");
#else
		SimpleAudioEngine::getInstance()->playEffect("cannonshot01.wav");
#endif
	}
}

void SoundManager::playMissile()
{
	if(UserDefault::getInstance()->getBoolForKey(OPTION_KEY_SOUND, true))
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		SimpleAudioEngine::getInstance()->playEffect("missile01.ogg");
#else
		SimpleAudioEngine::getInstance()->playEffect("missile01.wav");
#endif
	}
}

void SoundManager::playExplosion1()
{
	if(UserDefault::getInstance()->getBoolForKey(OPTION_KEY_SOUND, true))
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		SimpleAudioEngine::getInstance()->playEffect("explosion01.ogg");
#else
		SimpleAudioEngine::getInstance()->playEffect("explosion01.wav");
#endif
	}
}

void SoundManager::playExplosion2()
{
	if(UserDefault::getInstance()->getBoolForKey(OPTION_KEY_SOUND, true))
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		SimpleAudioEngine::getInstance()->playEffect("explosion02.ogg");
#else
		SimpleAudioEngine::getInstance()->playEffect("explosion02.wav");
#endif
	}
}









