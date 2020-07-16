//
// Created by 蔡元涵 on 2020/6/30.
//

#include "UIInputComponent.h"
#include "UIObject.h"
#include "Button.h"

UIInputComponent::UIInputComponent(class Object *owner, class UIObject *uiObject,
                                   int updateOrder) : Component(owner, updateOrder),
                                                      mUIObject(uiObject)
{
    mMouseClickPos = {mUIObject->getUIOConfig()["MouseClickPos"][0].asFloat(),
                      mUIObject->getUIOConfig()["MouseClickPos"][1].asFloat()};
}

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
                if (mMouseClickPos.x !=
                    mUIObject->getUIOConfig()["MouseClickPos"][0].asFloat() &&
                    mMouseClickPos.y !=
                    mUIObject->getUIOConfig()["MouseClickPos"][1].asFloat())
                {
                    glm::vec2 distance = button->getPosition() - mMouseClickPos;
                    float borderWid = mUIObject->getUIOConfig()["ButtonBorder"][0]["Width"].asFloat();
                    float borderHei = mUIObject->getUIOConfig()["ButtonBorder"][0]["Height"].asFloat();
                    if (distance.x * distance.x <= borderWid / 2.f * borderWid / 2.f &&
                        distance.y * distance.y <= borderHei / 2.f * borderHei / 2.f)
                    {
                        mUIObject->ButtonEvent(button);
                    }
                }
                break;
            case 1:
                if (mMouseClickPos.x !=
                    mUIObject->getUIOConfig()["MouseClickPos"][0].asFloat() &&
                    mMouseClickPos.y !=
                    mUIObject->getUIOConfig()["MouseClickPos"][1].asFloat())
                {
                    glm::vec2 distance = button->getPosition() - mMouseClickPos;
                    float borderWid = mUIObject->getUIOConfig()["ButtonBorder"][1]["Width"].asFloat();
                    float borderHei = mUIObject->getUIOConfig()["ButtonBorder"][1]["Height"].asFloat();
                    if (distance.x * distance.x <= borderWid / 2.f * borderWid / 2.f &&
                        distance.y * distance.y <= borderHei / 2.f * borderHei / 2.f)
                    {
                        mUIObject->ButtonEvent(button);
                    }
                }
                break;
            default:
                break;
        }
    }

    mMouseClickPos = {mUIObject->getUIOConfig()["MouseClickPos"][0].asFloat(),
                      mUIObject->getUIOConfig()["MouseClickPos"][1].asFloat()};
}
