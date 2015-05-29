//
//  SpriteScoreBoard.h
//  MyCppGame
//
//  Created by Jinryul Kim on 2014. 7. 31..
//
//

#ifndef __DokdoDefenceCommand__SpriteScoreBoard__
#define __DokdoDefenceCommand__SpriteScoreBoard__

#include "cocos2d.h"
#include "Defines.h"

class SpriteScoreBoard : public cocos2d::Sprite
{
public:
    static SpriteScoreBoard* create();
    void addNumbers();
    
    void setHighScore(int highscore);
    void setScore(int score);
    void addScore(int score);
    int getScore();
    
    void setTime(float time);
    void addTime(float time);
    float getTime();
    
    void setMoney(int money);
    void addMoney(int money);
    int getMoney();
    
private:
    void labelTimeChange();
    void labelScoreChange();
    void labelHighScoreChange();
    void labelMoneyChange();
    
    cocos2d::Label *labelScore, *labelHighScore, *labelTime, *labelMoney;
    int mScore;
    int mHighScore;
    float mTime;
    int mMoney;
    char szTEMP[16];
};

#endif /* defined(__DokdoDefenceCommand__SpriteScoreBoard__) */
