//
// Created by 蔡元涵 on 2020/6/5.
//

#include <cmath>
#include "MoveComponent.h"
#include "Object.h"
#include <SDL.h>

MoveComponent::MoveComponent(class Object *owner, int updateOrder) : Component(owner,
                                                                               updateOrder),
                                                                     mHorizontalSpeed(0.0f),
                                                                     mVerticalSpeed(0.0f)
{

}

void MoveComponent::Update(float deltatime)
{
    float posX = (mOwner->getPosition()).x;
    float posY = (mOwner->getPosition()).y;
    int posMapRow = (mOwner->getMapPositon()).x;
    int posMapCol = (mOwner->getMapPositon()).y;
    if (!SpeedNearZero(mHorizontalSpeed))
    {
        posX += mHorizontalSpeed * deltatime;

        //此处需要根据地图大小修改数值
        if (posX < -512.f && mOwner->IsPlayer())
        {
            if (posMapRow - 1 >= 0)
            {
                posX = 510.f;
                posMapRow -= 1;
            } else
            {
                posX = -511.f;
                SDL_Log("u've received left border.");
            }
        } else if (posX > 512.f && mOwner->IsPlayer())
        {
            if (posMapRow + 1 <= 2)
            {
                posX = -510.f;
                posMapRow += 1;
            } else
            {
                posX = 511.f;
                SDL_Log("u've received right border.");
            }
        }
    }
    if (!SpeedNearZero(mVerticalSpeed))
    {
        posY += mVerticalSpeed * deltatime;
        if (posY < -384.f && mOwner->IsPlayer())
        {
            if (posMapCol - 1 >= 0)
            {
                posY = 382.f;
                posMapCol -= 1;
            } else
            {
                posY = -383.f;
                SDL_Log("u've received bottom border.");
            }

        } else if (posY > 384.f && mOwner->IsPlayer())
        {
            if (posMapCol + 1 <= 2)
            {
                posY = -382.f;
                posMapCol += 1;
            } else
            {
                posY = 383.f;
                SDL_Log("u've received top border.");
            }
        }
    }

    glm::vec2 pos = glm::vec2(posX, posY);
    if (pos != mOwner->getPosition())
    {
        mOwner->setPosition(pos);
    }

    if (mOwner->IsPlayer())
    {
        mOwner->setMapPositon(posMapRow, posMapCol);
    }

//    SDL_Log("player's position is ( %f , %f )", mOwner->getPosition().x,
//            mOwner->getPosition().y);
}

bool MoveComponent::SpeedNearZero(float speed, float delta)
{
    if (fabs(speed) <= delta)
    {
        return true;
    } else
    {
        return false;
    }
}
