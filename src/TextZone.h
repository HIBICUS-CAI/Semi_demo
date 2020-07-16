//
// Created by 蔡元涵 on 2020/7/7.
//

#ifndef SEMI_DEMO_TEXTZONE_H
#define SEMI_DEMO_TEXTZONE_H

#include "Object.h"
#include "SpriteComponent.h"

class TextZone : public Object
{
public:
    TextZone(class GameSys *gameSys, class UIObject *uiObject, glm::vec2 positon,
             int textWidth, int id);

    void UpdateObject(float deltatime) override;

    SpriteComponent *getFontSC() const
    {
        return mFontSC;
    }

    const std::string &getText() const
    {
        return mText;
    }

    void setText(const std::string &mText)
    {
        TextZone::mText = mText;
        mIsTextChange = true;
    }

    int getID() const
    {
        return mID;
    }

private:
    std::string mText;
    int mTextWidth;
    bool mIsTextChange;

    int mID;

    class Font *mFont;

    class SpriteComponent *mFontSC;
};


#endif //SEMI_DEMO_TEXTZONE_H
