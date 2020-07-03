//
// Created by 蔡元涵 on 2020/7/3.
//

#ifndef SEMI_DEMO_FONT_H
#define SEMI_DEMO_FONT_H

#include <string>
#include <vector>
#include <unordered_map>
#include <SDL_ttf.h>
#include <glm.hpp>

class Font
{
public:
    Font(class GameSys *gameSys);

    ~Font();

    bool Load(const std::string &fileName);

    void Unload();

    // 使用string、font渲染texture
    class Texture *RenderText(const std::string &text,
                              int pointSize = 16,
                              const glm::vec3 &color = {0.f, 0.f, 0.f});

private:
    // Map of point sizes to font data
    std::unordered_map<int, TTF_Font *> mFontData;

    class GameSys *mGameSys;
};


#endif //SEMI_DEMO_FONT_H
