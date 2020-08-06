//
// Created by 蔡元涵 on 2020/6/22.
//

#include "House.h"
#include "BorderDecider.h"
#include "CollisionComponent.h"
#include "ZoneSwitchObjComponent.h"

House::House(GameSys *gameSys, Player *player) : Object(gameSys), mPlayer(player),
                                                 mIsPlayerNearHouse(false)
{
    //TODO 此处需要修改
    setID(0);

    int initX = gameSys->getInitPos().x;
    int initY = gameSys->getInitPos().y;
    mPlayerLatePosition = gameSys->getInitPos();
    Json::Value Houses = getGameSys()->GetInitObjRoot()["Houses"];
//    Json::Value ThisHouse;
    for (int i = 0; i < Houses.size(); ++i)
    {
        if (Houses[i]["ID"] == mID)
        {
            ThisHouse = Houses[i];
            break;
        }
    }

    float thisX = static_cast<float>(ThisHouse["MapPos"][0].asInt() - initX);
    float thisY = static_cast<float>(ThisHouse["MapPos"][1].asInt() - initY);
    thisX = thisX * 1024.f + ThisHouse["Position"][0].asFloat();
    thisY = thisY * 768.f + ThisHouse["Position"][1].asFloat();
//    float thisX = ThisHouse["Position"][0].asFloat();
//    float thisY = ThisHouse["Position"][1].asFloat();
    setPosition({thisX, thisY});

    mSC = new SpriteComponent(this, 120);
    mSC->SetTexture(gameSys->GetTexture(ThisHouse["OutTex"].asString()));

    mCC = new CollisionComponent(this);
    mCC->setRadius(180.f * 1.414f);     //在边角乱按的时候会卡出边界??

    new ZoneSwitchObjComponent(this, player, this, 10);

    BorderDecider *bd;
    float x = getPosition().x - 150.f;
    float y = getPosition().y - 100.f;

    for (int i = 0; i < 40; ++i)
    {
        bd = new BorderDecider(gameSys, player);
        bd->setPosition({x, y + (static_cast<float>(i)) * 5.f});
        mBorderDeciders.emplace_back(bd);
    }

    y += 200.f;
    for (int i = 0; i < 60; ++i)
    {
        bd = new BorderDecider(gameSys, player);
        bd->setPosition({x + (static_cast<float>(i)) * 5.f, y});
        mBorderDeciders.emplace_back(bd);
    }

    x += 300.f;
    for (int i = 0; i < 40; ++i)
    {
        bd = new BorderDecider(gameSys, player);
        bd->setPosition({x, y - (static_cast<float>(i)) * 5.f});
        mBorderDeciders.emplace_back(bd);
    }

    for (auto bd :mBorderDeciders)
    {
        bd->setState(Pause);
    }

    mInnerMap = new InnerMap(gameSys, player, this);
}

void House::UpdateObject(float deltatime)
{
    if (IsCollided(*mCC, *(getPlayer()->GetCC())))
    {
        mIsPlayerNearHouse = true;
        for (auto bd : mBorderDeciders)
        {
            bd->setState(Active);
        }
        mInnerMap->setState(Active);
    } else
    {
        if (mIsPlayerNearHouse)
        {
            for (auto bd : mBorderDeciders)
            {
                bd->setState(Pause);
            }
            mInnerMap->setState(Pause);

            mIsPlayerNearHouse = false;
        }
    }
}
