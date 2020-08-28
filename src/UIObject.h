//
// Created by 蔡元涵 on 2020/6/30.
//

#ifndef SEMI_DEMO_UIOBJECT_H
#define SEMI_DEMO_UIOBJECT_H

#include "Object.h"
#include "SpriteComponent.h"
#include "UIInputComponent.h"
#include "ButtonEventComponent.h"

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

    void DeltaMove(glm::vec2 delta);

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

    const Json::Value &getUIOConfig() const
    {
        return mUIOConfig;
    }

    void setIsInventory(bool mIsInventory)
    {
        UIObject::mIsInventory = mIsInventory;
    }

    bool isInventory() const
    {
        return mIsInventory;
    }

    int getIndex() const
    {
        return mIndex;
    }

    void setIndex(int mIndex)
    {
        UIObject::mIndex = mIndex;
    }

    bool hasChildUIO() const
    {
        return mHasChildUIO;
    }

    bool hasItemUIO() const
    {
        return mHasItemUIO;
    }

    UIObject *getItemUIO() const
    {
        return mItemUIO;
    }

    bool hasDocUIO() const
    {
        return mHasDocUIO;
    }

    UIObject *getDocUIO() const
    {
        return mDocUIO;
    }

    void setHasChildUIO(bool mHasChildUio)
    {
        mHasChildUIO = mHasChildUio;
    }

    void setHasItemUIO(bool mHasItemUio)
    {
        mHasItemUIO = mHasItemUio;
    }

    void setHasDocUIO(bool mHasDocUio)
    {
        mHasDocUIO = mHasDocUio;
    }

    void setChildUIO(UIObject *mChildUio)
    {
        mChildUIO = mChildUio;
    }

    void setItemUIO(UIObject *mItemUio)
    {
        mItemUIO = mItemUio;
    }

    void setDocUIO(UIObject *mDocUio)
    {
        mDocUIO = mDocUio;
    }

    UIInputComponent *getUIIC() const
    {
        return mUIIC;
    }

    ButtonEventComponent *getBEC() const
    {
        return mBEC;
    }

private:
    std::vector<class Button *> mButtons;
    std::vector<class TextZone *> mTexts;

    bool mIsInventory;

    // 用于记录需要记录的数值
    int mIndex;

    class Font *mFont;

    class SpriteComponent *mSC;

    class UIInputComponent *mUIIC;

    class ButtonEventComponent *mBEC;

    class GameSys *mGameSys;

    bool mHasChildUIO;

    class UIObject *mChildUIO;

    bool mHasItemUIO;

    class UIObject *mItemUIO;

    bool mHasDocUIO;

    class UIObject *mDocUIO;

    class UIObject *mParentUIO;

    Json::Value mUIOConfig;
};


#endif //SEMI_DEMO_UIOBJECT_H
