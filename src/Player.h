//
// Created by 蔡元涵 on 2020/6/3.
//

#ifndef SEMI_DEMO_PLAYER_H
#define SEMI_DEMO_PLAYER_H

#include <glm.hpp>
#include "Object.h"

class Player : public Object
{
public:
    Player(class GameSys *gameSys);

    bool IsPlayer() override
    {
        return true;
    }
};


#endif //SEMI_DEMO_PLAYER_H
