//
// Created by 蔡元涵 on 2020/6/15.
//

#include "SingleMap.h"
#include "SpriteComponent.h"

SingleMap::SingleMap(class GameSys *gameSys, class Maps *maps, std::string &mapPath, int row,
                     int col) : Actor(gameSys), mMaps(maps)
{
    mMaps->AddMap(this);

    //设置初始位置关系,以(1,0)作为初始地图块
    float x_pos = static_cast<float>(row - 1);
    float y_pos = static_cast<float>(col - 0);
    setPosition({x_pos * 1024.f, y_pos * 768.f});
    mLatePosition = {1, 0};

    SpriteComponent *sc = new SpriteComponent(this, 130);
    sc->SetTexture(this->getGameSys()->GetTexture(mapPath));
}

void SingleMap::Move(glm::ivec2 mapPosition)
{
    int deltaRow = mapPosition.x - mLatePosition.x;
    int deltaCol = mapPosition.y - mLatePosition.y;
    float posRow = getPosition().x;
    float posCol = getPosition().y;

    if (deltaRow != 0)
    {
        posRow += static_cast<float>(deltaRow) * -1024.f;
    }
    if (deltaCol != 0)
    {
        posCol += static_cast<float>(deltaCol) * -768.f;
    }

    setPosition({posRow, posCol});

    mLatePosition = mapPosition;
}