//
//  UnitManager.cpp
//  MyCppGame
//
//  Created by Jinryul Kim on 2014. 8. 7..
//
//

#include "UnitManager.h"

std::string UnitManager::getFilePath(int type)
{
    switch(type)
    {
        case UNIT_PKG:          return "pkg_711.png";
        case UNIT_KDX2:         return "kdk_3.png";
        case UNIT_KDX3:         return "kdk_2.png";
        case UNIT_DOKDO:        return "dokdoship.png";
        case UNIT_KSS3:         return "jang01.png";
        case UNIT_E747:         return "e737.png";
        case UNIT_PATROL:       return "patrolship.png";
        case UNIT_DESTROYER:    return "destroyer.png";
        case UNIT_CRUISER:      return "cruiser.png";
        case UNIT_CARRIER:      return "aircraftcarrier.png";
        case UNIT_HELICOPTER:   return "helicopter.png";
        case UNIT_FIGHTER:      return "fighter.png";
        case UNIT_BOMBER:       return "bomber.png";
        case UNIT_STRATEGIC:    return "b52h.png";
        case UNIT_SUBMARINE:    return "sub_j01.png";
        case UNIT_LYNX:         return "lynx01.png";
        case UNIT_F15K:         return "f15k.png";
        default:                return "";
    }
    return "";
}


