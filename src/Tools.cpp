//
// Created by 蔡元涵 on 2020/6/26.
//

#include <fstream>
#include "Tools.h"

Json::Value Tools::GetJsonRoot(std::string fileName)
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

glm::vec2 Tools::CountPosition(glm::ivec2 initPos, glm::ivec2 mapPos, glm::vec2 position)
{
    float posX = static_cast<float>(mapPos.x - initPos.x);
    float posY = static_cast<float>(mapPos.y - initPos.y);

    posX = posX * 1024.f + position.x;
    posY = posY * 768.f + position.y;

    return {posX, posY};
}

int Tools::GetClickItemIndex(glm::vec2 clickPos)
{
    int click_x = static_cast<int>(clickPos.x);
    int click_y = static_cast<int>(clickPos.y);

    // 需要根据按键的大小进行调整
    click_x = ((click_x + 400) / 100 * 100) - 360;
    click_y = ((click_y + 190) / 100 * 100) - 150;

    click_x = click_x / 100 + 3;
    click_y = ((click_y / (-50)) + 3) / 2;

    return click_x + (4 * click_y);
}

int Tools::GetClickDocIndex(glm::vec2 clickPos)
{
    int click_x = static_cast<int>(clickPos.x);
    int click_y = static_cast<int>(clickPos.y);

    // 需要根据按键的大小进行调整
    click_x = 60 + (((click_x + 80) / 100 - 1) * 100);
    click_y = 50 + (((click_y + 90) / 100 - 1) * 100);

    click_x = click_x / 100;
    click_y = ((click_y / (-50)) + 3) / 2;

    return click_x + (4 * click_y);
}

bool Tools::CheckMemberExistInt(int value, std::vector<int> vector)
{
    if (vector.empty())
    {
        return false;
    } else
    {
        for (int i = 0; i < vector.size(); ++i)
        {
            if (vector[i] == value)
            {
                return true;
            }
        }
        return false;
    }
}
