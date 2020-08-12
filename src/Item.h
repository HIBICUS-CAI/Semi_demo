//
// Created by 蔡元涵 on 2020/7/22.
//

#ifndef SEMI_DEMO_ITEM_H
#define SEMI_DEMO_ITEM_H

#include "Object.h"

struct ItemInner
{
    int ID;
    std::string name;
    std::string description;
};

class Item : public Object
{
public:
    Item(class GameSys *gameSys, class Player *player, Json::Value itemInfo);

    void UpdateObject(float deltatime) override;

    void GetItem();

    void SetIsVisibleInventory(bool isVisible);

    ItemInner UseItem();

    const glm::ivec2 &getPlayerLatePosition() const
    {
        return mPlayerLatePosition;
    }

    void setPlayerLatePosition(const glm::ivec2 &mPlayerLatePosition)
    {
        Item::mPlayerLatePosition = mPlayerLatePosition;
    }

private:
    // 道具容器
    ItemInner mItem;

    // 道具闪烁时间
    float mShinnyDeltaTime;
    float mSTD_backup;
    float mSTD_backBackup;
    bool mIsShinny;

    // player
    class Player *mPlayer;

    // 闪光贴图&道具贴图
    class SpriteComponent *mShinySC;

    class SpriteComponent *mTexSC;

    // 碰撞检测组件,检测玩家是否靠近&碰撞拾取
    class CollisionComponent *mNearCC;

    class CollisionComponent *mItemCC;

    // player地图位置记录
    glm::ivec2 mPlayerLatePosition;
};


#endif //SEMI_DEMO_ITEM_H
