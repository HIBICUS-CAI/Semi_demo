//
// Created by 蔡元涵 on 2020/6/16.
//

#ifndef SEMI_DEMO_ZONESWITCHMAPCOMPONENT_H
#define SEMI_DEMO_ZONESWITCHMAPCOMPONENT_H

#include "Component.h"
#include <glm.hpp>

class ZoneSwitchMapComponent : public Component
{
public:
    ZoneSwitchMapComponent(class Actor *owner, class Player *player,
                           class SingleMap *singleMap,
                           int updateOrder = 10);

    void Update(float deltatime) override;

private:
    class Player *mPlayer;

    class SingleMap *mSingleMap;
};


#endif //SEMI_DEMO_ZONESWITCHMAPCOMPONENT_H
