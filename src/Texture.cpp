//
// Created by 蔡元涵 on 2020/6/3.
//

#include <SDL.h>
#include <glew.h>
#include "stb_image.h"
#include "Texture.h"

Texture::Texture() : mTextureID(0), mHeight(0), mWidth(0)
{

}

Texture::~Texture()
{

}

bool Texture::Load(const std::string &fileName)
{
    int channels = 0;
    unsigned char *image = stbi_load(fileName.c_str(), &mWidth, &mHeight, &channels, 0);

    if (image == nullptr)
    {
        SDL_Log("STB failed to load image %s", fileName.c_str());

        return false;
    }

    int format = GL_RGB;
    if (channels == 4)
    {
        format = GL_RGBA;
    }

    glGenTextures(1, &mTextureID);
    glBindTexture(GL_TEXTURE_2D, mTextureID);
    glTexImage2D(GL_TEXTURE_2D, 0, format, mWidth, mHeight, 0, format, GL_UNSIGNED_BYTE,
                 image);

    stbi_image_free(image);

    //开启双线性滤波
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    return true;
}

void Texture::Unload()
{
    glDeleteTextures(1, &mTextureID);
}

void Texture::SetActive()
{
    glBindTexture(GL_TEXTURE_2D, mTextureID);
}

void Texture::CreateFromSurface(struct SDL_Surface *surface)
{
    mWidth = surface->w;
    mHeight = surface->h;

    glGenTextures(1, &mTextureID);
    glBindTexture(GL_TEXTURE_2D, mTextureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mWidth, mHeight, 0, GL_BGRA, GL_UNSIGNED_BYTE,
                 surface->pixels);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}
