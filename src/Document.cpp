//
// Created by 蔡元涵 on 2020/7/22.
//

#include "Document.h"
#include "Player.h"
#include "SpriteComponent.h"
#include "ZoneSwitchObjComponent.h"
#include "CollisionComponent.h"

Document::Document(class GameSys *gameSys, class Player *player, Json::Value docInfo) : Object(
        gameSys), mPlayer(player), mShinnyDeltaTime(2.f)
{
    mDoc.ID = docInfo["ID"].asInt();

    Json::Value docConfInfo = Tools::GetJsonRoot("../Configs/DocumentConf.json");
    for (int i = 0; i < docConfInfo["DocInner"].size(); ++i)
    {
        if (docConfInfo["DocInner"][i]["ID"] == mDoc.ID)
        {
            mDoc.title = docConfInfo["DocInner"][i]["Title"].asString();
            mDoc.mainText = docConfInfo["DocInner"][i]["Text"].asString();
            break;
        }
    }

    glm::ivec2 initPos = gameSys->getInitPos();
    mPlayerLatePosition = initPos;
    glm::ivec2 mapPos = {docInfo["MapPos"][0].asInt(), docInfo["MapPos"][1].asInt()};
    glm::vec2 position = {docInfo["Position"][0].asFloat(),
                          docInfo["Position"][1].asFloat()};
    setPosition(Tools::CountPosition(initPos, mapPos, position));

    mShinySC = new SpriteComponent(this, 115);
    mShinySC->SetTexture(gameSys->GetTexture(docInfo["ShinnyTex"].asString()));
    mShinySC->setIsVisible(false);
    mTexSC = new SpriteComponent(this, 1035);
    mTexSC->SetTexture(gameSys->GetTexture(docInfo["DocTex"].asString()));
    mTexSC->setIsVisible(false);

    mNearCC = new CollisionComponent(this);
    mNearCC->setRadius(300.f);
    mDocCC = new CollisionComponent(this);
    mDocCC->setRadius(20.f * 1.414f);

    new ZoneSwitchObjComponent(this, player, this);

    mSTD_backup = mShinnyDeltaTime;
    mSTD_backBackup = mSTD_backup;
    mIsShinny = false;

    gameSys->AddDocToSys(this);
}

void Document::UpdateObject(float deltatime)
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
    if (IsCollided(*mDocCC, *mPlayer->GetCC()))
    {
        GetDoc();
    }
}

void Document::GetDoc()
{
    mPlayer->AddDocToInventory(this);
    setState(Pause);
    mShinySC->setIsVisible(false);
}

void Document::SetIsVisibleInventory(bool isVisible)
{
    mTexSC->setIsVisible(isVisible);
}

DocInner Document::ReadDoc()
{
    return mDoc;
}
