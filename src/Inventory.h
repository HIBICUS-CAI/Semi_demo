//
// Created by 蔡元涵 on 2020/7/22.
//

#ifndef SEMI_DEMO_INVENTORY_H
#define SEMI_DEMO_INVENTORY_H

#include <vector>
#include "Item.h"
#include "Document.h"

class Inventory
{
public:
    Inventory();

    const std::vector<class Item *> &getItems() const
    {
        return mItems;
    }

    const std::vector<class Document *> &getDocuments() const
    {
        return mDocuments;
    }

    void AddItem(class Item *item);

    int UseItem(class Item *item);

    void AddDocument(class Document *document);

    DocInner ReadDocument(class Document *document);

//    void RefreshItems();

private:
    std::vector<class Item *> mItems;
    std::vector<class Document *> mDocuments;
};


#endif //SEMI_DEMO_INVENTORY_H
