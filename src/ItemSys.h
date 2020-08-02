//
// Created by 蔡元涵 on 2020/8/2.
//

#ifndef SEMI_DEMO_ITEMSYS_H
#define SEMI_DEMO_ITEMSYS_H

#include <vector>
#include <json.h>

class ItemSys
{
public:
    ItemSys(class GameSys *gameSys);

    void ItemEvent(int itemID);

    bool IsItemExist(int itemID);

    bool IsGearExist(int gearID);

private:
    std::vector<class Gear *> mGears;
    std::vector<class Gear *> mTriggedGears;
    //ItemEvent.json对象
    Json::Value mItemEventInfo;
};


#endif //SEMI_DEMO_ITEMSYS_H
