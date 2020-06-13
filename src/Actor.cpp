//
// Created by 蔡元涵 on 2020/6/2.
//

#include "Actor.h"
#include "GameSys.h"
#include "Component.h"
#include <algorithm>
#include <ext/matrix_transform.inl>

Actor::Actor(GameSys *gameSys) : mState(Active), mPosition(0, 0), mScale(1.0f),
                                 mGameSys(gameSys), mRecomputeWorldTransform(true)
{
    mGameSys->AddActor(this);
}

Actor::~Actor()
{
    mGameSys->RemoveActor(this);
}

void Actor::Update(float deltatime)
{
    if (mState == Active || mState == Pause)
    {
        ComputeWorldTransform();

        UpdateComponent(deltatime);
        UpdateActor(deltatime);

        ComputeWorldTransform();
    }
}

void Actor::UpdateComponent(float deltatime)
{
    for (auto comp:mComponents)
    {
        comp->Update(deltatime);
    }
}

void Actor::UpdateActor(float deltatime)
{}

void Actor::ProcessInput(const uint8_t *keyState)
{
    if (mState == Active)
    {
        for (auto comp:mComponents)
        {
            comp->ProcessInput(keyState);
        }
        ActorInput(keyState);
    }
}

void Actor::ActorInput(const uint8_t *keyState)
{}

void Actor::ComputeWorldTransform()
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

void Actor::AddComponent(class Component *component)
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

void Actor::RemoveComponent(class Component *component)
{
    auto iter = std::find(mComponents.begin(), mComponents.end(), component);
    if (iter != mComponents.end())
    {
        mComponents.erase(iter);
    }
}
