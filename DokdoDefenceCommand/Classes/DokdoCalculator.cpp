//
//  DokdoCalculator.cpp
//  DokdoDefenceCommand
//
//  Created by 김진율 on 2021/04/02.
//

#include "DokdoCalculator.hpp"

float DokdoCalculator::getDokdoCoolTime(int spm, int lv) {
    return 60.0 / getDokdoSPM(spm, lv);
}

int DokdoCalculator::getDokdoRange(int base, int lv) {
    return base + (5 * lv);
}

int DokdoCalculator::getDokdoSPM(int base, int lv) {
    return base * (1.0 + (0.005 * lv));
}

int DokdoCalculator::getDokdoDamage(int base, int lv) {
    return base * (1.0 + (DOKDO_POWER_RATE * lv));
}

int DokdoCalculator::getUnitHP(int base, int lv) {
    return base * (1.0 + (UNIT_HP_RATE * lv));
}

int DokdoCalculator::getUnitRange(int base, int lv) {
    return base * (1.0 + (UNIT_RANGE_RAGE * lv));
}

int DokdoCalculator::getUnitSPM(int base, int lv) {
    return base * (1.0 + (UNIT_SPM_RATE * lv));
}

int DokdoCalculator::getUnitDamage(int base, int lv) {
    return base * (1.0 + (UNIT_POWER_RATE * lv));
}

int DokdoCalculator::getUnitPrice(int base, int lv, int dc) {
    return base - (lv * dc);
}

int DokdoCalculator::getUpgradePrice(int base, int lv) {
    // 1 ~ 20배 가격
    if(lv >= MAX_LEVEL)
        return 0;
    return ((base * 20.f) * (lv + 1)) / MAX_LEVEL;
}

time_t DokdoCalculator::getCurrentDate() {
    timeval tv;
    gettimeofday(&tv, nullptr);
    time_t timep = tv.tv_sec;
    return timep;
}

long DokdoCalculator::getCurrentTime() {
    timeval tv;
    gettimeofday(&tv, nullptr);
    return tv.tv_usec / 1000 + tv.tv_sec * 1000;
}

float DokdoCalculator::getDistance(Vec2 pt1, Vec2 pt2) {
    float x = pt1.x - pt2.x;
    float y = pt1.y - pt2.y;
    return sqrtf((x * x) + (y * y));
}
