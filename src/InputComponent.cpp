//
// Created by 蔡元涵 on 2020/6/5.
//

#include "InputComponent.h"
#include "Actor.h"

InputComponent::InputComponent(class Actor *owner) : MoveComponent(owner), mForwardKey(0),
                                                     mBackKey(0), mLeftKey(0), mRightKey(0)
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

    setHorizontalSpeed(horSpeed);
    setVerticalSpeed(verSpeed);

}
