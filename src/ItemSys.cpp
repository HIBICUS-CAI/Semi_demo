//
// Created by 蔡元涵 on 2020/8/2.
//

#include "Tools.h"
#include "ItemSys.h"
#include "GameSys.h"
#include "Gear.h"

ItemSys::ItemSys(class GameSys *gameSys)
{
    mGears = gameSys->getGears();
    mItemEventInfo = GetJsonRoot("../Configs/ItemEvenConf.json");
}

void ItemSys::ItemEvent(int itemID)
{
    for (auto gear : mGears)
    {
        if (gear->isTrigged() && !gear->isUnlock())
        {
            mTriggedGears.emplace_back(gear);
        }
    }

    // 比对事件有无
    if (!mTriggedGears.empty())
    {
        SDL_Log("has trigged gear");
        for (auto gear : mTriggedGears)
        {
            SDL_Log("Gear's ID:%d", gear->getID());
            if (IsItemExist(itemID) && IsGearExist(gear->getID()))
            {
                for (int i = 0; i < mItemEventInfo["ItemEvent"].size(); ++i)
                {
                    if (mItemEventInfo["ItemEvent"][i]["ItemID"].asInt() == itemID &&
                        mItemEventInfo["ItemEvent"][i]["GearID"].asInt() == gear->getID())
                    {
                        SDL_Log("Use ID:%d item to unlock ID:%d gear successfully", itemID,
                                gear->getID());
                        gear->GearEvent(gear->getID());
                    } else
                    {
                        SDL_Log("ID:%d item and the ID:%d gear cannot match", itemID,
                                gear->getID());
                    }
                }
            } else
            {
                SDL_Log("item or gear doesn't exist");
            }
        }
    } else
    {
        SDL_Log("no trigged gear");
    }

    mTriggedGears.clear();
}

bool ItemSys::IsItemExist(int itemID)
{
    bool isExist = false;

    for (int i = 0; i < mItemEventInfo["ItemIDVec"].size(); ++i)
    {
        if (mItemEventInfo["ItemIDVec"][i] == itemID)
        {
            isExist = true;
            break;
        }
    }

    return isExist;
}

bool ItemSys::IsGearExist(int gearID)
{
    bool isExist = false;

    for (int i = 0; i < mItemEventInfo["GearIDVec"].size(); ++i)
    {
        if (mItemEventInfo["GearIDVec"][i] == gearID)
        {
            isExist = true;
            break;
        }
    }

    return isExist;
}
