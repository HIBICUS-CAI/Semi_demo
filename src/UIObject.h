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
                      int buttonType, std::string text, glm::vec2 buttonPos, int buttonFunc);

    void AddButton(class Button *button);

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

private:
    std::vector<class Button *> mButtons;

    class SpriteComponent *mSC;

    class UIInputComponent *mUIIC;

    class GameSys *mGameSys;

    class UIObject *mChildUIO;
    class UIObject *mParentUIO;
};


#endif //SEMI_DEMO_UIOBJECT_H
