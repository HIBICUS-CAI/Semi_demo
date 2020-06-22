//
// Created by 蔡元涵 on 2020/6/22.
//

#include "House.h"
#include "BorderDecider.h"
#include "SpriteComponent.h"
#include "CollisionComponent.h"
#include "ZoneSwitchHouseComponent.h"

House::House(GameSys *gameSys, Player *player) : Object(gameSys), mPlayer(player),
                                                 mPlayerLatePosition({1, 0})
{
    setPosition({200.f, 100.f});
    setID(1);

    SpriteComponent *sc = new SpriteComponent(this, 110);
    sc->SetTexture(gameSys->GetTexture("../Assets/house.png"));

    mCC = new CollisionComponent(this);
    mCC->setRadius(150.f * 1.414f);

    new ZoneSwitchHouseComponent(this, player, this, 10);

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
}

void House::UpdateObject(float deltatime)
{
    if (IsCollided(*mCC, *(getPlayer()->GetCC())))
    {
        for (auto bd : mBorderDeciders)
        {
            bd->setState(Active);
        }
    } else
    {
        for (auto bd : mBorderDeciders)
        {
            bd->setState(Pause);
        }
    }
}
