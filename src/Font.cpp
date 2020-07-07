//
// Created by 蔡元涵 on 2020/7/3.
//

#include "Font.h"
#include "GameSys.h"
#include "Texture.h"

Font::Font(class GameSys *gameSys) : mGameSys(gameSys)
{}

Font::~Font()
{}

bool Font::Load(const std::string &fileName)
{
    std::vector<int> fontSizes = {
            8, 9, 10, 11, 12, 14, 16, 18,
            20, 22, 24, 26, 28, 30, 32,
            34, 36, 38, 40, 42, 44, 46,
            48, 52, 56, 60, 64, 68, 72
    };

    for (auto &size : fontSizes)
    {
        TTF_Font *font = TTF_OpenFont(fileName.c_str(), size);
        if (font == nullptr)
        {
            SDL_Log("Failed to load font %s in size %d", fileName.c_str(), size);
            return false;
        }
        mFontData.emplace(size, font);
    }

    return true;
}

void Font::Unload()
{
    for (auto &font : mFontData)
    {
        TTF_CloseFont(font.second);
    }
}

class Texture *
Font::RenderText(const std::string &text, int pointSize, int textWidth, const glm::vec3 &color)
{
    Texture *texture = nullptr;
    SDL_Color sdlColor;
    sdlColor.r = static_cast<Uint8>(color.x * 255);
    sdlColor.g = static_cast<Uint8>(color.y * 255);
    sdlColor.b = static_cast<Uint8>(color.z * 255);
    sdlColor.a = 255;

    auto iter = mFontData.find(pointSize);
    if (iter != mFontData.end())
    {
        TTF_Font *font = iter->second;
//        SDL_Surface *surface = TTF_RenderUTF8_Blended(font, text.c_str(), sdlColor);
        SDL_Surface *surface = TTF_RenderUTF8_Blended_Wrapped(font, text.c_str(), sdlColor,
                                                              textWidth);
        if (surface != nullptr)
        {
            texture = new Texture();
            texture->CreateFromSurface(surface);
        }
    } else
    {
        SDL_Log("Point size %d is unsupported", pointSize);
    }

    return texture;
}
