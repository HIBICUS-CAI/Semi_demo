//
// Created by 蔡元涵 on 2020/8/24.
//

#include "NPCSys.h"
#include "Player.h"
#include "NPChara.h"
#include "Tools.h"
#include "Item.h"
#include "Document.h"
#include "UIObject.h"
#include "TextZone.h"

NPCSys::NPCSys(class Player *player, Json::Value npcInitInfo) : mPlayer(player),
                                                                mIsTalking(false),
                                                                mTalkIndex(-1),
                                                                mLatestID(-1),
                                                                mEventID(-1),
                                                                mEventType(-1)
{
    NPChara *npc;
    for (int i = 0; i < npcInitInfo.size(); ++i)
    {
        npc = new NPChara(player->getGameSys(), this, npcInitInfo[i]);
        player->getGameSys()->AddNPCToSys(npc);
    }
    mNPCharas = player->getGameSys()->getNPCharas();

    npcInitInfo.clear();
    npcInitInfo = Tools::GetJsonRoot("../Configs/NPCharaConf.json");
    Json::Value value = npcInitInfo["NPCItems"];
    Item *item;
    Document *document;

    for (int i = 0; i < value.size(); ++i)
    {
        item = new Item(player->getGameSys(), player, value[i]);
        //item->setState(Object::Pause);
        mNPCItems.emplace_back(item);
    }

    value = npcInitInfo["NPCDocs"];
    for (int i = 0; i < value.size(); ++i)
    {
        document = new Document(player->getGameSys(), player, value[i]);
        //document->setState(Object::Pause);
        mNPCDocuments.emplace_back(document);
    }

    value = npcInitInfo["NPCMoveEvent"];
    for (int i = 0; i < value.size(); ++i)
    {
        NPCMoveEvent npcMoveEvent;
        npcMoveEvent.EventID = value[i]["EventID"].asInt();
        npcMoveEvent.NpcID = value[i]["NPC_ID"].asInt();
        for (int j = 0; j < value[i]["MoveInfo"].size(); ++j)
        {
            MoveInfo moveInfo;
            moveInfo.Direction = value[i]["MoveInfo"][j]["Direction"].asInt();
            moveInfo.Distance = value[i]["MoveInfo"][j]["Distance"].asFloat();
            npcMoveEvent.NpcMoveInfo.emplace_back(moveInfo);
        }
        mNPCMoveEvents.emplace_back(npcMoveEvent);
    }

    value.clear();
    value = player->getGameSys()->GetInitObjRoot()["UIObjects"]["DialogUI"];
    mUIO = new UIObject(player->getGameSys(), value["UITexPath"].asString());
    for (int i = 0; i < value["Button"].size(); ++i)
    {
        mUIO->CreateButton(player->getGameSys(), mUIO,
                           value["Button"][i]["TexPath"].asString(),
                           value["Button"][i]["Type"].asInt(),
                           value["Button"][i]["Text"].asString(),
                           {value["Button"][i]["Position"][0].asFloat(),
                            value["Button"][i]["Position"][1].asFloat()},
                           value["Button"][i]["Function"].asInt());
    }
    for (int i = 0; i < value["TextZone"].size(); ++i)
    {
        mUIO->CreateTextZone(player->getGameSys(), mUIO,
                             {value["TextZone"][i]["Position"][0].asFloat(),
                              value["TextZone"][i]["Position"][1].asFloat()},
                             value["TextZone"][i]["Width"].asInt(),
                             value["TextZone"][i]["ID"].asInt());
    }
    mUIO->TurnOff();

    mTalkInfo = Tools::GetJsonRoot("../Configs/TalkTextConf.json");

    ClearPlayerInfo();
}

NPChara *NPCSys::FindChara(int id)
{
    for (int i = 0; i < mNPCharas.size(); ++i)
    {
        if (mNPCharas[i]->getNPCInfo().ID == id)
        {
            return mNPCharas[i];
        }
    }
    NPChara *npChara = nullptr;
    return npChara;
}

