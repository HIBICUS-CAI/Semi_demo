//
// Created by 蔡元涵 on 2020/8/2.
//

#ifndef SEMI_DEMO_GEAR_H
#define SEMI_DEMO_GEAR_H

#include "Object.h"

class Gear : public Object
{
public:
    Gear(class GameSys *gameSys, class Player *player, Json::Value gearInfo);

    void UpdateObject(float deltatime) override;

    void GearEvent(int gearID);

    const glm::ivec2 &getPlayerLatePosition() const
    {
        return mPlayerLatePosition;
    }

    void setPlayerLatePosition(const glm::ivec2 &mPlayerLatePosition)
    {
        Gear::mPlayerLatePosition = mPlayerLatePosition;
    }

    int getID() const
    {
        return mID;
    }

    bool isUnlock() const
    {
        return mIsUnlock;
    }

    bool isTrigged() const
    {
        return mPlayerTrigged;
    }

private:
    int mID;

    // 是否解锁机关
    bool mIsUnlock;

    // 玩家是否在机关附近
    bool mPlayerTrigged;

    class Player *mPlayer;

    class SpriteComponent *mTexSC;

    class CollisionComponent *mCC;

    glm::ivec2 mPlayerLatePosition;

    std::vector<class BorderDecider *> mBorderDeciders;
};


#endif //SEMI_DEMO_GEAR_H
