//
// Created by 蔡元涵 on 2020/6/30.
//

#include "UIObject.h"
#include "SpriteComponent.h"
#include "UIInputComponent.h"
#include "ButtonEventComponent.h"
#include "Button.h"
#include "TextZone.h"
#include "Font.h"
#include "Item.h"
#include "Document.h"

UIObject::UIObject(class GameSys *gameSys, std::string texPath) : Object(gameSys),
                                                                  mGameSys(gameSys),
                                                                  mHasChildUIO(false),
                                                                  mIsInventory(false),
                                                                  mIndex(-1),
                                                                  mHasDocUIO(false),
                                                                  mHasItemUIO(false),
                                                                  mItemUIO(nullptr),
                                                                  mDocUIO(nullptr)
{
    mUIOConfig = gameSys->GetInitObjRoot()["UIConfig"];
    mSC = new SpriteComponent(this, 1000);
    mSC->SetTexture(gameSys->GetTexture(texPath));

    mFont = gameSys->GetFont(mUIOConfig["FontPath"].asString());

    mUIIC = new UIInputComponent(this, this);

    mBEC = new ButtonEventComponent(this, this);
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

void UIObject::DeltaMove(glm::vec2 delta)
{
    glm::vec2 dialogSelf = {100.f, 50.f};
    setPosition(getPosition() + delta + dialogSelf);

    for (auto button : mButtons)
    {
        button->setPosition(button->getPosition() + delta + dialogSelf);
    }
    for (auto textZone : mTexts)
    {
        textZone->setPosition(textZone->getPosition() + delta + dialogSelf);
    }

    if (getPosition().x < (-512.f + 100.f))
    {
        DeltaMove({50.f - dialogSelf.x, 0.f - dialogSelf.y});
    } else if (getPosition().x > (512.f - 100.f))
    {
        DeltaMove({-50.f - dialogSelf.x, 0.f - dialogSelf.y});
    }
    if (getPosition().y < (-384.f + 50.f))
    {
        DeltaMove({0.f - dialogSelf.x, 50.f - dialogSelf.y});
    } else if (getPosition().y > (384.f - 50.f))
    {
        DeltaMove({0.f - dialogSelf.x, -50.f - dialogSelf.y});
    }
}
