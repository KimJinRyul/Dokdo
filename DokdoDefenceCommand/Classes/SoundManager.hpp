//
//  SoundManager.hpp
//  DokdoDefenceCommand
//
//  Created by 김진율 on 2021/04/02.
//

#ifndef SoundManager_hpp
#define SoundManager_hpp

#include "audio/include/AudioEngine.h"
#include "cocos2d.h"


USING_NS_CC;
using namespace cocos2d::experimental;

class SoundManager
{
public:
    static void preloadSounds();

    static void playBGM();
    static void stopBGM();
    
    static void pauseBGM();
    static void resumeBGM();

    static void playButton();
    static void playEnermyGun();
    static void playGun1();
    static void playGun2();
    static void playCannon();
    static void playMissile();
    static void playExplosion1();
    static void playExplosion2();
    
private:
    static int audioIndexBGM;
};

#endif /* SoundManager_hpp */
