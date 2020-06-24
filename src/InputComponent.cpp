//
// Created by 蔡元涵 on 2020/6/5.
//

#include "InputComponent.h"
#include "Object.h"
#include "Player.h"

InputComponent::InputComponent(class Object *owner, class Player *player) : MoveComponent(
        owner), mForwardKey(0), mBackKey(0), mLeftKey(0), mRightKey(0), mPlayer(player)
{

}

void InputComponent::ProcessInput(const uint8_t *keyState)
{
    float horSpeed = 0.0f;
    if (keyState[mRightKey])
    {
        horSpeed = mHorMoveSpeed;
    }
    if (keyState[mLeftKey])
    {
        horSpeed = -mHorMoveSpeed;
    }

    float verSpeed = 0.0f;
    if (keyState[mForwardKey])
    {
        verSpeed = mVerMoveSpeed;
    }
    if (keyState[mBackKey])
    {
        verSpeed = -mVerMoveSpeed;
    }

    if ((keyState[mForwardKey] && keyState[mRightKey]) ||
        (keyState[mForwardKey] && keyState[mLeftKey]) ||
        (keyState[mBackKey] && keyState[mRightKey]) ||
        (keyState[mBackKey] && keyState[mLeftKey]))
    {
        verSpeed /= 1.414f;
        horSpeed /= 1.414f;
    }

    if (keyState[mForwardKey] && keyState[mBackKey])
    {
        verSpeed = 0.f;
        horSpeed = 0.f;
    }
    if (keyState[mLeftKey] && keyState[mRightKey])
    {
        verSpeed = 0.f;
        horSpeed = 0.f;
    }

    if (keyState[mForwardKey] && !keyState[mRightKey] &&
        !keyState[mBackKey] && !keyState[mLeftKey])
    {
        mPlayer->setInputStatus(1);
    } else if (!keyState[mForwardKey] && keyState[mRightKey] &&
               !keyState[mBackKey] && !keyState[mLeftKey])
    {
        mPlayer->setInputStatus(2);
    } else if (!keyState[mForwardKey] && !keyState[mRightKey] &&
               keyState[mBackKey] && !keyState[mLeftKey])
    {
        mPlayer->setInputStatus(3);
    } else if (!keyState[mForwardKey] && !keyState[mRightKey] &&
               !keyState[mBackKey] && keyState[mLeftKey])
    {
        mPlayer->setInputStatus(4);
    } else if (keyState[mForwardKey] && keyState[mRightKey] &&
               !keyState[mBackKey] && !keyState[mLeftKey])
    {
        mPlayer->setInputStatus(5);
    } else if (!keyState[mForwardKey] && keyState[mRightKey] &&
               keyState[mBackKey] && !keyState[mLeftKey])
    {
        mPlayer->setInputStatus(6);
    } else if (!keyState[mForwardKey] && !keyState[mRightKey] &&
               keyState[mBackKey] && keyState[mLeftKey])
    {
        mPlayer->setInputStatus(7);
    } else if (keyState[mForwardKey] && !keyState[mRightKey] &&
               !keyState[mBackKey] && keyState[mLeftKey])
    {
        mPlayer->setInputStatus(8);
    } else
    {
        mPlayer->setInputStatus(0);
    }

    setHorizontalSpeed(horSpeed);
    setVerticalSpeed(verSpeed);

}
