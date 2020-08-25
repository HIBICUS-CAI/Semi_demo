//
// Created by 蔡元涵 on 2020/6/26.
//

#ifndef SEMI_DEMO_TOOLS_H
#define SEMI_DEMO_TOOLS_H

#include <json.h>
#include <glm.hpp>
#include <vector>

namespace Tools
{
    Json::Value GetJsonRoot(std::string fileName);

    glm::vec2 CountPosition(glm::ivec2 initPos, glm::ivec2 mapPos, glm::vec2 position);

    int GetClickItemIndex(glm::vec2 clickPos);

    int GetClickDocIndex(glm::vec2 clickPos);

    bool CheckMemberExistInt(int value, std::vector<int> vector);
}


#endif //SEMI_DEMO_TOOLS_H
