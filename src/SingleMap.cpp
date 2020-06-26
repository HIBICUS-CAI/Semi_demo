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
    int initX = gameSys->getInitPos().x;
    int initY = gameSys->getInitPos().y;
    float x_pos = static_cast<float>(row - initX);
    float y_pos = static_cast<float>(col - initY);
    setPosition({x_pos * 1024.f, y_pos * 768.f});
    mPlayerLatePosition = gameSys->getInitPos();

    SpriteComponent *sc = new SpriteComponent(this, 100);
    sc->SetTexture(this->getGameSys()->GetTexture(mapPath));

    new ZoneSwitchMapComponent(this, this->getMaps()->getPlayer(), this,
                               10);
}