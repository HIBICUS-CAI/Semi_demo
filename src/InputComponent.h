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
    InputComponent(class Object *owner, class Player *player);

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

    int getTalkKey() const
    {
        return mTalkKey;
    }

    void setTalkKey(int mTalkKey)
    {
        InputComponent::mTalkKey = mTalkKey;
    }

    int getDebugKey() const
    {
        return mDebugKey;
    }

    void setDebugKey(int mDebugKey)
    {
        InputComponent::mDebugKey = mDebugKey;
    }

    int getCancelDebugKey() const
    {
        return mCancelDebugKey;
    }

    void setCancelDebugKey(int mCancelDebugKey)
    {
        InputComponent::mCancelDebugKey = mCancelDebugKey;
    }

private:
    float mHorMoveSpeed;
    float mVerMoveSpeed;

    class Player *mPlayer;

    int mForwardKey;
    int mBackKey;
    int mLeftKey;
    int mRightKey;

    int mTalkKey;

    // 用于游戏调试输出信息
    int mDebugKey;
    int mCancelDebugKey;
    bool mIsPrinting;
};


#endif //SEMI_DEMO_INPUTCOMPONENT_H
