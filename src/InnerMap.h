//
// Created by 蔡元涵 on 2020/6/25.
//

#ifndef SEMI_DEMO_INNERMAP_H
#define SEMI_DEMO_INNERMAP_H

#include "Object.h"
#include "Player.h"
#include "House.h"
#include "SpriteComponent.h"

class InnerMap : public Object
{
public:
    InnerMap(class GameSys *gameSys, class Player *player, class House *house);

    Player *getPlayer() const
    {
        return mPlayer;
    }

    void UpdateObject(float deltatime) override;

    const glm::ivec2 &getPlayerLatePosition() const
    {
        return mPlayerLatePosition;
    }

    void setPlayerLatePosition(const glm::ivec2 &mPlayerLatePosition)
    {
        InnerMap::mPlayerLatePosition = mPlayerLatePosition;
    }

    SpriteComponent *getSC() const
    {
        return mSC;
    }

private:
    class Player *mPlayer;

    class House *mHouse;

    glm::ivec2 mPlayerLatePosition;

    class SpriteComponent *mSC;
};


#endif //SEMI_DEMO_INNERMAP_H
