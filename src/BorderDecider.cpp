//
// Created by 蔡元涵 on 2020/6/22.
//

#include "BorderDecider.h"
#include "CollisionComponent.h"
#include "ZoneSwitchObjComponent.h"

BorderDecider::BorderDecider(class GameSys *gameSys, class Player *player) : Object(gameSys),
                                                                             mCC(nullptr),
                                                                             mPlayer(player)
{
    mPlayerLatePosition = gameSys->getInitPos();

    new ZoneSwitchObjComponent(this, player, this, 10);

    mCC = new CollisionComponent(this);
    mCC->setRadius(5.f);
}

void BorderDecider::UpdateObject(float deltatime)
{
    if (IsCollided(*mCC, *(mPlayer->GetCC())))
    {
        mPlayer->RevertMove();
    }
}

void BorderDecider::SetCCRadius(int radius)
{
    mCC->setRadius(radius);
}

void BorderDecider::DeltaMove(glm::vec2 ownerDeltaMove)
{
    ownerDeltaMove.x = ownerDeltaMove.x + getPosition().x;
    ownerDeltaMove.y = ownerDeltaMove.y + getPosition().y;
    setPosition(ownerDeltaMove);
}
