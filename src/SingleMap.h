//
// Created by 蔡元涵 on 2020/6/15.
//

#ifndef SEMI_DEMO_SINGLEMAP_H
#define SEMI_DEMO_SINGLEMAP_H

#include <string>
#include <glm.hpp>
#include "Actor.h"
#include "Maps.h"

class SingleMap : public Actor
{
public:
    SingleMap(class GameSys *gameSys, class Maps *maps, std::string &mapPath, int row,
              int col);

    SingleMap(GameSys *gameSys, int row, int col);

    Maps *getMaps() const
    {
        return mMaps;
    }

    const glm::ivec2 &getPlayerLatePosition() const
    {
        return mPlayerLatePosition;
    }

    void setPlayerLatePosition(const glm::ivec2 &mPlayerLatePosition)
    {
        SingleMap::mPlayerLatePosition = mPlayerLatePosition;
    }

private:
    class Maps *mMaps;
    glm::ivec2 mPlayerLatePosition;
};


#endif //SEMI_DEMO_SINGLEMAP_H
