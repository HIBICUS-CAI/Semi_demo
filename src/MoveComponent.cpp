//
// Created by 蔡元涵 on 2020/6/5.
//

#include <cmath>
#include "MoveComponent.h"
#include "Actor.h"
#include <SDL.h>

MoveComponent::MoveComponent(class Actor *owner, int updateOrder) : Component(owner,
                                                                              updateOrder),
                                                                    mHorizontalSpeed(0.0f),
                                                                    mVerticalSpeed(0.0f)
{

}

void MoveComponent::Update(float deltatime)
{
    float posX = (mOwner->getPosition()).x;
    float posY = (mOwner->getPosition()).y;
    if (!SpeedNearZero(mHorizontalSpeed))
    {
        posX += mHorizontalSpeed * deltatime;
        if (posX < -512.f)
        {
            posX = 510.f;
        } else if (posX > 512.f)
        {
            posX = -510.f;
        }
    }
    if (!SpeedNearZero(mVerticalSpeed))
    {
        posY += mVerticalSpeed * deltatime;
        if (posY < -384.f)
        {
            posY = 382.f;
        } else if (posY > 384.f)
        {
            posY = -382.f;
        }
    }

    glm::vec2 pos = glm::vec2(posX, posY);
    if (pos != mOwner->getPosition())
    {
        mOwner->setPosition(pos);
    }

    SDL_Log("player's position is ( %f , %f )", mOwner->getPosition().x,
            mOwner->getPosition().y);
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
