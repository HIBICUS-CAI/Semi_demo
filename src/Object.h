//
// Created by 蔡元涵 on 2020/6/2.
//

#ifndef SEMI_DEMO_OBJECT_H
#define SEMI_DEMO_OBJECT_H

#include <vector>
#include <cstdint>
#include <glm.hpp>
#include "Component.h"
#include "GameSys.h"

class Object
{
public:
    enum State
    {
        Active,     //显示中
        Pause,      //暂停、非显示中
        Dead        //死亡、销毁
    };

    Object(class GameSys *gameSys);

    virtual ~Object();

    void Update(float deltatime);

    void UpdateComponent(float deltatime);

    //可重写
    virtual void UpdateObject(float deltatime);

    void ProcessInput(const uint8_t *keyState);

    //可重写
    virtual void ObjectInput(const uint8_t *keyState);

    virtual bool IsPlayer()
    {
        return false;
    }

    void ComputeWorldTransform();

    State getState() const
    {
        return mState;
    }

    void setState(State mState)
    {
        Object::mState = mState;
    }

    const glm::vec2 &getPosition() const
    {
        return mPosition;
    }

    void setPosition(const glm::vec2 &mPostion)
    {
        Object::mPosition = mPostion;
        mRecomputeWorldTransform = true;
    }

    float getScale() const
    {
        return mScale;
    }

    void setScale(float mScale)
    {
        Object::mScale = mScale;
        mRecomputeWorldTransform = true;
    }

    const glm::ivec2 &getMapPositon() const
    {
        return mMapPositon;
    }

    void setMapPositon(const int row, const int col)
    {
        Object::mMapPositon = {row, col};
    }

    const glm::mat4 &getWorldTransform() const
    {
        return mWorldTransform;
    }

    GameSys *getGameSys() const
    {
        return mGameSys;
    }

    //添加、删除组件
    void AddComponent(class Component *component);

    void RemoveComponent(class Component *component);

private:
    State mState;

    //transform相关
    glm::vec2 mPosition;

    //地图标记 (1,0)代表第一行第二列
    glm::ivec2 mMapPositon;

    glm::mat4 mWorldTransform;
    float mScale;
    bool mRecomputeWorldTransform;

    std::vector<class Component *> mComponents;

    class GameSys *mGameSys;
};


#endif //SEMI_DEMO_OBJECT_H
