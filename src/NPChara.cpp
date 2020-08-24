//
// Created by 蔡元涵 on 2020/8/24.
//

#include "NPChara.h"
#include "NPCSys.h"
#include "BorderDecider.h"
#include "SpriteComponent.h"
#include "ZoneSwitchObjComponent.h"
#include "CollisionComponent.h"

NPChara::NPChara(class GameSys *gameSys, class NPCSys *npcSys, Json::Value npcInfo) : Object(
        gameSys), mNPCSys(npcSys), mPlayerTrigged(false)
{
    mNPCInfo.ID = npcInfo["ID"].asInt();
    mNPCInfo.Name = npcInfo["Name"].asString();

    glm::ivec2 initPos = gameSys->getInitPos();
    mPlayerLatePosition = initPos;
    glm::ivec2 mapPos = {npcInfo["MapPos"][0].asInt(), npcInfo["MapPos"][1].asInt()};
    glm::vec2 position = {npcInfo["Position"][0].asFloat(), npcInfo["Position"][1].asFloat()};
    setPosition(CountPosition(initPos, mapPos, position));

    mTexSC = new SpriteComponent(this, 115);
    mTexSC->SetTexture(gameSys->GetTexture(npcInfo["Tex"].asString()));

    new ZoneSwitchObjComponent(this, npcSys->getPlayer(), this);

    mCC = new CollisionComponent(this);
    float radius = (npcInfo["Width"].asFloat() > npcInfo["Height"].asFloat()
                    ? npcInfo["Width"].asFloat() : npcInfo["Height"].asFloat());
    mCC->setRadius(radius * 1.414f);

    BorderDecider *bd;
    float x = getPosition().x - npcInfo["Width"].asFloat() / 2.f;
    float y = getPosition().y - npcInfo["Height"].asFloat() / 2.f;
    for (int i = 0; i < npcInfo["Height"].asInt() / 5; ++i)
    {
        bd = new BorderDecider(gameSys, npcSys->getPlayer());
        bd->setPosition({x, y + (static_cast<float>(i)) * 5.f});
        mBorderDeciders.emplace_back(bd);
    }
    y += npcInfo["Height"].asFloat();
    for (int i = 0; i < npcInfo["Width"].asInt() / 5; ++i)
    {
        bd = new BorderDecider(gameSys, npcSys->getPlayer());
        bd->setPosition({x + (static_cast<float>(i)) * 5.f, y});
        mBorderDeciders.emplace_back(bd);
    }
    x += npcInfo["Width"].asFloat();
    for (int i = 0; i < npcInfo["Height"].asInt() / 5; ++i)
    {
        bd = new BorderDecider(gameSys, npcSys->getPlayer());
        bd->setPosition({x, y - (static_cast<float>(i)) * 5.f});
        mBorderDeciders.emplace_back(bd);
    }
    y -= npcInfo["Height"].asFloat();
    for (int i = 0; i < npcInfo["Width"].asInt() / 5; ++i)
    {
        bd = new BorderDecider(gameSys, npcSys->getPlayer());
        bd->setPosition({x - (static_cast<float>(i)) * 5.f, y});
        mBorderDeciders.emplace_back(bd);
    }
    for (auto bd : mBorderDeciders)
    {
        bd->SetCCRadius(npcInfo["BorderCCRadius"].asFloat());
        bd->setState(Pause);
    }
}

void NPChara::UpdateObject(float deltatime)
{
    if (IsCollided(*mCC, *(mNPCSys->getPlayer()->GetCC())))
    {
        mPlayerTrigged = true;
        for (auto bd : mBorderDeciders)
        {
            bd->setState(Active);
        }
    } else
    {
        mPlayerTrigged = false;
        for (auto bd : mBorderDeciders)
        {
            bd->setState(Pause);
        }
    }
}

void NPChara::TalkWithPlayer()
{
    getNPCSys()->getUIO()->TurnOn();
    getNPCSys()->setTalkIndex(0);
    getNPCSys()->setTalkId(0);

    //TODO 此处修改根据状态调整的数值
    getNPCSys()->SetTalk(getNPCSys()->getTalkId());
}
