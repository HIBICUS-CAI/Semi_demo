//
// Created by 蔡元涵 on 2020/6/30.
//

#ifndef SEMI_DEMO_BUTTON_H
#define SEMI_DEMO_BUTTON_H

#include "Object.h"
#include "SpriteComponent.h"

class Button : public Object
{
public:
    Button(class GameSys *gameSys, class UIObject *uiObject, std::string texPath,
           int buttonType, std::string text, glm::vec2 buttonPos, int buttonFunc, int size);

    SpriteComponent *getSC() const
    {
        return mSC;
    }

    SpriteComponent *getFontSC() const
    {
        return mFontSC;
    }

    int getButtonType() const
    {
        return mButtonType;
    }

    int getButtonFunc() const
    {
        return mButtonFunc;
    }

private:
    class SpriteComponent *mSC;

    //文字贴图
    class SpriteComponent *mFontSC;

    int mButtonType;
    int mButtonFunc;
    std::string mText;

    class Font *mFont;
};


#endif //SEMI_DEMO_BUTTON_H
