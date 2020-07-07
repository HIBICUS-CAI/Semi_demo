//
// Created by 蔡元涵 on 2020/6/30.
//

#ifndef SEMI_DEMO_UIOBJECT_H
#define SEMI_DEMO_UIOBJECT_H

#include "Object.h"
#include "SpriteComponent.h"

class UIObject : public Object
{
public:
    UIObject(class GameSys *gameSys, std::string texPath);

    void CreateButton(class GameSys *gameSys, class UIObject *uiObject, std::string texPath,
                      int buttonType, std::string text, glm::vec2 buttonPos, int buttonFunc,
                      int size = 16);

    void CreateTextZone(class GameSys *gameSys, class UIObject *uiObject, glm::vec2 positon,
                        int textWidth, int id);

    void AddButton(class Button *button);

    void AddText(class TextZone *text);

    TextZone *FindText(int id);

    void TurnOff();

    void TurnOn();

    void ButtonEvent(class Button *button);

    const std::vector<struct Button *> &getButtons() const
    {
        return mButtons;
    }

    SpriteComponent *getSC() const
    {
        return mSC;
    }

    UIObject *getChildUIO() const
    {
        return mChildUIO;
    }

    UIObject *getParentUIO() const
    {
        return mParentUIO;
    }

    void setParentUIO(UIObject *mParentUio)
    {
        mParentUIO = mParentUio;
    }

    Font *getFont() const
    {
        return mFont;
    }

private:
    std::vector<class Button *> mButtons;
    std::vector<class TextZone *> mTexts;

    class Font *mFont;

    class SpriteComponent *mSC;

    class UIInputComponent *mUIIC;

    class GameSys *mGameSys;

    bool mHasChildUIO;

    class UIObject *mChildUIO;

    class UIObject *mParentUIO;
};


#endif //SEMI_DEMO_UIOBJECT_H
