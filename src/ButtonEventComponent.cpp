//
// Created by 蔡元涵 on 2020/8/14.
//

#include "ButtonEventComponent.h"
#include "UIObject.h"
#include "TextZone.h"
#include "Item.h"
#include "Document.h"

ButtonEventComponent::ButtonEventComponent(class Object *owner, class UIObject *uiObject,
                                           int updateOrder) : Component(owner, updateOrder),
                                                              mOwnerUIO(uiObject)
{}

void ButtonEventComponent::PressButton(int func_id)
{
    ButtonEvent(func_id);
}

void ButtonEventComponent::ButtonEvent(int func_id)
{
    /**
     * 1: 开始进行游戏
     * 2: 显示操作介绍界面
     * 3: 关闭窗口
     * 4: 开启物品栏
     * 5: 展示道具
     * 6: 阅读文档
     * 7: 使用道具
     */
    switch (func_id)
    {
        case 1:
            ClickBtn_StartGame();
            break;
        case 2:
            ClickBtn_GetHelp();
            break;
        case 3:
            ClickBtn_CloseWnd();
            break;
        case 4:
            ClickBtn_OpenInventory();
            break;
        case 5:
            ClickBtn_ShowItem();
            break;
        case 6:
            ClickBtn_ReadDoc();
            break;
        case 7:
            ClickBtn_UseItem();
            break;
        default:
            break;
    }
}

// 1: 开始进行游戏
void ButtonEventComponent::ClickBtn_StartGame()
{
    SDL_Log("Game Start button has been pressed.");
    mOwner->getGameSys()->BeginGame();
    mOwnerUIO->TurnOff();
}

// 2: 显示操作介绍界面
void ButtonEventComponent::ClickBtn_GetHelp()
{
    SDL_Log("Help button has been pressed.");
    if (mOwnerUIO->hasChildUIO())
    {
        mOwnerUIO->getChildUIO()->TurnOn();
    } else
    {
        mOwnerUIO->setHasChildUIO(true);
        Json::Value helpUI = mOwner->getGameSys()->GetInitObjRoot()["UIObjects"]["HelpUI"];
        Json::Value buttonInfo;
        Json::Value textInfo = helpUI["TextZone"];

        //需要修改贴图,或者找出让SDL_TTF换行的方法,当前方案需要计算字符数量,很嗨麻烦
        mOwnerUIO->setChildUIO(
                new UIObject(mOwner->getGameSys(), helpUI["UITexPath"].asString()));
        mOwnerUIO->getChildUIO()->setParentUIO(mOwnerUIO);
        for (int i = 0; i < helpUI["Button"].size(); ++i)
        {
            buttonInfo = helpUI["Button"][i];
            mOwnerUIO->getChildUIO()->CreateButton(mOwner->getGameSys(),
                                                   mOwnerUIO->getChildUIO(),
                                                   buttonInfo["TexPath"].asString(),
                                                   buttonInfo["Type"].asInt(),
                                                   buttonInfo["Text"].asString(),
                                                   {buttonInfo["Position"][0].asFloat(),
                                                    buttonInfo["Position"][1].asFloat()},
                                                   buttonInfo["Function"].asInt());
        }

        mOwnerUIO->getChildUIO()->CreateTextZone(mOwner->getGameSys(),
                                                 mOwnerUIO->getChildUIO(),
                                                 mOwnerUIO->getChildUIO()->getPosition(),
                                                 textInfo["Width"].asInt(),
                                                 textInfo["ID"].asInt());
        TextZone *text = mOwnerUIO->getChildUIO()->FindText(textInfo["ID"].asInt());
        if (text != nullptr)
        {
            text->setPosition(
                    {mOwnerUIO->getPosition().x, mOwnerUIO->getPosition().y + 100.f});
            text->setText(textInfo["Text"].asString());
        }
    }

    mOwnerUIO->TurnOff();
}

// 3: 关闭窗口
void ButtonEventComponent::ClickBtn_CloseWnd()
{
    SDL_Log("Close button has been pressed.");

    if (mOwnerUIO->isInventory())
    {
        for (auto item : mOwner->getGameSys()->getItemsInInventory())
        {
            item->SetIsVisibleInventory(false);
        }
        for (auto doc : mOwner->getGameSys()->getDocsInInventory())
        {
            doc->SetIsVisibleInventory(false);
        }
    }
    if (mOwnerUIO->getParentUIO()->isInventory())
    {
        for (auto item : mOwner->getGameSys()->getItemsInInventory())
        {
            item->SetIsVisibleInventory(true);
        }
        for (auto doc : mOwner->getGameSys()->getDocsInInventory())
        {
            doc->SetIsVisibleInventory(true);
        }
    }

    mOwnerUIO->TurnOff();
    mOwnerUIO->getParentUIO()->TurnOn();
}

