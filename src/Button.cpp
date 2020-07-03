//
// Created by 蔡元涵 on 2020/6/30.
//

#include "Button.h"
#include "Font.h"
#include "UIObject.h"
#include "SpriteComponent.h"

Button::Button(class GameSys *gameSys, class UIObject *uiObject, std::string texPath,
               int buttonType, std::string text, glm::vec2 buttonPos, int buttonFunc, int size)
        : Object(gameSys), mText(text), mButtonType(buttonType), mButtonFunc(buttonFunc)
{
    setPosition(buttonPos);
    mSC = new SpriteComponent(this, 20);
    mSC->SetTexture(gameSys->GetTexture(texPath));

    mFont = uiObject->getFont();
    mFontSC = new SpriteComponent(this, 30);
    mFontSC->SetTexture(mFont->RenderText(text, size));

    uiObject->AddButton(this);
}
