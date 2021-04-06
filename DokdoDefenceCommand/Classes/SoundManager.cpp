//
//  SoundManager.cpp
//  DokdoDefenceCommand
//
//  Created by 김진율 on 2021/04/02.
//

#include "SoundManager.hpp"
#include "DialogOption.hpp"
#include "Defines.h"

int SoundManager::audioIndexBGM = -1;

void SoundManager::preloadSounds() {
//    SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(1.0);
//    SimpleAudioEngine::getInstance()->setEffectsVolume(1.0);
//    SimpleAudioEngine::getInstance()->preloadBackgroundMusic("bgm.mp3");

//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//        SimpleAudioEngine::getInstance()->preloadEffect("button.ogg");
//        SimpleAudioEngine::getInstance()->preloadEffect("cannonshot01.ogg");
//        SimpleAudioEngine::getInstance()->preloadEffect("enermygunshot01.ogg");
//        SimpleAudioEngine::getInstance()->preloadEffect("explosion01.ogg");
//        SimpleAudioEngine::getInstance()->preloadEffect("explosion02.ogg");
//        SimpleAudioEngine::getInstance()->preloadEffect("gun01.ogg");
//        SimpleAudioEngine::getInstance()->preloadEffect("gunshot01.ogg");
//        SimpleAudioEngine::getInstance()->preloadEffect("missile01.ogg");
//#else
//        SimpleAudioEngine::getInstance()->preloadEffect("button.wav");
//        SimpleAudioEngine::getInstance()->preloadEffect("cannonshot01.wav");
//        SimpleAudioEngine::getInstance()->preloadEffect("enermygunshot01.wav");
//        SimpleAudioEngine::getInstance()->preloadEffect("explosion01.wav");
//        SimpleAudioEngine::getInstance()->preloadEffect("explosion02.wav");
//        SimpleAudioEngine::getInstance()->preloadEffect("gun01.wav");
//        SimpleAudioEngine::getInstance()->preloadEffect("gunshot01.wav");
//        SimpleAudioEngine::getInstance()->preloadEffect("missile01.wav");
//#endif
}

void SoundManager::playBGM() {
//    if (UserDefault::getInstance()->getBoolForKey(OPTION_KEY_MUSIC, true) &&
//       !SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying()) {
//        SimpleAudioEngine::getInstance()->playBackgroundMusic("bgm.mp3", true);
//    }
    stopBGM();
    if(UserDefault::getInstance()->getBoolForKey(OPTION_KEY_MUSIC, true)) {
        audioIndexBGM = AudioEngine::play2d("bgm.mp3", true);
    }
}

void SoundManager::stopBGM() {
//    SimpleAudioEngine::getInstance()->stopBackgroundMusic(false);
    if(audioIndexBGM != -1) {
        AudioEngine::stop(audioIndexBGM);
        audioIndexBGM = -1;
    }
}

void SoundManager::pauseBGM() {
    if(audioIndexBGM != -1) {
        AudioEngine::setVolume(audioIndexBGM, 0.f);
//        AudioEngine::pause(audioIndexBGM);
    }
}

void SoundManager::resumeBGM() {
    if(audioIndexBGM != -1) {
        AudioEngine::setVolume(audioIndexBGM, 1.f);
//        AudioEngine::resume(audioIndexBGM);
    }
}

void SoundManager::playButton() {
    if (UserDefault::getInstance()->getBoolForKey(OPTION_KEY_SOUND, true)) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        AudioEngine::play2d("button.ogg");
#else
        AudioEngine::play2d("button.wav");
#endif
    }
}

void SoundManager::playEnermyGun() {
    if (UserDefault::getInstance()->getBoolForKey(OPTION_KEY_SOUND, true)) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        AudioEngine::play2d("enermygunshot01.ogg");
#else
        AudioEngine::play2d("enermygunshot01.wav");
#endif
    }
}

void SoundManager::playGun1() {
    if (UserDefault::getInstance()->getBoolForKey(OPTION_KEY_SOUND, true)) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        AudioEngine::play2d("gun01.ogg");
#else
        AudioEngine::play2d("gun01.wav");
#endif
    }
}

void SoundManager::playGun2() {
    if (UserDefault::getInstance()->getBoolForKey(OPTION_KEY_SOUND, true)) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        AudioEngine::play2d("gunshot01.ogg");
#else
        AudioEngine::play2d("gunshot01.wav");
#endif
    }
}

void SoundManager::playCannon() {
    if (UserDefault::getInstance()->getBoolForKey(OPTION_KEY_SOUND, true)) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        AudioEngine::play2d("cannonshot01.ogg");
#else
        AudioEngine::play2d("cannonshot01.wav");
#endif
    }
}

void SoundManager::playMissile() {
    if (UserDefault::getInstance()->getBoolForKey(OPTION_KEY_SOUND, true)) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        AudioEngine::play2d("missile01.ogg");
#else
        AudioEngine::play2d("missile01.wav");
#endif
    }
}

void SoundManager::playExplosion1() {
    if (UserDefault::getInstance()->getBoolForKey(OPTION_KEY_SOUND, true)) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        AudioEngine::play2d("explosion01.ogg");
#else
        AudioEngine::play2d("explosion01.wav");
#endif
    }
}

void SoundManager::playExplosion2() {
    if(UserDefault::getInstance()->getBoolForKey(OPTION_KEY_SOUND, true)) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        AudioEngine::play2d("explosion02.ogg");
#else
        AudioEngine::play2d("explosion02.wav");
#endif
    }
}
