//
// Created by 蔡元涵 on 2020/6/22.
//

#ifndef SEMI_DEMO_ZONESWITCHHOUSECOMPONENT_H
#define SEMI_DEMO_ZONESWITCHHOUSECOMPONENT_H

#include "Component.h"
#include <glm.hpp>

class ZoneSwitchHouseComponent : public Component
{
public:
    ZoneSwitchHouseComponent(class Object *owner, class Player *player,
                             class House *house,
                             int updateOrder = 10);

    ZoneSwitchHouseComponent(class Object *owner, class Player *player,
                             class BorderDecider *borderDecider,
                             int updateOrder = 10);

    void Update(float deltatime) override;

private:
    class Player *mPlayer;

    class House *mHouse;

    class BorderDecider *mBorderDecider;
};


#endif //SEMI_DEMO_ZONESWITCHHOUSECOMPONENT_H
