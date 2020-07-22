//
// Created by 蔡元涵 on 2020/6/26.
//

#include <fstream>
#include "Tools.h"

Json::Value GetJsonRoot(std::string fileName)
{
    std::ifstream ifs(fileName);
    bool result;
    Json::String errors;
    Json::Value root, error;
    Json::CharReaderBuilder readerBuilder;
    std::unique_ptr<Json::CharReader> const jsonReader(readerBuilder.newCharReader());
    result = Json::parseFromStream(readerBuilder, ifs, &root, &errors);

    if (result && errors.empty())
    {
        return root;
    } else
    {
        return error;
    }
}

glm::vec2 CountPosition(glm::ivec2 initPos, glm::ivec2 mapPos, glm::vec2 position)
{
    float posX = static_cast<float>(mapPos.x - initPos.x);
    float posY = static_cast<float>(mapPos.y - initPos.y);

    posX = posX * 1024.f + position.x;
    posY = posY * 768.f + position.y;

    return {posX, posY};
}
