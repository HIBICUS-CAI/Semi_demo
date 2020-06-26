//
// Created by 蔡元涵 on 2020/6/15.
//

#include "Maps.h"
#include "Player.h"

Maps::Maps(GameSys *gameSys, Player *player) : Object(gameSys), mPlayer(player)
{
    Json::Value Maps = getGameSys()->GetInitObjRoot()["Maps"];
    Json::Value SingleMaps = Maps["SingleMap"];
    for (int i = 0; i < Maps["SingleMap"].size(); ++i)
    {
        std::string texPath = SingleMaps[i]["Tex"].asString();
        new SingleMap(getGameSys(), this, texPath,
                      SingleMaps[i]["Pos"][0].asInt(),
                      SingleMaps[i]["Pos"][1].asInt());
    }

}

void Maps::AddMap(class SingleMap *singleMap)
{
    mMaps.emplace_back(singleMap);
}