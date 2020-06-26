//
// Created by 蔡元涵 on 2020/6/3.
//

#include "Player.h"
#include "GameSys.h"
#include "SpriteComponent.h"
#include "InputComponent.h"
#include "CollisionComponent.h"

Player::Player(GameSys *gameSys) : Object(gameSys), mCC(nullptr), mInputStatus(0)
{
//    setScale(0.125f / 2.0f);
//    setScale(20.f);
    //设置初始地图块
    int initX = getGameSys()->GetInitObjRoot()["Maps"]["StartMapPos"][0].asInt();
    int initY = getGameSys()->GetInitObjRoot()["Maps"]["StartMapPos"][1].asInt();
    setMapPositon(initX, initY);
    gameSys->setInitPos({initX, initY});

    SpriteComponent *sc = new SpriteComponent(this, 150);
    sc->SetTexture(
            gameSys->GetTexture(gameSys->GetInitObjRoot()["Player"]["Tex"].asString()));

    InputComponent *ic = new InputComponent(this, this);
    ic->setForwardKey(SDL_SCANCODE_W);
    ic->setBackKey(SDL_SCANCODE_S);
    ic->setLeftKey(SDL_SCANCODE_A);
    ic->setRightKey(SDL_SCANCODE_D);
    ic->setHorMoveSpeed(300.0f);
    ic->setVerMoveSpeed(300.0f);

    mCC = new CollisionComponent(this);
    mCC->setRadius(10.f);
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