void NPCSys::SetTalk(int id)
{

    if (id != mLatestID)
    {
        for (int i = 0; i < mTalkInfo["TalkTexts"].size(); ++i)
        {
            if (mTalkInfo["TalkTexts"][i]["ID"].asInt() == id)
            {
                mTalkText = mTalkInfo["TalkTexts"][i]["TalkText"];
                mLatestID = id;
            }
        }
    }

    if (mTalkIndex == mTalkText.size())
    {
        // 进行道具(0)或文档(1)发放或移动(2)
        std::vector<int> idList;
        switch (mEventType)
        {
            case 0:
            {
                idList.clear();
                for (auto item : mNPCItems)
                {
                    idList.emplace_back(item->UseItem().ID);
                }
                if (Tools::CheckMemberExistInt(mEventID, idList))
                {
                    //TODO 这里是有问题的，直接使用GetItem会导致贴图无法显示，此处牺牲性能绕远路实现
                    //GetItemInSys(mEventID)->GetItem();
                    GetItemInSys(mEventID)->setPosition(mPlayer->getPosition());
                }

                break;
            }
            case 1:
            {
                idList.clear();
                for (auto doc : mNPCDocuments)
                {
                    idList.emplace_back(doc->ReadDoc().ID);
                }
                if (Tools::CheckMemberExistInt(mEventID, idList))
                {
                    //GetDocInSys(mEventID)->GetDoc();
                    GetDocInSys(mEventID)->setPosition(mPlayer->getPosition());
                }

                break;
            }
            case 2:
            {
                idList.clear();
                NPCMoveEvent npcMoveEvent;
                for (auto event : mNPCMoveEvents)
                {
                    idList.emplace_back(event.EventID);
                    if (event.EventID == mEventID)
                    {
                        npcMoveEvent = event;
                    }
                }
                if (Tools::CheckMemberExistInt(mEventID, idList))
                {
                    NPChara *npChara = FindChara(npcMoveEvent.NpcID);
                    for (int i = 0; i < npcMoveEvent.NpcMoveInfo.size(); ++i)
                    {
                        npChara->AddMoveInfo(npcMoveEvent.NpcMoveInfo[i]);
                    }
                    mPlayer->setCanMove(false);
                    npChara->setRdyToMove(true);
                    npChara->setRdyForNextMove(true);
                }

                break;
            }
            default:
                break;
        }

        // 初始化所有相关参数
        InitTalkStatus();
    } else
    {
        TextZone *textZone;
        textZone = mUIO->FindText(
                mPlayer->getGameSys()->GetInitObjRoot()["UIObjects"]["DialogUI"]["TextZone"][0]["ID"].asInt());
        if (textZone != nullptr)
        {
            // 设置人名
            if (mTalkText[mTalkIndex]["SpeakerID"].asInt() == -1)
            {
                mUIO->DeltaMove(mPlayer->getPosition() - mUIO->getPosition());
                textZone->setText("Player");
            } else
            {
                mUIO->DeltaMove(
                        FindChara(mTalkText[mTalkIndex]["SpeakerID"].asInt())->getPosition() -
                        mUIO->getPosition());
                textZone->setText(FindChara(
                        mTalkText[mTalkIndex]["SpeakerID"].asInt())->getNPCInfo().Name);
            }
        }
        textZone = mUIO->FindText(
                mPlayer->getGameSys()->GetInitObjRoot()["UIObjects"]["DialogUI"]["TextZone"][1]["ID"].asInt());
        if (textZone != nullptr)
        {
            // 设置对话
            textZone->setText(mTalkText[mTalkIndex]["Text"].asString());
        }
        mTalkIndex++;
    }
}

void NPCSys::InitTalkStatus()
{
    mUIO->TurnOff();
    mTalkIndex = -1;
    mIsTalking = false;
    mEventType = -1;
    mEventID = -1;
}

void NPCSys::ClearPlayerInfo()
{
    mPlayerInfo.GotDocs.clear();
    mPlayerInfo.GotItems.clear();
    mPlayerInfo.TalkedNPCs.clear();
    mPlayerInfo.UnlockedGears.clear();
}

void NPCSys::UpdatePlayerInfo()
{
    ClearPlayerInfo();

    mPlayerInfo.GotDocs = mPlayer->getGotDocuments();
    mPlayerInfo.GotItems = mPlayer->getGotItems();
    mPlayerInfo.TalkedNPCs = mPlayer->getTalkedNpCs();
    mPlayerInfo.UnlockedGears = mPlayer->getUnlockedGears();
}

Item *NPCSys::GetItemInSys(int itemID)
{
    int index = 0;
    for (auto item : mNPCItems)
    {
        if (item->UseItem().ID == itemID)
        {
            mNPCItems.erase(mNPCItems.begin() + index);
            return item;
        }
        index++;
    }

    return nullptr;
}

Document *NPCSys::GetDocInSys(int docID)
{
    int index = 0;
    for (auto doc : mNPCDocuments)
    {
        if (doc->ReadDoc().ID == docID)
        {
            mNPCDocuments.erase(mNPCDocuments.begin() + index);
            return doc;
        }
        index++;
    }

    return nullptr;
}
