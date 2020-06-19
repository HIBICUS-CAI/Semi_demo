//
// Created by 蔡元涵 on 2020/6/2.
//

#include "Object.h"
#include "GameSys.h"
#include "Component.h"
#include <algorithm>
#include <ext/matrix_transform.inl>

Object::Object(GameSys *gameSys) : mState(Active), mPosition(0, 0), mScale(1.0f),
                                   mGameSys(gameSys), mRecomputeWorldTransform(true)
{
    mGameSys->AddObject(this);
}

Object::~Object()
{
    mGameSys->RemoveObject(this);
}

void Object::Update(float deltatime)
{
    if (mState == Active || mState == Pause)
    {
        ComputeWorldTransform();

        UpdateComponent(deltatime);
        UpdateObject(deltatime);

        ComputeWorldTransform();
    }
}

void Object::UpdateComponent(float deltatime)
{
    for (auto comp:mComponents)
    {
        comp->Update(deltatime);
    }
}

void Object::UpdateObject(float deltatime)
{}

void Object::ProcessInput(const uint8_t *keyState)
{
    if (mState == Active)
    {
        for (auto comp:mComponents)
        {
            comp->ProcessInput(keyState);
        }
        ObjectInput(keyState);
    }
}

void Object::ObjectInput(const uint8_t *keyState)
{}

void Object::ComputeWorldTransform()
{
    if (mRecomputeWorldTransform)
    {
        mWorldTransform = glm::mat4(1.0f);
        mWorldTransform = glm::scale(mWorldTransform, glm::vec3(mScale, mScale, 1.0));
        mWorldTransform = glm::translate(mWorldTransform,
                                         glm::vec3(mPosition.x, mPosition.y, 0.0f));

        for (auto comp:mComponents)
        {
            comp->OnUpdateWorldTransform();
        }
    }
}

void Object::AddComponent(class Component *component)
{
    //按顺序插入
    int myOrder = component->getUpdateOrder();
    auto iter = mComponents.begin();
    for (; iter != mComponents.end(); iter++)
    {
        if (myOrder < (*iter)->getUpdateOrder())
        {
            break;
        }
    }

    mComponents.insert(iter, component);
}

void Object::RemoveComponent(class Component *component)
{
    auto iter = std::find(mComponents.begin(), mComponents.end(), component);
    if (iter != mComponents.end())
    {
        mComponents.erase(iter);
    }
}
