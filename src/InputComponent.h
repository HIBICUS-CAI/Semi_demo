//
// Created by 蔡元涵 on 2020/6/5.
//

#ifndef SEMI_DEMO_INPUTCOMPONENT_H
#define SEMI_DEMO_INPUTCOMPONENT_H

#include <cstdint>
#include "MoveComponent.h"

class InputComponent : public MoveComponent
{
public:
    InputComponent(class Actor *owner);

    void ProcessInput(const uint8_t *keyState) override;

    void OnUpdateWorldTransform() override
    {
        //此处可以监控所有actor的移动
    }

    float getHorMoveSpeed() const
    {
        return mHorMoveSpeed;
    }

    void setHorMoveSpeed(float mHorMoveSpeed)
    {
        InputComponent::mHorMoveSpeed = mHorMoveSpeed;
    }

    float getVerMoveSpeed() const
    {
        return mVerMoveSpeed;
    }

    void setVerMoveSpeed(float mVerMoveSpeed)
    {
        InputComponent::mVerMoveSpeed = mVerMoveSpeed;
    }

    int getForwardKey() const
    {
        return mForwardKey;
    }

    void setForwardKey(int mForwardKey)
    {
        InputComponent::mForwardKey = mForwardKey;
    }

    int getBackKey() const
    {
        return mBackKey;
    }

    void setBackKey(int mBackKey)
    {
        InputComponent::mBackKey = mBackKey;
    }

    int getLeftKey() const
    {
        return mLeftKey;
    }

    void setLeftKey(int mLeftKey)
    {
        InputComponent::mLeftKey = mLeftKey;
    }

    int getRightKey() const
    {
        return mRightKey;
    }

    void setRightKey(int mRightKey)
    {
        InputComponent::mRightKey = mRightKey;
    }

private:
    float mHorMoveSpeed;
    float mVerMoveSpeed;

    int mForwardKey;
    int mBackKey;
    int mLeftKey;
    int mRightKey;
};


#endif //SEMI_DEMO_INPUTCOMPONENT_H