// 4: 开启物品栏
void ButtonEventComponent::ClickBtn_OpenInventory()
{
    SDL_Log("Inventory button has been pressed.");

    if (mOwnerUIO->hasChildUIO())
    {
        for (auto item : mOwner->getGameSys()->getItemsInInventory())
        {
            item->SetIsVisibleInventory(true);
        }
        for (auto doc : mOwner->getGameSys()->getDocsInInventory())
        {
            doc->SetIsVisibleInventory(true);
        }

        mOwnerUIO->getChildUIO()->TurnOn();
    } else
    {
        mOwnerUIO->setHasChildUIO(true);

        for (auto item : mOwner->getGameSys()->getItemsInInventory())
        {
            item->SetIsVisibleInventory(true);
        }
        for (auto doc : mOwner->getGameSys()->getDocsInInventory())
        {
            doc->SetIsVisibleInventory(true);
        }

        Json::Value inventoryUI = mOwner->getGameSys()->GetInitObjRoot()["UIObjects"]["InventoryUI"];
        mOwnerUIO->setChildUIO(new UIObject(mOwner->getGameSys(),
                                            inventoryUI["UITexPath"].asString()));
        mOwnerUIO->getChildUIO()->setIsInventory(true);
        mOwnerUIO->getChildUIO()->setParentUIO(mOwnerUIO);
        for (int i = 0; i < inventoryUI["Button"].size(); ++i)
        {
            mOwnerUIO->getChildUIO()->CreateButton(mOwner->getGameSys(),
                                                   mOwnerUIO->getChildUIO(),
                                                   inventoryUI["Button"][i]["TexPath"].asString(),
                                                   inventoryUI["Button"][i]["Type"].asInt(),
                                                   inventoryUI["Button"][i]["Text"].asString(),
                                                   {inventoryUI["Button"][i]["Position"][0].asFloat(),
                                                    inventoryUI["Button"][i]["Position"][1].asFloat()},
                                                   inventoryUI["Button"][i]["Function"].asInt());
        }
    }

    mOwnerUIO->TurnOff();
}

// 5: 展示道具
void ButtonEventComponent::ClickBtn_ShowItem()
{
    glm::vec2 clickPos = mOwnerUIO->getUIIC()->getMouseClickPos();
    int index = GetClickItemIndex(clickPos);
    TextZone *textZone;

    SDL_Log("use item witch index is: %d", index);
    if (index + 1 > mOwner->getGameSys()->getItemsInInventory().size())
    {
        SDL_Log("You don't have item here");
    } else
    {
        Json::Value itemUI = mOwner->getGameSys()->GetInitObjRoot()["UIObjects"]["UseItemUI"];

        if (mOwnerUIO->hasItemUIO())
        {
            mOwnerUIO->getItemUIO()->TurnOn();
            mOwnerUIO->getItemUIO()->setIndex(index);

            textZone = mOwnerUIO->getItemUIO()->FindText(
                    itemUI["TextZone"][0]["ID"].asInt());
            if (textZone != nullptr)
            {
                textZone->setText(
                        mOwner->getGameSys()->getItemsInInventory()[index]->UseItem().name);
            }
            textZone = mOwnerUIO->getItemUIO()->FindText(
                    itemUI["TextZone"][1]["ID"].asInt());
            if (textZone != nullptr)
            {
                textZone->setText(
                        mOwner->getGameSys()->getItemsInInventory()[index]->UseItem().description);
            }
        } else
        {
            mOwnerUIO->setHasItemUIO(true);
            mOwnerUIO->setItemUIO(new UIObject(mOwner->getGameSys(),
                                               itemUI["UITexPath"].asString()));
            mOwnerUIO->getItemUIO()->setParentUIO(mOwnerUIO);
            mOwnerUIO->getItemUIO()->setIndex(index);
            for (int i = 0; i < itemUI["Button"].size(); ++i)
            {
                mOwnerUIO->getItemUIO()->CreateButton(mOwner->getGameSys(),
                                                      mOwnerUIO->getItemUIO(),
                                                      itemUI["Button"][i]["TexPath"].asString(),
                                                      itemUI["Button"][i]["Type"].asInt(),
                                                      itemUI["Button"][i]["Text"].asString(),
                                                      {itemUI["Button"][i]["Position"][0].asFloat(),
                                                       itemUI["Button"][i]["Position"][1].asFloat()},
                                                      itemUI["Button"][i]["Function"].asInt());
            }
            for (int i = 0; i < itemUI["TextZone"].size(); ++i)
            {
                mOwnerUIO->getItemUIO()->CreateTextZone(mOwner->getGameSys(),
                                                        mOwnerUIO->getItemUIO(),
                                                        {itemUI["TextZone"][i]["Position"][0].asFloat(),
                                                         itemUI["TextZone"][i]["Position"][1].asFloat()},
                                                        itemUI["TextZone"][i]["Width"].asInt(),
                                                        itemUI["TextZone"][i]["ID"].asInt());
            }

            textZone = mOwnerUIO->getItemUIO()->FindText(
                    itemUI["TextZone"][0]["ID"].asInt());
            if (textZone != nullptr)
            {
                textZone->setText(
                        mOwner->getGameSys()->getItemsInInventory()[index]->UseItem().name);
            }
            textZone = mOwnerUIO->getItemUIO()->FindText(
                    itemUI["TextZone"][1]["ID"].asInt());
            if (textZone != nullptr)
            {
                textZone->setText(
                        mOwner->getGameSys()->getItemsInInventory()[index]->UseItem().description);
            }
        }

        mOwnerUIO->TurnOff();
        for (auto item : mOwner->getGameSys()->getItemsInInventory())
        {
            item->SetIsVisibleInventory(false);
        }
        for (auto doc : mOwner->getGameSys()->getDocsInInventory())
        {
            doc->SetIsVisibleInventory(false);
        }
    }
}

