//
// Created by 蔡元涵 on 2020/6/15.
//

#include "SingleMap.h"
#include "SpriteComponent.h"
#include "ZoneSwitchMapComponent.h"

SingleMap::SingleMap(class GameSys *gameSys, class Maps *maps, std::string &mapPath, int row,
                     int col) : Object(gameSys), mMaps(maps)
{
    mMaps->AddMap(this);

    //设置初始位置关系,以(1,0)作为初始地图块
    float x_pos = static_cast<float>(row - 1);
    float y_pos = static_cast<float>(col - 0);
    setPosition({x_pos * 1024.f, y_pos * 768.f});
    mPlayerLatePosition = {1, 0};

    SpriteComponent *sc = new SpriteComponent(this, 130);
    sc->SetTexture(this->getGameSys()->GetTexture(mapPath));

    new ZoneSwitchMapComponent(this, this->getMaps()->getPlayer(), this,
                               10);
}