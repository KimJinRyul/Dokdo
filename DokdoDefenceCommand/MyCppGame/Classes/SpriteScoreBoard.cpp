//
//  SpriteScoreBoard.cpp
//  MyCppGame
//
//  Created by Jinryul Kim on 2014. 7. 31..
//
//

#include "SpriteScoreBoard.h"
#include "LabelCreater.h"

USING_NS_CC;

SpriteScoreBoard* SpriteScoreBoard::create()
{
    SpriteScoreBoard* scoreBoard = new SpriteScoreBoard();
    if(scoreBoard && scoreBoard->initWithSpriteFrameName("score_board.png"))
    {
        scoreBoard->autorelease();
        scoreBoard->addNumbers();
        return scoreBoard;
    }
    CC_SAFE_DELETE(scoreBoard);
    return nullptr;
}

void SpriteScoreBoard::addNumbers()
{
    labelScore = LabelCreater::createLabel("000000000", "OneSlot.ttf", 32);
    labelScore->setPosition(Vec2(110, 57));
    addChild(labelScore);
    
    labelHighScore = LabelCreater::createLabel("000000000", "OneSlot.ttf", 22);
    labelHighScore->setPosition(Vec2(110, 12));
    addChild(labelHighScore);
    
    labelTime = LabelCreater::createLabel("00:00", "OneSlot.ttf", 21);
    labelTime->setPosition(Vec2(270, 67));
    addChild(labelTime);
    
    labelMoney = LabelCreater::createLabel("000000000", "OneSlot.ttf", 21);
    labelMoney->setPosition(Vec2(365, 67));
    addChild(labelMoney);
}

void SpriteScoreBoard::setHighScore(int highscore)
{
    mHighScore = highscore;
    labelHighScoreChange();
}

void SpriteScoreBoard::setScore(int score)
{
    mScore = score;
    labelScoreChange();
    if(mHighScore < mScore)
    {
        setHighScore(mScore);
    }
}

void SpriteScoreBoard::addScore(int score)
{
    mScore += score;
    labelScoreChange();
    if(mHighScore < mScore)
    {
        setHighScore(mScore);
    }
}

int SpriteScoreBoard::getScore()
{
    return mScore;
}

void SpriteScoreBoard::setTime(float time)
{
    mTime = time;
    labelTimeChange();
}

void SpriteScoreBoard::addTime(float time)
{
    float old = mTime;
    mTime += time;
    
    // 실제 화면 갱신이 필요한 경우에만 갱신
    if((int)mTime - (int)old >= 1)
    {
        labelTimeChange();
    }
}

float SpriteScoreBoard::getTime()
{
    return mTime;
}

void SpriteScoreBoard::setMoney(int money)
{
    mMoney = money;
    labelMoneyChange();
}

void SpriteScoreBoard::addMoney(int money)
{
    mMoney += money;
    labelMoneyChange();
}

int SpriteScoreBoard::getMoney()
{
    return mMoney;
}

void SpriteScoreBoard::labelTimeChange()
{
    int minute = 0;
    int second = 0;
    
    float temp = mTime;
    while(temp >= 60)
    {
        minute++;
        temp -= 60;
    }
    second = temp;
    
    sprintf(szTEMP, "%02d:%02d", minute, second);
    labelTime->setString(szTEMP);
}

void SpriteScoreBoard::labelScoreChange()
{
    sprintf(szTEMP, "%09d", mScore);
    labelScore->setString(szTEMP);
}

void SpriteScoreBoard::labelHighScoreChange()
{
    sprintf(szTEMP, "%09d", mHighScore);
    labelHighScore->setString(szTEMP);
}

void SpriteScoreBoard::labelMoneyChange()
{
    sprintf(szTEMP, "%09d", mMoney);
    labelMoney->setString(szTEMP);
}
