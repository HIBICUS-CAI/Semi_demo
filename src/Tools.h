//
// Created by 蔡元涵 on 2020/6/26.
//

#ifndef SEMI_DEMO_TOOLS_H
#define SEMI_DEMO_TOOLS_H

#include <json.h>
#include <glm.hpp>

Json::Value GetJsonRoot(std::string fileName);

glm::vec2 CountPosition(glm::ivec2 initPos, glm::ivec2 mapPos, glm::vec2 position);

int GetClickItemIndex(glm::vec2 clickPos);

int GetClickDocIndex(glm::vec2 clickPos);


#endif //SEMI_DEMO_TOOLS_H
