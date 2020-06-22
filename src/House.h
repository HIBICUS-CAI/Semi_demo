//
// Created by 蔡元涵 on 2020/6/22.
//

#ifndef SEMI_DEMO_HOUSE_H
#define SEMI_DEMO_HOUSE_H

#include <vector>
#include "Object.h"
#include "Player.h"

class House : public Object
{
public:
    House(class GameSys *gameSys, class Player *player);

    void UpdateObject(float deltatime) override;

    Player *getPlayer() const
    {
        return mPlayer;
    }

    int getID() const
    {
        return mID;
    }

    void setID(int mId)
    {
        mID = mId;
    }

    const glm::ivec2 &getPlayerLatePosition() const
    {
        return mPlayerLatePosition;
    }

    void setPlayerLatePosition(const glm::ivec2 &mPlayerLatePosition)
    {
        House::mPlayerLatePosition = mPlayerLatePosition;
    }

private:
    int mID;
    class Player *mPlayer;

    class CollisionComponent *mCC;

    std::vector<class BorderDecider *> mBorderDeciders;

    glm::ivec2 mPlayerLatePosition;
};


#endif //SEMI_DEMO_HOUSE_H
