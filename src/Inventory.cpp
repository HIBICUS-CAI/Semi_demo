//
// Created by 蔡元涵 on 2020/7/22.
//

#include "Inventory.h"

Inventory::Inventory()
{
    mItems.clear();
}

void Inventory::AddItem(class Item *item)
{
    mItems.emplace_back(item);

    switch (mItems.size())
    {
        case 1:
            item->setPosition({-360.f, 150.f});
            break;
        case 2:
            item->setPosition({-260.f, 150.f});
            break;
        case 3:
            item->setPosition({-160.f, 150.f});
            break;
        case 4:
            item->setPosition({-60.f, 150.f});
            break;
        case 5:
            item->setPosition({-360.f, 50.f});
            break;
        case 6:
            item->setPosition({-260.f, 50.f});
            break;
        case 7:
            item->setPosition({-160.f, 50.f});
            break;
        case 8:
            item->setPosition({-60.f, 50.f});
            break;
        case 9:
            item->setPosition({-360.f, -50.f});
            break;
        case 10:
            item->setPosition({-260.f, -50.f});
            break;
        case 11:
            item->setPosition({-160.f, -50.f});
            break;
        case 12:
            item->setPosition({-60.f, -50.f});
            break;
        case 13:
            item->setPosition({-360.f, -150.f});
            break;
        case 14:
            item->setPosition({-260.f, -150.f});
            break;
        case 15:
            item->setPosition({-160.f, -150.f});
            break;
        case 16:
            item->setPosition({-60.f, -150.f});
            break;
        default:
            SDL_Log("cannot hold anymore item");
            break;
    }
}

int Inventory::UseItem(class Item *item)
{
    return item->UseItem().ID;
}

void Inventory::AddDocument(class Document *document)
{
    mDocuments.emplace_back(document);

    switch (mDocuments.size())
    {
        case 1:
            document->setPosition({60.f, 150.f});
            break;
        case 2:
            document->setPosition({160.f, 150.f});
            break;
        case 3:
            document->setPosition({260.f, 150.f});
            break;
        case 4:
            document->setPosition({360.f, 150.f});
            break;
        case 5:
            document->setPosition({60.f, 50.f});
            break;
        case 6:
            document->setPosition({160.f, 50.f});
            break;
        case 7:
            document->setPosition({260.f, 50.f});
            break;
        case 8:
            document->setPosition({360.f, 50.f});
            break;
        default:
            SDL_Log("cannot hold anymore doc");
            break;
    }
}

DocInner Inventory::ReadDocument(class Document *document)
{
    return document->ReadDoc();
}

void Inventory::RefreshItems()
{
    //TODO 完成道具事件系统后完善
}
