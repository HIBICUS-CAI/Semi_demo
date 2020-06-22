//
// Created by 蔡元涵 on 2020/6/22.
//

#include "CollisionComponent.h"

CollisionComponent::CollisionComponent(class Object *owner) : Component(owner), mRadius(0.0f)
{}

//void CollisionComponent::Update(float deltatime)
//{}

bool IsCollided(const CollisionComponent &self, const CollisionComponent &object)
{
    glm::vec2 diff = object.getCenter() - self.getCenter();
    float disSquare = diff.x * diff.x + diff.y * diff.y;
    float radSquare = (self.getRadius() + object.getRadius());
    radSquare *= radSquare;

    return disSquare <= radSquare;
}
