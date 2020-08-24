//
// Created by 蔡元涵 on 2020/6/5.
//

#include "InputComponent.h"
#include "Object.h"
#include "Player.h"
#include "Item.h"
#include "Document.h"
#include "NPCSys.h"
#include "NPChara.h"

InputComponent::InputComponent(class Object *owner, class Player *player) : MoveComponent(
        owner), mForwardKey(0), mBackKey(0), mLeftKey(0), mRightKey(0), mTalkKey(0),
                                                                            mPlayer(player)
{
    // 调试用部分开始
    mIsPrinting = false;
    // 调试用部分结束
}

void InputComponent::ProcessInput(const uint8_t *keyState)
{
    // 调试用部分开始

    if (keyState[mDebugKey] && !mIsPrinting)
    {
        mIsPrinting = true;

        std::vector<class Item *> items = mPlayer->getInventory()->getItems();
        std::vector<class Document *> documents = mPlayer->getInventory()->getDocuments();

//        SDL_Log("in this player's inventory, there are some items and docs those id: ");

        if (!items.empty())
        {
            for (auto item : items)
            {
                SDL_Log("item's ID: %d  ", item->UseItem().ID);
            }
        } else
        {
//            SDL_Log("none item here stupid");
        }
        if (!documents.empty())
        {
            for (auto document : documents)
            {
//                SDL_Log("doc's ID: %d  ", document->ReadDoc().ID);
            }
        } else
        {
//            SDL_Log("none doc here stupid");
        }
    }

    if (keyState[mCancelDebugKey] && mIsPrinting)
    {
        SDL_Log("ready for next debug");
        mIsPrinting = false;
    }

    // 调试用部分结束

    if (keyState[mTalkKey])
    {
        if (!mOwner->getGameSys()->getNPCharas()[0]->getNPCSys()->isTalking())
        {
            SDL_Log("rdy to talk");
            mOwner->getGameSys()->getNPCharas()[0]->getNPCSys()->setIsTalking(true);
            for (int i = 0; i < mOwner->getGameSys()->getNPCharas().size(); ++i)
            {
                if (mOwner->getGameSys()->getNPCharas()[i]->isPlayerTrigged())
                {
                    mOwner->getGameSys()->getNPCharas()[i]->TalkWithPlayer();
                    break;
                }
            }
        }
    }

    float horSpeed = 0.0f;
    if (keyState[mRightKey])
    {
        horSpeed = mHorMoveSpeed;
    }
    if (keyState[mLeftKey])
    {
        horSpeed = -mHorMoveSpeed;
    }

    float verSpeed = 0.0f;
    if (keyState[mForwardKey])
    {
        verSpeed = mVerMoveSpeed;
    }
    if (keyState[mBackKey])
    {
        verSpeed = -mVerMoveSpeed;
    }

    if ((keyState[mForwardKey] && keyState[mRightKey]) ||
        (keyState[mForwardKey] && keyState[mLeftKey]) ||
        (keyState[mBackKey] && keyState[mRightKey]) ||
        (keyState[mBackKey] && keyState[mLeftKey]))
    {
        verSpeed /= 1.414f;
        horSpeed /= 1.414f;
    }

    if (keyState[mForwardKey] && keyState[mBackKey])
    {
        verSpeed = 0.f;
        horSpeed = 0.f;
    }
    if (keyState[mLeftKey] && keyState[mRightKey])
    {
        verSpeed = 0.f;
        horSpeed = 0.f;
    }

    if (keyState[mForwardKey] && !keyState[mRightKey] &&
        !keyState[mBackKey] && !keyState[mLeftKey])
    {
        mPlayer->setInputStatus(1);
    } else if (!keyState[mForwardKey] && keyState[mRightKey] &&
               !keyState[mBackKey] && !keyState[mLeftKey])
    {
        mPlayer->setInputStatus(2);
    } else if (!keyState[mForwardKey] && !keyState[mRightKey] &&
               keyState[mBackKey] && !keyState[mLeftKey])
    {
        mPlayer->setInputStatus(3);
    } else if (!keyState[mForwardKey] && !keyState[mRightKey] &&
               !keyState[mBackKey] && keyState[mLeftKey])
    {
        mPlayer->setInputStatus(4);
    } else if (keyState[mForwardKey] && keyState[mRightKey] &&
               !keyState[mBackKey] && !keyState[mLeftKey])
    {
        mPlayer->setInputStatus(5);
    } else if (!keyState[mForwardKey] && keyState[mRightKey] &&
               keyState[mBackKey] && !keyState[mLeftKey])
    {
        mPlayer->setInputStatus(6);
    } else if (!keyState[mForwardKey] && !keyState[mRightKey] &&
               keyState[mBackKey] && keyState[mLeftKey])
    {
        mPlayer->setInputStatus(7);
    } else if (keyState[mForwardKey] && !keyState[mRightKey] &&
               !keyState[mBackKey] && keyState[mLeftKey])
    {
        mPlayer->setInputStatus(8);
    } else
    {
        mPlayer->setInputStatus(0);
    }

    setHorizontalSpeed(horSpeed);
    setVerticalSpeed(verSpeed);

}
