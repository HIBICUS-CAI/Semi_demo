//
// Created by 蔡元涵 on 2020/8/14.
//

#ifndef SEMI_DEMO_BUTTONEVENTCOMPONENT_H
#define SEMI_DEMO_BUTTONEVENTCOMPONENT_H

#include "Component.h"

class ButtonEventComponent : public Component
{
public:
    ButtonEventComponent(class Object *owner, class UIObject *uiObject, int updateOrder = 10);

    void PressButton(int func_id);

private:
    void ButtonEvent(int func_id);

    // 1: 开始进行游戏
    void ClickBtn_StartGame();

    // 2: 显示操作介绍界面
    void ClickBtn_GetHelp();

    // 3: 关闭窗口
    void ClickBtn_CloseWnd();

    // 4: 开启物品栏
    void ClickBtn_OpenInventory();

    // 5: 展示道具
    void ClickBtn_ShowItem();

    // 6: 阅读文档
    void ClickBtn_ReadDoc();

    // 7: 使用道具
    void ClickBtn_UseItem();

    class UIObject *mOwnerUIO;
};


#endif //SEMI_DEMO_BUTTONEVENTCOMPONENT_H
