//
// Created by 蔡元涵 on 2020/6/2.
//

#ifndef SEMI_DEMO_COMPONENT_H
#define SEMI_DEMO_COMPONENT_H

#include <cstdint>

class Component
{
public:
    //updateOrder越小越早更新
    Component(class Object *owner, int updateOrder = 100);

    virtual ~Component();

    virtual void Update(float deltatime)
    {}

    virtual void ProcessInput(const uint8_t *keyState)
    {}

    //特殊场景下的调用方法
    virtual void OnUpdateWorldTransform()
    {}

    int getUpdateOrder() const
    {
        return mUpdateOrder;
    }

protected:
    class Object *mOwner;

    int mUpdateOrder;
};


#endif //SEMI_DEMO_COMPONENT_H
