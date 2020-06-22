//
// Created by 蔡元涵 on 2020/6/22.
//

#include "ZoneSwitchHouseComponent.h"
#include "Player.h"
#include "House.h"
#include "BorderDecider.h"

ZoneSwitchHouseComponent::ZoneSwitchHouseComponent(class Object *owner, class Player *player,
                                                   class House *house, int updateOrder)
        : Component(owner, updateOrder), mPlayer(player), mHouse(house),
          mBorderDecider(nullptr)
{}

ZoneSwitchHouseComponent::ZoneSwitchHouseComponent(class Object *owner, class Player *player,
                                                   class BorderDecider *borderDecider,
                                                   int updateOrder)
        : Component(owner, updateOrder), mPlayer(player), mBorderDecider(borderDecider),
          mHouse(nullptr)
{}

void ZoneSwitchHouseComponent::Update(float deltatime)
{
    if (mHouse != nullptr)
    {
        glm::ivec2 mapPosition = mPlayer->getMapPositon();
        int deltaRow = mapPosition.x - mHouse->getPlayerLatePosition().x;
        int deltaCol = mapPosition.y - mHouse->getPlayerLatePosition().y;
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
        mHouse->setPlayerLatePosition(mapPosition);
    }

    if (mBorderDecider != nullptr)
    {
        glm::ivec2 mapPosition = mPlayer->getMapPositon();
        int deltaRow = mapPosition.x - mBorderDecider->getPlayerLatePosition().x;
        int deltaCol = mapPosition.y - mBorderDecider->getPlayerLatePosition().y;
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
        mBorderDecider->setPlayerLatePosition(mapPosition);
    }
}
