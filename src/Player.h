//
// Created by 蔡元涵 on 2020/6/3.
//

#ifndef SEMI_DEMO_PLAYER_H
#define SEMI_DEMO_PLAYER_H

#include <glm.hpp>
#include "Object.h"

const glm::ivec2 PLAYERINITPOS = glm::ivec2{1, 0};

class Player : public Object
{
public:
    Player(class GameSys *gameSys);

    bool IsPlayer() override
    {
        return true;
    }

    class CollisionComponent *GetCC()
    {
        return mCC;
    }

    int getInputStatus() const
    {
        return mInputStatus;
    }

    void setInputStatus(int mInputStatus)
    {
        Player::mInputStatus = mInputStatus;
    }

    void RevertMove();

private:
    class CollisionComponent *mCC;

    //↑1 →2 ↓3 ←4 ↗5 ↘6 ↙7 ↖8
    int mInputStatus;
};


#endif //SEMI_DEMO_PLAYER_H
