//
// Created by 蔡元涵 on 2020/6/3.
//

#ifndef SEMI_DEMO_PLAYER_H
#define SEMI_DEMO_PLAYER_H

#include <glm.hpp>
#include "Object.h"
#include "Inventory.h"

const glm::ivec2 PLAYERINITPOS = glm::ivec2{1, 0};

class Player : public Object
{
public:
    Player(class GameSys *gameSys);

    bool IsPlayer() override
    {
        return true;
    }

    class CollisionComponent *GetCC()
    {
        return mCC;
    }

    int getInputStatus() const
    {
        return mInputStatus;
    }

    void setInputStatus(int mInputStatus)
    {
        Player::mInputStatus = mInputStatus;
    }

    void RevertMove();

    void AddItemToInventory(class Item *item);

    void AddDocToInventory(class Document *document);

    Inventory *getInventory() const
    {
        return mInventory;
    }

    void AddItemToRecord(int itemID);

    void AddDocToRecord(int docID);

    void AddGearToRecord(int gearID);

    void AddNPCToRecord(int npcID);

    const std::vector<int> &getGotItems() const
    {
        return mGotItems;
    }

    const std::vector<int> &getGotDocuments() const
    {
        return mGotDocuments;
    }

    const std::vector<int> &getUnlockedGears() const
    {
        return mUnlockedGears;
    }

    const std::vector<int> &getTalkedNpCs() const
    {
        return mTalkedNPCs;
    }

    bool isCanMove() const
    {
        return mCanMove;
    }

    void setCanMove(bool mCanMove)
    {
        Player::mCanMove = mCanMove;
    }

private:
    class Inventory *mInventory;

    class CollisionComponent *mCC;

    //↑1 →2 ↓3 ←4 ↗5 ↘6 ↙7 ↖8
    int mInputStatus;
    bool mCanMove;

    // 已经得到的道具文档、解锁过的机关、对话过的NPC
    std::vector<int> mGotItems;
    std::vector<int> mGotDocuments;
    std::vector<int> mUnlockedGears;
    std::vector<int> mTalkedNPCs;
};


#endif //SEMI_DEMO_PLAYER_H
