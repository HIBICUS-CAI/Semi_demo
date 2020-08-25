//
// Created by 蔡元涵 on 2020/7/22.
//

#include "Item.h"
#include "Player.h"
#include "SpriteComponent.h"
#include "ZoneSwitchObjComponent.h"
#include "CollisionComponent.h"

Item::Item(class GameSys *gameSys, class Player *player, Json::Value itemInfo) : Object(
        gameSys), mPlayer(player), mShinnyDeltaTime(2.f)
{
    mItem.ID = itemInfo["ID"].asInt();

    Json::Value itemConfInfo = Tools::GetJsonRoot("../Configs/ItemConf.json");
    for (int i = 0; i < itemConfInfo["ItemInner"].size(); ++i)
    {
        if (itemConfInfo["ItemInner"][i]["ID"] == mItem.ID)
        {
            mItem.name = itemConfInfo["ItemInner"][i]["Name"].asString();
            mItem.description = itemConfInfo["ItemInner"][i]["Description"].asString();
            break;
        }
    }

    glm::ivec2 initPos = gameSys->getInitPos();
    mPlayerLatePosition = initPos;
    glm::ivec2 mapPos = {itemInfo["MapPos"][0].asInt(), itemInfo["MapPos"][1].asInt()};
    glm::vec2 position = {itemInfo["Position"][0].asFloat(),
                          itemInfo["Position"][1].asFloat()};
    setPosition(Tools::CountPosition(initPos, mapPos, position));

    mShinySC = new SpriteComponent(this, 115);
    mShinySC->SetTexture(gameSys->GetTexture(itemInfo["ShinnyTex"].asString()));
    mShinySC->setIsVisible(false);
    mTexSC = new SpriteComponent(this, 1035);
    mTexSC->SetTexture(gameSys->GetTexture(itemInfo["ItemTex"].asString()));
    mTexSC->setIsVisible(false);

    mNearCC = new CollisionComponent(this);
    mNearCC->setRadius(300.f);
    mItemCC = new CollisionComponent(this);
    mItemCC->setRadius(20.f * 1.414f);

    new ZoneSwitchObjComponent(this, player, this);

    mSTD_backup = mShinnyDeltaTime;
    mSTD_backBackup = mSTD_backup;
    mIsShinny = false;

    gameSys->AddItemToSys(this);
}

void Item::UpdateObject(float deltatime)
{
    if (mShinnyDeltaTime > 0.f)
    {
        mShinnyDeltaTime -= deltatime;
    } else
    {
        mIsShinny = !mIsShinny;
        mShinySC->setIsVisible(mIsShinny);
        mShinnyDeltaTime = mSTD_backup;
    }

    if (IsCollided(*mNearCC, *mPlayer->GetCC()))
    {
        mSTD_backup = 0.4f;
    } else
    {
        mSTD_backup = mSTD_backBackup;
    }
    if (IsCollided(*mItemCC, *mPlayer->GetCC()))
    {
        GetItem();
    }
}

void Item::GetItem()
{
    mPlayer->AddItemToInventory(this);
    setState(Pause);
    mShinySC->setIsVisible(false);
}

void Item::SetIsVisibleInventory(bool isVisible)
{
    mTexSC->setIsVisible(isVisible);
}

ItemInner Item::UseItem()
{
    return mItem;
}
