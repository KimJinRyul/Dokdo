//
//  SpriteScoreBoard.hpp
//  DokdoDefenceCommand
//
//  Created by 김진율 on 2021/04/02.
//

#ifndef SpriteScoreBoard_hpp
#define SpriteScoreBoard_hpp

#include "cocos2d.h"
#include "Defines.h"

USING_NS_CC;

class SpriteScoreBoard : public Sprite
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
    
    Label *labelScore, *labelHighScore, *labelTime, *labelMoney;
    int mScore;
    int mHighScore;
    float mTime;
    int mMoney;
    char szTEMP[16];
};

#endif /* SpriteScoreBoard_hpp */
