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
}

int Inventory::UseItem(class Item *item)
{
    return item->UseItem();
}

void Inventory::AddDocument(class Document *document)
{
    mDocuments.emplace_back(document);
}

DocInner Inventory::ReadDocument(class Document *document)
{
    return document->ReadDoc();
}

void Inventory::RefreshItems()
{
    //TODO 完成道具事件系统后完善
}
