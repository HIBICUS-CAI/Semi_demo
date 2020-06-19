//
// Created by 蔡元涵 on 2020/6/2.
//

#include "Component.h"
#include "Object.h"

Component::Component(Object *owner, int updateOrder) : mOwner(owner), mUpdateOrder(updateOrder)
{
    //添加至拥有者的组件列表
    mOwner->AddComponent(this);
}

Component::~Component()
{
    mOwner->RemoveComponent(this);
}