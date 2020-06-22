//
// Created by 蔡元涵 on 2020/6/22.
//

#ifndef SEMI_DEMO_COLLISIONCOMPONENT_H
#define SEMI_DEMO_COLLISIONCOMPONENT_H

#include "Component.h"
#include "Object.h"

class CollisionComponent : public Component
{
public:
    CollisionComponent(class Object *owner);

//    void Update(float deltatime) override;

    float getRadius() const
    {
        return mOwner->getScale() * mRadius;
    }

    void setRadius(float mRadius)
    {
        CollisionComponent::mRadius = mRadius;
    }

    const glm::vec2 &getCenter() const
    {
        return mOwner->getPosition();
    }

private:
    //碰撞半径
    float mRadius;
};

bool IsCollided(const CollisionComponent &self, const CollisionComponent &object);


#endif //SEMI_DEMO_COLLISIONCOMPONENT_H
