//
// Created by 蔡元涵 on 2020/8/2.
//

#include "Gear.h"
#include "Player.h"
#include "BorderDecider.h"
#include "SpriteComponent.h"
#include "ZoneSwitchObjComponent.h"
#include "CollisionComponent.h"

Gear::Gear(class GameSys *gameSys, class Player *player, Json::Value gearInfo) :
        Object(gameSys), mPlayer(player), mIsUnlock(false), mPlayerTrigged(false)
{
    mID = gearInfo["ID"].asInt();

    glm::ivec2 initPos = gameSys->getInitPos();
    mPlayerLatePosition = initPos;
    glm::ivec2 mapPos = {gearInfo["MapPos"][0].asInt(), gearInfo["MapPos"][1].asInt()};
    glm::vec2 position = {gearInfo["Position"][0].asFloat(),
                          gearInfo["Position"][1].asFloat()};
    setPosition(Tools::CountPosition(initPos, mapPos, position));

    mTexSC = new SpriteComponent(this, 115);
    mTexSC->SetTexture(gameSys->GetTexture(gearInfo["Tex"].asString()));

    new ZoneSwitchObjComponent(this, player, this);

    mCC = new CollisionComponent(this);
    float radius = (gearInfo["Width"].asFloat() > gearInfo["Height"].asFloat()
                    ? gearInfo["Width"].asFloat() : gearInfo["Height"].asFloat());
    mCC->setRadius(radius * 1.414f);

    gameSys->AddGearToSys(this);

    BorderDecider *bd;
    float x = getPosition().x - gearInfo["Width"].asFloat() / 2.f;
    float y = getPosition().y - gearInfo["Height"].asFloat() / 2.f;
    for (int i = 0; i < gearInfo["Height"].asInt() / 5; ++i)
    {
        bd = new BorderDecider(gameSys, player);
        bd->setPosition({x, y + (static_cast<float>(i)) * 5.f});
        mBorderDeciders.emplace_back(bd);
    }
    y += gearInfo["Height"].asFloat();
    for (int i = 0; i < gearInfo["Width"].asInt() / 5; ++i)
    {
        bd = new BorderDecider(gameSys, player);
        bd->setPosition({x + (static_cast<float>(i)) * 5.f, y});
        mBorderDeciders.emplace_back(bd);
    }
    x += gearInfo["Width"].asFloat();
    for (int i = 0; i < gearInfo["Height"].asInt() / 5; ++i)
    {
        bd = new BorderDecider(gameSys, player);
        bd->setPosition({x, y - (static_cast<float>(i)) * 5.f});
        mBorderDeciders.emplace_back(bd);
    }
    y -= gearInfo["Height"].asFloat();
    for (int i = 0; i < gearInfo["Width"].asInt() / 5; ++i)
    {
        bd = new BorderDecider(gameSys, player);
        bd->setPosition({x - (static_cast<float>(i)) * 5.f, y});
        mBorderDeciders.emplace_back(bd);
    }
    for (auto bd : mBorderDeciders)
    {
        bd->setState(Pause);
    }
}

void Gear::UpdateObject(float deltatime)
{
    if (!mIsUnlock)
    {
        if (IsCollided(*mCC, *(mPlayer->GetCC())))
        {
            mPlayerTrigged = true;
            for (auto bd : mBorderDeciders)
            {
                bd->setState(Active);
            }
        } else
        {
            mPlayerTrigged = false;
            for (auto bd : mBorderDeciders)
            {
                bd->setState(Pause);
            }
        }
    }
}

void Gear::GearEvent(int gearID)
{
    switch (gearID)
    {
        case 0:
            mIsUnlock = true;
            mPlayer->AddGearToRecord(gearID);
            for (auto bd : mBorderDeciders)
            {
                bd->setState(Pause);
            }

            break;
        case 1:
            mIsUnlock = true;
            mPlayer->AddGearToRecord(gearID);
            for (auto bd : mBorderDeciders)
            {
                bd->setState(Pause);
            }

            break;
    }
}
