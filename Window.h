//
// Created by zomer on 02/05/2023.
//

#ifndef PAMSI_PROJEKT_WINDOW_H
#define PAMSI_PROJEKT_WINDOW_H
#include "Object.h"
#include <list>


class Window: public sf::RenderWindow{
private:
    std::list<Object*> Elements;
public:
    int IsTouching(Object* elem1,Object* elem2);
    void Action_Loop(int n);
    void EasyColision(Object* elem1,Object* elem2);
    static void Colision(Object *elem1, Object *elem2);
};


#endif //PAMSI_PROJEKT_WINDOW_H
