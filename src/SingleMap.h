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

    void Move(glm::ivec2 mapPosition);

private:
    class Maps *mMaps;
    glm::ivec2 mLatePosition;
};


#endif //SEMI_DEMO_SINGLEMAP_H
