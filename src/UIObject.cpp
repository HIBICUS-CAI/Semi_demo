//
// Created by 蔡元涵 on 2020/6/30.
//

#include "UIObject.h"
#include "SpriteComponent.h"
#include "UIInputComponent.h"
#include "Button.h"
#include "TextZone.h"
#include "Font.h"

UIObject::UIObject(class GameSys *gameSys, std::string texPath) : Object(gameSys),
                                                                  mGameSys(gameSys),
                                                                  mHasChildUIO(false)
{
    mSC = new SpriteComponent(this, 10);
    mSC->SetTexture(gameSys->GetTexture(texPath));

    mFont = gameSys->GetFont("../Assets/heiti.ttc");

    mUIIC = new UIInputComponent(this, this);
}

void
UIObject::CreateButton(class GameSys *gameSys, class UIObject *uiObject, std::string texPath,
                       int buttonType, std::string text, glm::vec2 buttonPos, int buttonFunc,
                       int size)
{
    new Button(gameSys, uiObject, texPath, buttonType, text, buttonPos, buttonFunc, size);
}

void
UIObject::CreateTextZone(class GameSys *gameSys, class UIObject *uiObject, glm::vec2 positon,
                         int textWidth, int id)
{
    new TextZone(gameSys, uiObject, positon, textWidth, id);
}

void UIObject::AddButton(class Button *button)
{
    mButtons.emplace_back(button);
}

void UIObject::AddText(class TextZone *text)
{
    mTexts.emplace_back(text);
}

TextZone *UIObject::FindText(int id)
{
    TextZone *textZone = nullptr;
    for (auto text : mTexts)
    {
        if (text->getID() == id)
        {
            textZone = text;
            break;
        }
    }
    if (textZone == nullptr)
    {
        SDL_Log("TextZone Not Found With ID: %d", id);
    }

    return textZone;
}

void UIObject::TurnOff()
{
    for (auto button : mButtons)
    {
        button->getSC()->setIsVisible(false);
        button->getFontSC()->setIsVisible(false);
        button->setState(Pause);
    }
    for (auto text : mTexts)
    {
        text->getFontSC()->setIsVisible(false);
        text->setState(Pause);
    }

    mSC->setIsVisible(false);
    setState(Pause);
}

void UIObject::TurnOn()
{
    for (auto button : mButtons)
    {
        button->getSC()->setIsVisible(true);
        button->getFontSC()->setIsVisible(true);
        button->setState(Active);
    }
    for (auto text : mTexts)
    {
        text->getFontSC()->setIsVisible(true);
        text->setState(Active);
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
            if (mHasChildUIO)
            {
                mChildUIO->TurnOn();
            } else
            {
                mHasChildUIO = true;
                //需要修改贴图,或者找出让SDL_TTF换行的方法,当前方案需要计算字符数量,很嗨麻烦
                mChildUIO = new UIObject(mGameSys, "../Assets/help_window.png");
                mChildUIO->setParentUIO(this);
                mChildUIO->CreateButton(mGameSys, mChildUIO, "../Assets/cross-1.png",
                                        1, " ", {256.f, 192.f},
                                        3);
                mChildUIO->CreateTextZone(mGameSys, mChildUIO, mChildUIO->getPosition(),
                                          300, 0);
                TextZone *text = mChildUIO->FindText(0);
                if (text != nullptr)
                {
                    text->setPosition({getPosition().x, getPosition().y + 100.f});
                    text->setText("这里是帮助信息，今天天气好好啊。");
                }
            }

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
