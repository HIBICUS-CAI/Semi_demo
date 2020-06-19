//
// Created by 蔡元涵 on 2020/6/15.
//

#ifndef SEMI_DEMO_MAPS_H
#define SEMI_DEMO_MAPS_H

#include <string>
#include <array>
#include <vector>
#include "Object.h"
#include "SingleMap.h"
#include "Player.h"

//地图3*3
typedef std::array<std::string, 3> row_type;
typedef std::array<row_type, 3> array_type;

class Maps : public Object
{
public:
    Maps(class GameSys *gameSys, class Player *player);

    void AddMap(class SingleMap *singleMap);

    const array_type &getMapTexs() const
    {
        return mMapTexs;
    }

    Player *getPlayer() const
    {
        return mPlayer;
    }

private:
    array_type mMapTexs;
    std::vector<class SingleMap *> mMaps;

    class Player *mPlayer;
};


#endif //SEMI_DEMO_MAPS_H
