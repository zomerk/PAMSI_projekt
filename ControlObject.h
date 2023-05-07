//
// Created by zomer on 06/05/2023.
//

#ifndef PAMSI_PROJEKT_CONTROLOBJECT_H
#define PAMSI_PROJEKT_CONTROLOBJECT_H
#include "Object.h"

class ControlObject :public Object {

public:
    ControlObject(float x, float y, float radius,sf::Color color);
    void Control() override;
    void movement_funtion();
};


#endif //PAMSI_PROJEKT_CONTROLOBJECT_H
