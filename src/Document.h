//
// Created by 蔡元涵 on 2020/7/22.
//

#ifndef SEMI_DEMO_DOCUMENT_H
#define SEMI_DEMO_DOCUMENT_H

#include "Object.h"

struct DocInner
{
    int ID;
    std::string title;
    std::string mainText;
};

class Document : public Object
{
public:
    Document(class GameSys *gameSys, class Player *player, Json::Value docInfo);

    void UpdateObject(float deltatime) override;

    void GetDoc();

    void SetIsVisibleInventory(bool isVisible);

    DocInner ReadDoc();

    const glm::ivec2 &getPlayerLatePosition() const
    {
        return mPlayerLatePosition;
    }

    void setPlayerLatePosition(const glm::ivec2 &mPlayerLatePosition)
    {
        Document::mPlayerLatePosition = mPlayerLatePosition;
    }

private:
    // 文档唯一ID
    int mID;

    // 文档闪烁时间
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

    class CollisionComponent *mDocCC;

    // player地图位置记录
    glm::ivec2 mPlayerLatePosition;

    DocInner mDoc;
};


#endif //SEMI_DEMO_DOCUMENT_H
