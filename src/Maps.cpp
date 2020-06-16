//
// Created by 蔡元涵 on 2020/6/15.
//

#include "Maps.h"
#include "Player.h"

Maps::Maps(GameSys *gameSys, Player *player) : Actor(gameSys), mPlayer(player)
{
    //地图贴图路径
    mMapTexs[0][0] = "../Assets/1.png";
    mMapTexs[1][0] = "../Assets/2.png";
    mMapTexs[2][0] = "../Assets/3.png";
    mMapTexs[0][1] = "../Assets/4.png";
    mMapTexs[1][1] = "../Assets/5.png";
    mMapTexs[2][1] = "../Assets/6.png";
    mMapTexs[0][2] = "../Assets/7.png";
    mMapTexs[1][2] = "../Assets/8.png";
    mMapTexs[2][2] = "../Assets/9.png";

    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            new SingleMap(this->getGameSys(), this, mMapTexs[i][j], i, j);
        }
    }
}

void Maps::AddMap(class SingleMap *singleMap)
{
    mMaps.emplace_back(singleMap);
}