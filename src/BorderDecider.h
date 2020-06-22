//
// Created by 蔡元涵 on 2020/6/22.
//

#ifndef SEMI_DEMO_BORDERDECIDER_H
#define SEMI_DEMO_BORDERDECIDER_H

#include "Object.h"
#include "Player.h"

class BorderDecider : public Object
{
public:
    BorderDecider(class GameSys *gameSys, class Player *player);

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
        BorderDecider::mPlayerLatePosition = mPlayerLatePosition;
    }

private:
    class CollisionComponent *mCC;

    class Player *mPlayer;

    glm::ivec2 mPlayerLatePosition;
};


#endif //SEMI_DEMO_BORDERDECIDER_H
