//
// Created by 蔡元涵 on 2020/6/3.
//

#include "Player.h"
#include "GameSys.h"
#include "SpriteComponent.h"
#include "InputComponent.h"

Player::Player(GameSys *gameSys) : Actor(gameSys)
{
//    setScale(0.125f / 2.0f);
//    setScale(20.f);
    SpriteComponent *sc = new SpriteComponent(this, 150);
    sc->SetTexture(
            gameSys->GetTexture("../Assets/man_1.png"));

    InputComponent *ic = new InputComponent(this);
    ic->setForwardKey(SDL_SCANCODE_W);
    ic->setBackKey(SDL_SCANCODE_S);
    ic->setLeftKey(SDL_SCANCODE_A);
    ic->setRightKey(SDL_SCANCODE_D);
    ic->setHorMoveSpeed(300.0f);
    ic->setVerMoveSpeed(300.0f);
}
