//
// Created by 蔡元涵 on 2020/6/3.
//

#ifndef SEMI_DEMO_TEXTURE_H
#define SEMI_DEMO_TEXTURE_H

#include <string>

class Texture
{
public:
    Texture();

    ~Texture();

    bool Load(const std::string &fileName);

    void Unload();

    void CreateFromSurface(struct SDL_Surface *surface);

    void SetActive();

    int getHeight() const
    {
        return mHeight;
    }

    int getWidth() const
    {
        return mWidth;
    }

private:
    //纹理的OpenGL ID
    unsigned int mTextureID;
    //长宽
    int mHeight;
    int mWidth;
};


#endif //SEMI_DEMO_TEXTURE_H
