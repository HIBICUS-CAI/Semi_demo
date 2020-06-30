//
// Created by 蔡元涵 on 2020/6/30.
//

#include "Button.h"
#include "UIObject.h"
#include "SpriteComponent.h"

Button::Button(class GameSys *gameSys, class UIObject *uiObject, std::string texPath,
               int buttonType, std::string text, glm::vec2 buttonPos, int buttonFunc) : Object(
        gameSys), mText(text), mButtonType(buttonType), mButtonFunc(buttonFunc)
{
    setPosition(buttonPos);
    mSC = new SpriteComponent(this, 20);
    mSC->SetTexture(gameSys->GetTexture(texPath));

    uiObject->AddButton(this);
}
