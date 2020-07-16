//
// Created by 蔡元涵 on 2020/6/30.
//

#ifndef SEMI_DEMO_UIINPUTCOMPONENT_H
#define SEMI_DEMO_UIINPUTCOMPONENT_H

#include "Component.h"

class UIInputComponent : public Component
{
public:
    UIInputComponent(class Object *owner, class UIObject *uiObject, int updateOrder = 10);

    void UIInput(const glm::vec2 mouseClickPos) override;

    void Update(float deltatime) override;

    const glm::vec2 &getMouseClickPos() const
    {
        return mMouseClickPos;
    }

private:
    class UIObject *mUIObject;

    glm::vec2 mMouseClickPos;
};


#endif //SEMI_DEMO_UIINPUTCOMPONENT_H
