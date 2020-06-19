//
// Created by 蔡元涵 on 2020/6/3.
//

#include <glm.hpp>
#include <ext/matrix_transform.inl>
#include "SpriteComponent.h"
#include "Texture.h"
#include "Shader.h"
#include "Object.h"
#include "GameSys.h"

SpriteComponent::SpriteComponent(Object *owner, int drawOrder) : Component(owner),
                                                                 mTexture(nullptr),
                                                                 mDrawOrder(drawOrder),
                                                                 mTexWidth(0), mTexHeight(0)
{
    mOwner->getGameSys()->AddSprite(this);
}

SpriteComponent::~SpriteComponent()
{
    mOwner->getGameSys()->RemoveSprite(this);
}

void SpriteComponent::SetTexture(Texture *texture)
{
    mTexture = texture;
    mTexHeight = texture->getHeight();
    mTexWidth = texture->getWidth();
}

void SpriteComponent::Draw(Shader *shader)
{
    if (mTexture)
    {
        glm::mat4 scaleMat = glm::mat4(1.0f);
        scaleMat = glm::scale(scaleMat, glm::vec3(static_cast<float>(mTexWidth),
                                                  static_cast<float>(mTexHeight), 1.0f));

        //问题你妈出在这里 glm矩阵相乘需要顺序反过来
        glm::mat4 world = mOwner->getWorldTransform() * scaleMat;

        shader->SetMatrixUniform("uWorldTransform", world);
        mTexture->SetActive();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    }
}
