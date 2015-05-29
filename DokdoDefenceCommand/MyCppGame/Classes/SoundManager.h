#ifndef __DokdoDefenceCommand__SoundManager__
#define __DokdoDefenceCommand__SoundManager__

#include "SimpleAudioEngine.h"
#include "cocos2d.h"

class SoundManager
{
public:
	static void preloadSounds();

	static void playBGM();
	static void stopBGM();

	static void playButton();
	static void playEnermyGun();
	static void playGun1();
	static void playGun2();
	static void playCannon();
	static void playMissile();
	static void playExplosion1();
	static void playExplosion2();
};

#endif /* defined(__DokdoDefenceCommand__SoundManager__) */
