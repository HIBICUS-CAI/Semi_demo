//
// Created by 蔡元涵 on 2020/8/24.
//

#ifndef SEMI_DEMO_NPCSYS_H
#define SEMI_DEMO_NPCSYS_H

#include <json.h>
#include "Player.h"
#include "UIObject.h"

struct PlayerInfo
{
    std::vector<int> GotItems;
    std::vector<int> GotDocs;
    std::vector<int> UnlockedGears;
    std::vector<int> TalkedNPCs;
};

class NPCSys
{
public:
    NPCSys(class Player *player, Json::Value npcInitInfo);

    NPChara FindChara(int id);

    void SetTalk(int id);

    void InitTalkStatus();

    void ClearPlayerInfo();

    void UpdatePlayerInfo();

    Player *getPlayer() const
    {
        return mPlayer;
    }

    const std::vector<class NPChara *> &getNPCharas() const
    {
        return mNPCharas;
    }

    bool isTalking() const
    {
        return mIsTalking;
    }

    void setIsTalking(bool mIsTalking)
    {
        NPCSys::mIsTalking = mIsTalking;
    }

    int getTalkIndex() const
    {
        return mTalkIndex;
    }

    void setTalkIndex(int mTalkIndex)
    {
        NPCSys::mTalkIndex = mTalkIndex;
    }

    int getTalkId() const
    {
        return mTalkID;
    }

    void setTalkId(int mTalkId)
    {
        mTalkID = mTalkId;
    }

    UIObject *getUIO() const
    {
        return mUIO;
    }

private:
    class Player *mPlayer;

    class UIObject *mUIO;

    bool mIsTalking;
    int mTalkIndex;
    int mTalkID;
    int mLatestID;
    Json::Value mTalkInfo;
    Json::Value mTalkText;

    std::vector<class NPChara *> mNPCharas;
    std::vector<class Item *> mNPCItems;
    std::vector<class Document *> mNPCDocuments;

    PlayerInfo mPlayerInfo;
};


#endif //SEMI_DEMO_NPCSYS_H
