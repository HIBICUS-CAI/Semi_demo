//
// Created by 蔡元涵 on 2020/8/24.
//

#ifndef SEMI_DEMO_NPCSYS_H
#define SEMI_DEMO_NPCSYS_H

#include <json.h>
#include "Player.h"
#include "UIObject.h"

class NPCSys
{
public:
    NPCSys(class Player *player, Json::Value npcInitInfo);

    NPChara FindChara(int id);

    void SetTalk(int id);

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
    Json::Value mTalkInfo;

    std::vector<class NPChara *> mNPCharas;
    std::vector<class Item *> mNPCItems;
    std::vector<class Document *> mNPCDocuments;
};


#endif //SEMI_DEMO_NPCSYS_H
