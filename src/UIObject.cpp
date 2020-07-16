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
    mUIOConfig = gameSys->GetInitObjRoot()["UIConfig"];
    mSC = new SpriteComponent(this, 10);
    mSC->SetTexture(gameSys->GetTexture(texPath));

    mFont = gameSys->GetFont(mUIOConfig["FontPath"].asString());

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
                Json::Value helpUI = mGameSys->GetInitObjRoot()["UIObjects"]["HelpUI"];
                Json::Value buttonInfo;
                Json::Value textInfo = helpUI["TextZone"];

                //需要修改贴图,或者找出让SDL_TTF换行的方法,当前方案需要计算字符数量,很嗨麻烦
                mChildUIO = new UIObject(mGameSys, helpUI["UITexPath"].asString());
                mChildUIO->setParentUIO(this);
                for (int i = 0; i < helpUI["Button"].size(); ++i)
                {
                    buttonInfo = helpUI["Button"][i];
                    mChildUIO->CreateButton(mGameSys, mChildUIO,
                                            buttonInfo["TexPath"].asString(),
                                            buttonInfo["Type"].asInt(),
                                            buttonInfo["Text"].asString(),
                                            {buttonInfo["Position"][0].asFloat(),
                                             buttonInfo["Position"][1].asFloat()},
                                            buttonInfo["Function"].asInt());
                }

                mChildUIO->CreateTextZone(mGameSys, mChildUIO, mChildUIO->getPosition(),
                                          textInfo["Width"].asInt(), textInfo["ID"].asInt());
                TextZone *text = mChildUIO->FindText(textInfo["ID"].asInt());
                if (text != nullptr)
                {
                    text->setPosition({getPosition().x, getPosition().y + 100.f});
                    text->setText(textInfo["Text"].asString());
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
