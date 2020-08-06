//
// Created by 蔡元涵 on 2020/7/7.
//

#include "TextZone.h"
#include "Font.h"
#include "UIObject.h"
#include "SpriteComponent.h"

TextZone::TextZone(class GameSys *gameSys, class UIObject *uiObject, glm::vec2 positon,
                   int textWidth, int id) : Object(gameSys), mIsTextChange(false),
                                            mTextWidth(textWidth), mID(id)
{
    setPosition(positon);
    mFont = uiObject->getFont();
    mFontSC = new SpriteComponent(this, 1030);

    uiObject->AddText(this);
}

void TextZone::UpdateObject(float deltatime)
{
    if (mIsTextChange)
    {
        mFontSC->SetTexture(mFont->RenderText(mText, 16, mTextWidth));
        mIsTextChange = false;
    }
}
