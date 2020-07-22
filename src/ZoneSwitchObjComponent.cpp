//
// Created by 蔡元涵 on 2020/6/22.
//

#include "ZoneSwitchObjComponent.h"
#include "Player.h"
#include "House.h"
#include "BorderDecider.h"
#include "Item.h"
#include "Document.h"

// House
ZoneSwitchObjComponent::ZoneSwitchObjComponent(class Object *owner, class Player *player,
                                               class House *house, int updateOrder)
        : Component(owner, updateOrder), mPlayer(player), mHouse(house),
          mBorderDecider(nullptr), mItem(nullptr), mDocument(nullptr)
{}

// BorderDecider
ZoneSwitchObjComponent::ZoneSwitchObjComponent(class Object *owner, class Player *player,
                                               class BorderDecider *borderDecider,
                                               int updateOrder)
        : Component(owner, updateOrder), mPlayer(player), mBorderDecider(borderDecider),
          mHouse(nullptr), mItem(nullptr), mDocument(nullptr)
{}

// Item
ZoneSwitchObjComponent::ZoneSwitchObjComponent(class Object *owner, class Player *player,
                                               class Item *item,
                                               int updateOrder)
        : Component(owner, updateOrder), mPlayer(player), mItem(item),
          mHouse(nullptr), mBorderDecider(nullptr), mDocument(nullptr)
{}

// Document
ZoneSwitchObjComponent::ZoneSwitchObjComponent(class Object *owner, class Player *player,
                                               class Document *document,
                                               int updateOrder)
        : Component(owner, updateOrder), mPlayer(player), mDocument(document),
          mHouse(nullptr), mBorderDecider(nullptr), mItem(nullptr)
{}

void ZoneSwitchObjComponent::Update(float deltatime)
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

    if (mItem != nullptr)
    {
        glm::ivec2 mapPosition = mPlayer->getMapPositon();
        int deltaRow = mapPosition.x - mItem->getPlayerLatePosition().x;
        int deltaCol = mapPosition.y - mItem->getPlayerLatePosition().y;
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
        mItem->setPlayerLatePosition(mapPosition);
    }

    if (mDocument != nullptr)
    {
        glm::ivec2 mapPosition = mPlayer->getMapPositon();
        int deltaRow = mapPosition.x - mDocument->getPlayerLatePosition().x;
        int deltaCol = mapPosition.y - mDocument->getPlayerLatePosition().y;
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
        mDocument->setPlayerLatePosition(mapPosition);
    }
}
