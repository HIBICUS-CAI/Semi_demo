//
// Created by 蔡元涵 on 2020/6/30.
//

#include "UIObject.h"
#include "SpriteComponent.h"
#include "UIInputComponent.h"
#include "Button.h"
#include "TextZone.h"
#include "Font.h"
#include "Item.h"
#include "Document.h"

UIObject::UIObject(class GameSys *gameSys, std::string texPath) : Object(gameSys),
                                                                  mGameSys(gameSys),
                                                                  mHasChildUIO(false),
                                                                  mIsInventory(false)
{
    mUIOConfig = gameSys->GetInitObjRoot()["UIConfig"];
    mSC = new SpriteComponent(this, 1000);
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
     * 4: 开启物品栏
     * 5: 使用道具
     * 6: 阅读文档
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

            if (mIsInventory)
            {
                for (auto item : mGameSys->getItemsInInventory())
                {
                    item->SetIsVisibleInventory(false);
                }
                for (auto doc : mGameSys->getDocsInInventory())
                {
                    doc->SetIsVisibleInventory(false);
                }
            }
            if (getParentUIO()->isInventory())
            {
                for (auto item : mGameSys->getItemsInInventory())
                {
                    item->SetIsVisibleInventory(true);
                }
                for (auto doc : mGameSys->getDocsInInventory())
                {
                    doc->SetIsVisibleInventory(true);
                }
            }

            TurnOff();
            getParentUIO()->TurnOn();
            break;
        case 4:
            SDL_Log("Inventory button has been pressed.");

            if (mHasChildUIO)
            {
                for (auto item : mGameSys->getItemsInInventory())
                {
                    item->SetIsVisibleInventory(true);
                }
                for (auto doc : mGameSys->getDocsInInventory())
                {
                    doc->SetIsVisibleInventory(true);
                }

                mChildUIO->TurnOn();
            } else
            {
                mHasChildUIO = true;

                for (auto item : mGameSys->getItemsInInventory())
                {
                    item->SetIsVisibleInventory(true);
                }
                for (auto doc : mGameSys->getDocsInInventory())
                {
                    doc->SetIsVisibleInventory(true);
                }

                Json::Value inventoryUI = mGameSys->GetInitObjRoot()["UIObjects"]["InventoryUI"];
                mChildUIO = new UIObject(mGameSys, inventoryUI["UITexPath"].asString());
                mChildUIO->setIsInventory(true);
                mChildUIO->setParentUIO(this);
                for (int i = 0; i < inventoryUI["Button"].size(); ++i)
                {
                    mChildUIO->CreateButton(mGameSys, mChildUIO,
                                            inventoryUI["Button"][i]["TexPath"].asString(),
                                            inventoryUI["Button"][i]["Type"].asInt(),
                                            inventoryUI["Button"][i]["Text"].asString(),
                                            {inventoryUI["Button"][i]["Position"][0].asFloat(),
                                             inventoryUI["Button"][i]["Position"][1].asFloat()},
                                            inventoryUI["Button"][i]["Function"].asInt());
                }
            }

            TurnOff();
            break;
        case 5:
        {
            glm::vec2 clickPos = mUIIC->getMouseClickPos();
            int index = GetClickItemIndex(clickPos);

            SDL_Log("use item witch index is: %d", index);
            if (index + 1 > mGameSys->getItemsInInventory().size())
            {
                SDL_Log("You don't have item here");
            } else
            {
                mGameSys->UseItemInUI(mGameSys->getItemsInInventory()[index]->UseItem());
            }
        }

            break;
        case 6:
        {
            glm::vec2 clickPos = mUIIC->getMouseClickPos();
            int index = GetClickDocIndex(clickPos);
            Json::Value docUI = mGameSys->GetInitObjRoot()["UIObjects"]["ReadDocUI"];

            SDL_Log("read doc witch index is: %d", index);
            if (index + 1 > mGameSys->getDocsInInventory().size())
            {
                SDL_Log("You don't have doc here");
            } else
            {
                if (mHasChildUIO)
                {
                    mChildUIO->TurnOn();

                    TextZone *title = mChildUIO->FindText(docUI["TextZone"][0]["ID"].asInt());
                    if (title != nullptr)
                    {
                        // 设置标题
                        title->setText(mGameSys->getDocsInInventory()[index]->ReadDoc().title);
                    }
                    TextZone *text = mChildUIO->FindText(docUI["TextZone"][1]["ID"].asInt());
                    if (text != nullptr)
                    {
                        // 设置正文
                        text->setText(
                                mGameSys->getDocsInInventory()[index]->ReadDoc().mainText);
                    }
                } else
                {
                    mHasChildUIO = true;

                    mChildUIO = new UIObject(mGameSys, docUI["UITexPath"].asString());
                    mChildUIO->setParentUIO(this);
                    for (int i = 0; i < docUI["Button"].size(); ++i)
                    {
                        mChildUIO->CreateButton(mGameSys, mChildUIO,
                                                docUI["Button"][i]["TexPath"].asString(),
                                                docUI["Button"][i]["Type"].asInt(),
                                                docUI["Button"][i]["Text"].asString(),
                                                {docUI["Button"][i]["Position"][0].asFloat(),
                                                 docUI["Button"][i]["Position"][1].asFloat()},
                                                docUI["Button"][i]["Function"].asInt());
                    }
                    for (int i = 0; i < docUI["TextZone"].size(); ++i)
                    {
                        mChildUIO->CreateTextZone(mGameSys, mChildUIO,
                                                  {docUI["TextZone"][i]["Position"][0].asFloat(),
                                                   docUI["TextZone"][i]["Position"][1].asFloat()},
                                                  docUI["TextZone"][i]["Width"].asInt(),
                                                  docUI["TextZone"][i]["ID"].asInt());
                    }

                    TextZone *title = mChildUIO->FindText(docUI["TextZone"][0]["ID"].asInt());
                    if (title != nullptr)
                    {
                        SDL_Log("1");
                        // 设置标题
                        title->setText(mGameSys->getDocsInInventory()[index]->ReadDoc().title);
                    }
                    TextZone *text = mChildUIO->FindText(docUI["TextZone"][1]["ID"].asInt());
                    if (text != nullptr)
                    {
                        SDL_Log("2");
                        // 设置正文
                        text->setText(
                                mGameSys->getDocsInInventory()[index]->ReadDoc().mainText);
                    }
                }

                TurnOff();
                for (auto item : mGameSys->getItemsInInventory())
                {
                    item->SetIsVisibleInventory(false);
                }
                for (auto doc : mGameSys->getDocsInInventory())
                {
                    doc->SetIsVisibleInventory(false);
                }
            }
        }

            break;
        default:
            break;
    }
}