// 6: 阅读文档
void ButtonEventComponent::ClickBtn_ReadDoc()
{
    glm::vec2 clickPos = mOwnerUIO->getUIIC()->getMouseClickPos();
    int index = GetClickDocIndex(clickPos);
    Json::Value docUI = mOwner->getGameSys()->GetInitObjRoot()["UIObjects"]["ReadDocUI"];
    TextZone *textZone;

    SDL_Log("read doc witch index is: %d", index);
    if (index + 1 > mOwner->getGameSys()->getDocsInInventory().size())
    {
        SDL_Log("You don't have doc here");
    } else
    {
        if (mOwnerUIO->hasDocUIO())
        {
            mOwnerUIO->getDocUIO()->TurnOn();

            textZone = mOwnerUIO->getDocUIO()->FindText(
                    docUI["TextZone"][0]["ID"].asInt());
            if (textZone != nullptr)
            {
                // 设置标题
                textZone->setText(
                        mOwner->getGameSys()->getDocsInInventory()[index]->ReadDoc().title);
            }
            textZone = mOwnerUIO->getDocUIO()->FindText(
                    docUI["TextZone"][1]["ID"].asInt());
            if (textZone != nullptr)
            {
                // 设置正文
                textZone->setText(
                        mOwner->getGameSys()->getDocsInInventory()[index]->ReadDoc().mainText);
            }
        } else
        {
            mOwnerUIO->setHasDocUIO(true);

            mOwnerUIO->setDocUIO(
                    new UIObject(mOwner->getGameSys(), docUI["UITexPath"].asString()));
            mOwnerUIO->getDocUIO()->setParentUIO(mOwnerUIO);
            for (int i = 0; i < docUI["Button"].size(); ++i)
            {
                mOwnerUIO->getDocUIO()->CreateButton(mOwner->getGameSys(),
                                                     mOwnerUIO->getDocUIO(),
                                                     docUI["Button"][i]["TexPath"].asString(),
                                                     docUI["Button"][i]["Type"].asInt(),
                                                     docUI["Button"][i]["Text"].asString(),
                                                     {docUI["Button"][i]["Position"][0].asFloat(),
                                                      docUI["Button"][i]["Position"][1].asFloat()},
                                                     docUI["Button"][i]["Function"].asInt());
            }
            for (int i = 0; i < docUI["TextZone"].size(); ++i)
            {
                mOwnerUIO->getDocUIO()->CreateTextZone(mOwner->getGameSys(),
                                                       mOwnerUIO->getDocUIO(),
                                                       {docUI["TextZone"][i]["Position"][0].asFloat(),
                                                        docUI["TextZone"][i]["Position"][1].asFloat()},
                                                       docUI["TextZone"][i]["Width"].asInt(),
                                                       docUI["TextZone"][i]["ID"].asInt());
            }

            textZone = mOwnerUIO->getDocUIO()->FindText(
                    docUI["TextZone"][0]["ID"].asInt());
            if (textZone != nullptr)
            {
                // 设置标题
                textZone->setText(
                        mOwner->getGameSys()->getDocsInInventory()[index]->ReadDoc().title);
            }
            textZone = mOwnerUIO->getDocUIO()->FindText(
                    docUI["TextZone"][1]["ID"].asInt());
            if (textZone != nullptr)
            {
                // 设置正文
                textZone->setText(
                        mOwner->getGameSys()->getDocsInInventory()[index]->ReadDoc().mainText);
            }
        }

        mOwnerUIO->TurnOff();
        for (auto item : mOwner->getGameSys()->getItemsInInventory())
        {
            item->SetIsVisibleInventory(false);
        }
        for (auto doc : mOwner->getGameSys()->getDocsInInventory())
        {
            doc->SetIsVisibleInventory(false);
        }
    }
}

// 7: 使用道具
void ButtonEventComponent::ClickBtn_UseItem()
{
    mOwner->getGameSys()->UseItemInUI(
            mOwner->getGameSys()->getItemsInInventory()[mOwnerUIO->getIndex()]->UseItem().ID);
}
