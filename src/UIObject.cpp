//
// Created by 蔡元涵 on 2020/6/30.
//

#include "UIObject.h"
#include "SpriteComponent.h"
#include "UIInputComponent.h"
#include "Button.h"

UIObject::UIObject(class GameSys *gameSys, std::string texPath) : Object(gameSys),
                                                                  mGameSys(gameSys)
{
    mSC = new SpriteComponent(this, 10);
    mSC->SetTexture(gameSys->GetTexture(texPath));

    mUIIC = new UIInputComponent(this, this);
}

void
UIObject::CreateButton(class GameSys *gameSys, class UIObject *uiObject, std::string texPath,
                       int buttonType, std::string text, glm::vec2 buttonPos, int buttonFunc)
{
    new Button(gameSys, uiObject, texPath, buttonType, text, buttonPos, buttonFunc);
}

void UIObject::AddButton(class Button *button)
{
    mButtons.emplace_back(button);
}

void UIObject::TurnOff()
{
    for (auto button : mButtons)
    {
        button->getSC()->setIsVisible(false);
        button->setState(Pause);
    }

    mSC->setIsVisible(false);
    setState(Pause);
}

void UIObject::TurnOn()
{
    for (auto button : mButtons)
    {
        button->getSC()->setIsVisible(true);
        button->setState(Active);
    }

    mSC->setIsVisible(true);
    setState(Active);
}

void UIObject::ButtonEvent(class Button *button)
{
    /**
     * 1: 开始进行游戏
     * 2: 显示操作介绍界面
     * 3: 关闭窗口
     */
    switch (button->getButtonFunc())
    {
        case 1:
            SDL_Log("Game Start button has been pressed.");
            mGameSys->BeginGame();
            TurnOff();
            break;
        case 2:
            SDL_Log("Help button has been pressed.");
            mChildUIO = new UIObject(mGameSys, "../Assets/help_window.png");
            mChildUIO->setParentUIO(this);
            mChildUIO->CreateButton(mGameSys, mChildUIO, "../Assets/cross-1.png", 1, "",
                                    {256.f, 192.f}, 3);

            TurnOff();
            break;
        case 3:
            SDL_Log("Close button has been pressed.");

            TurnOff();
            getParentUIO()->TurnOn();
            break;
        default:
            break;
    }
}
