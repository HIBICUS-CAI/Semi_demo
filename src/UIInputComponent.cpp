//
// Created by 蔡元涵 on 2020/6/30.
//

#include "UIInputComponent.h"
#include "UIObject.h"
#include "Button.h"

UIInputComponent::UIInputComponent(class Object *owner, class UIObject *uiObject,
                                   int updateOrder) : Component(owner, updateOrder),
                                                      mUIObject(uiObject),
                                                      mMouseClickPos(900.f, 900.f)
{}

void UIInputComponent::UIInput(const glm::vec2 mouseClickPos)
{
    mMouseClickPos = mouseClickPos;
    SDL_Log("[%f ,%f] form UI INPUT", mMouseClickPos.x, mMouseClickPos.y);
}

void UIInputComponent::Update(float deltatime)
{
    for (auto button : mUIObject->getButtons())
    {
        switch (button->getButtonType())
        {
            /**
             * 0: 开始界面的两个
             * 1: 关闭窗口的叉号
             */
            case 0:
                if (mMouseClickPos.x != 900.f && mMouseClickPos.y != 900.f)
                {
                    glm::vec2 distance = button->getPosition() - mMouseClickPos;
                    if (distance.x * distance.x <= 50.f * 50.f &&
                        distance.y * distance.y <= 25.f * 25.f)
                    {
                        mUIObject->ButtonEvent(button);
                    }
                }
                break;
            case 1:
                if (mMouseClickPos.x != 900.f && mMouseClickPos.y != 900.f)
                {
                    glm::vec2 distance = button->getPosition() - mMouseClickPos;
                    if (distance.x * distance.x <= 10.f * 10.f &&
                        distance.y * distance.y <= 10.f * 10.f)
                    {
                        mUIObject->ButtonEvent(button);
                    }
                }
                break;
            default:
                break;
        }
    }

    mMouseClickPos = {900.f, 900.f};
}
