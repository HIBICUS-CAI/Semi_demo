//
// Created by 蔡元涵 on 2020/6/16.
//

#include "ZoneSwitchMapComponent.h"
#include "Player.h"
#include "SingleMap.h"

ZoneSwitchMapComponent::ZoneSwitchMapComponent(class Actor *owner, class Player *player,
                                               class SingleMap *singleMap,
                                               int updateOrder)
        : Component(owner, updateOrder), mPlayer(player), mSingleMap(singleMap)
{}

void ZoneSwitchMapComponent::Update(float deltatime)
{
    glm::ivec2 mapPosition = mPlayer->getMapPositon();
    int deltaRow = mapPosition.x - mSingleMap->getPlayerLatePosition().x;
    int deltaCol = mapPosition.y - mSingleMap->getPlayerLatePosition().y;
    float posRow = mOwner->getPosition().x;
    float posCol = mOwner->getPosition().y;

    if (deltaRow != 0)
    {
        posRow += static_cast<float>(deltaRow) * -1024.f;
    }
    if (deltaCol != 0)
    {
        posCol += static_cast<float>(deltaCol) * -768.f;
    }

    mOwner->setPosition({posRow, posCol});
    mSingleMap->setPlayerLatePosition(mapPosition);
}
