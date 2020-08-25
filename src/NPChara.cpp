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

    npcInfo.clear();
    npcInfo = GetJsonRoot("../Configs/NPCharaConf.json")["NPCConfig"];
    for (int i = 0; i < npcInfo.size(); ++i)
    {
        if (npcInfo[i]["NPC_ID"].asInt() == mNPCInfo.ID)
        {
            npcInfo = npcInfo[i]["Status"];
            break;
        }
    }

    NPCStatus status;
    for (int i = 0; i < npcInfo.size(); ++i)
    {
        status.Priority = npcInfo[i]["Priority"].asInt();
        if (!npcInfo[i]["Depends"]["Items"].empty())
        {
            status.GotItems.clear();
            for (int j = 0; j < npcInfo[i]["Depends"]["Items"].size(); ++j)
            {
                status.GotItems.emplace_back(npcInfo[i]["Depends"]["Items"][j].asInt());
            }
        }
        if (!npcInfo[i]["Depends"]["Docs"].empty())
        {
            status.GotDocs.clear();
            for (int j = 0; j < npcInfo[i]["Depends"]["Docs"].size(); ++j)
            {
                status.GotDocs.emplace_back(npcInfo[i]["Depends"]["Docs"][j].asInt());
            }
        }
        if (!npcInfo[i]["Depends"]["Gears"].empty())
        {
            status.UnlockdedGears.clear();
            for (int j = 0; j < npcInfo[i]["Depends"]["Gears"].size(); ++j)
            {
                status.UnlockdedGears.emplace_back(npcInfo[i]["Depends"]["Gears"][j].asInt());
            }
        }
        if (!npcInfo[i]["Depends"]["NPCs"].empty())
        {
            status.TalkedNPCs.clear();
            for (int j = 0; j < npcInfo[i]["Depends"]["NPCs"].size(); ++j)
            {
                status.TalkedNPCs.emplace_back(npcInfo[i]["Depends"]["NPCs"][j].asInt());
            }
        }
        status.TalkTextID = npcInfo[i]["TalkTextID"].asInt();
        status.EventType = npcInfo[i]["EventType"].asInt();
        status.EventID = npcInfo[i]["EventID"].asInt();

        mNPCStatus.emplace_back(status);
    }
    // 按照优先级的从高到低进行排序
    std::sort(mNPCStatus.begin(), mNPCStatus.end(), GreaterSort);
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
    mNPCSys->UpdatePlayerInfo();

    mNPCSys->getUIO()->TurnOn();
    mNPCSys->setTalkIndex(0);
    mNPCSys->setTalkId(GetTalkIDByStatus());

    //TODO 此处增加派发道具或者文档的方法
    mNPCSys->SetTalk(mNPCSys->getTalkId());
}

int NPChara::GetTalkIDByStatus()
{
    bool itemCompleted = false;
    bool docCompleted = false;
    bool gearCompleted = false;
    bool npcCompleted = false;

    for (int i = 0; i < mNPCStatus.size(); ++i)
    {
        if (!mNPCStatus[i].GotItems.empty())
        {
            for (int j = 0; j < mNPCStatus[i].GotItems.size(); ++j)
            {
                if (!CheckMemberExistInt(mNPCStatus[i].GotItems[j],
                                         mNPCSys->getPlayerInfo().GotItems))
                {
                    itemCompleted = false;
                    break;
                } else
                {
                    itemCompleted = true;
                }
            }
        } else
        {
            itemCompleted = true;
        }

        if (!mNPCStatus[i].GotDocs.empty())
        {
            for (int j = 0; j < mNPCStatus[i].GotDocs.size(); ++j)
            {
                if (!CheckMemberExistInt(mNPCStatus[i].GotDocs[j],
                                         mNPCSys->getPlayerInfo().GotDocs))
                {
                    docCompleted = false;
                    break;
                } else
                {
                    docCompleted = true;
                }
            }
        } else
        {
            docCompleted = true;
        }

        if (!mNPCStatus[i].UnlockdedGears.empty())
        {
            for (int j = 0; j < mNPCStatus[i].UnlockdedGears.size(); ++j)
            {
                if (!CheckMemberExistInt(mNPCStatus[i].UnlockdedGears[j],
                                         mNPCSys->getPlayerInfo().UnlockedGears))
                {
                    gearCompleted = false;
                    break;
                } else
                {
                    gearCompleted = true;
                }
            }
        } else
        {
            gearCompleted = true;
        }

        if (!mNPCStatus[i].TalkedNPCs.empty())
        {
            for (int j = 0; j < mNPCStatus[i].TalkedNPCs.size(); ++j)
            {
                if (!CheckMemberExistInt(mNPCStatus[i].TalkedNPCs[j],
                                         mNPCSys->getPlayerInfo().TalkedNPCs))
                {
                    npcCompleted = false;
                    break;
                } else
                {
                    npcCompleted = true;
                }
            }
        } else
        {
            npcCompleted = true;
        }

        if (itemCompleted && docCompleted && gearCompleted && npcCompleted)
        {
            return mNPCStatus[i].TalkTextID;
        }
    }

    if (!itemCompleted || !docCompleted || !gearCompleted || !npcCompleted)
    {
        SDL_Log("cannot match text");
        return -1;
    } else
    {
        return -1;
    }
}
