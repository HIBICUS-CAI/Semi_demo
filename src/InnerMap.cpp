//
// Created by 蔡元涵 on 2020/6/25.
//

#include "InnerMap.h"
#include "SpriteComponent.h"
#include "ZoneSwitchHouseComponent.h"

InnerMap::InnerMap(class GameSys *gameSys, class Player *player, class House *house) : Object(
        gameSys), mPlayer(player), mHouse(house)
{
    mPlayerLatePosition = gameSys->getInitPos();

//    setPosition(house->getPosition());
    setPosition({house->getThisHouse()["Position"][0].asFloat(),
                 house->getThisHouse()["Position"][1].asFloat()});

    mSC = new SpriteComponent(this, 120);
    mSC->SetTexture(gameSys->GetTexture(house->getThisHouse()["InTex"].asString()));
    mSC->setIsVisible(false);

    setState(Pause);
}

void InnerMap::UpdateObject(float deltatime)
{
    glm::vec2 posDiff = mPlayer->getPosition() - getPosition();
    float xDiff = posDiff.x;
    float yDiff = posDiff.y;
    xDiff *= xDiff;
    yDiff *= yDiff;

    if (xDiff <= 150.f * 150.f && yDiff <= 100.f * 100.f)
    {
        mHouse->getSC()->setIsVisible(false);
        this->getSC()->setIsVisible(true);
    } else
    {
        this->getSC()->setIsVisible(false);
        mHouse->getSC()->setIsVisible(true);
    }
}
