//
// Created by 蔡元涵 on 2020/6/5.
//

#ifndef SEMI_DEMO_MOVECOMPONENT_H
#define SEMI_DEMO_MOVECOMPONENT_H

#include <glm.hpp>
#include "Component.h"

class MoveComponent : public Component
{
public:
    MoveComponent(class Object *owner, int updateOrder = 10);

    void Update(float deltatime) override;

    bool SpeedNearZero(float speed, float delta=0.0001f);

    float getHorizontalSpeed() const
    {
        return mHorizontalSpeed;
    }

    void setHorizontalSpeed(float mHorizontalSpeed)
    {
        MoveComponent::mHorizontalSpeed = mHorizontalSpeed;
    }

    float getVerticalSpeed() const
    {
        return mVerticalSpeed;
    }

    void setVerticalSpeed(float mVerticalSpeed)
    {
        MoveComponent::mVerticalSpeed = mVerticalSpeed;
    }

private:
    float mHorizontalSpeed;
    float mVerticalSpeed;
};


#endif //SEMI_DEMO_MOVECOMPONENT_H
