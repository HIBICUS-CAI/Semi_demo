//
// Created by 蔡元涵 on 2020/6/3.
//

#include "Player.h"
#include "GameSys.h"
#include "Item.h"
#include "Document.h"
#include "Inventory.h"
#include "SpriteComponent.h"
#include "InputComponent.h"
#include "CollisionComponent.h"

Player::Player(GameSys *gameSys) : Object(gameSys), mCC(nullptr), mInputStatus(0)
{
    //设置初始地图块
    int initX = getGameSys()->GetInitObjRoot()["Maps"]["StartMapPos"][0].asInt();
    int initY = getGameSys()->GetInitObjRoot()["Maps"]["StartMapPos"][1].asInt();
    setMapPositon(initX, initY);
    gameSys->setInitPos({initX, initY});

    SpriteComponent *sc = new SpriteComponent(this, 150);
    sc->SetTexture(
            gameSys->GetTexture(gameSys->GetInitObjRoot()["Player"]["Tex"].asString()));

    InputComponent *ic = new InputComponent(this, this);
    ic->setTalkKey(SDL_SCANCODE_C);
    ic->setForwardKey(SDL_SCANCODE_W);
    ic->setBackKey(SDL_SCANCODE_S);
    ic->setLeftKey(SDL_SCANCODE_A);
    ic->setRightKey(SDL_SCANCODE_D);
    ic->setDebugKey(SDL_SCANCODE_F);
    ic->setCancelDebugKey(SDL_SCANCODE_R);
    ic->setHorMoveSpeed(gameSys->GetInitObjRoot()["Player"]["MoveSpeed"].asFloat());
    ic->setVerMoveSpeed(gameSys->GetInitObjRoot()["Player"]["MoveSpeed"].asFloat());

    mCC = new CollisionComponent(this);
    mCC->setRadius(10.f);

    mInventory = new Inventory();
}

void Player::RevertMove()
{
    switch (mInputStatus)
    {
        case 1:
            setPosition({getPosition().x, getPosition().y - 5.f});
            break;
        case 2:
            setPosition({getPosition().x - 5.f, getPosition().y});
            break;
        case 3:
            setPosition({getPosition().x, getPosition().y + 5.f});
            break;
        case 4:
            setPosition({getPosition().x + 5.f, getPosition().y});
            break;
        case 5:
            setPosition({getPosition().x - 5.f / 1.414f, getPosition().y - 5.f / 1.414f});
            break;
        case 6:
            setPosition({getPosition().x - 5.f / 1.414f, getPosition().y + 5.f / 1.414f});
            break;
        case 7:
            setPosition({getPosition().x + 5.f / 1.414f, getPosition().y + 5.f / 1.414f});
            break;
        case 8:
            setPosition({getPosition().x + 5.f / 1.414f, getPosition().y - 5.f / 1.414f});
            break;
        default:
            break;
    }
}

void Player::AddItemToInventory(class Item *item)
{
    SDL_Log("add a item to inventory witch id is: %d", item->UseItem().ID);
    mInventory->AddItem(item);
    AddItemToRecord(item->UseItem().ID);
}

void Player::AddDocToInventory(class Document *document)
{
    SDL_Log("add a doc to inventory witch id is: %d", document->ReadDoc().ID);
    mInventory->AddDocument(document);
    AddDocToRecord(document->ReadDoc().ID);
}

void Player::AddItemToRecord(int itemID)
{
    if (!Tools::CheckMemberExistInt(itemID, mGotItems))
    {
        mGotItems.emplace_back(itemID);
    }
}

void Player::AddDocToRecord(int docID)
{
    if (!Tools::CheckMemberExistInt(docID, mGotDocuments))
    {
        mGotDocuments.emplace_back(docID);
    }
}

void Player::AddGearToRecord(int gearID)
{
    if (!Tools::CheckMemberExistInt(gearID, mUnlockedGears))
    {
        mUnlockedGears.emplace_back(gearID);
    }
}

void Player::AddNPCToRecord(int npcID)
{
    if (!Tools::CheckMemberExistInt(npcID, mTalkedNPCs))
    {
        mTalkedNPCs.emplace_back(npcID);
    }
}
