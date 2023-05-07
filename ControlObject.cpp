//
// Created by zomer on 06/05/202-50.
//

#include "ControlObject.h"

ControlObject::ControlObject(float x, float y, float radius,sf::Color color) : Object(x, y, radius, color) {
this->setMovement({0,0});
};
void ControlObject::movement_funtion(){
    this->getMovemetn();
}


void ControlObject::Control() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            setMovement({-5,-5});
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            setMovement({-5,5});
        }
        else{
            setMovement({-5,0});
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            setMovement({5,-5});
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            setMovement({5,5});
        }
        else{
            setMovement({5,0});
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            setMovement({5,-5});
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            setMovement({-5,-5});
        }
        else{
            setMovement({0,-5});
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                setMovement({5,5});
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                setMovement({-5,5});
            }
            else{
                setMovement({0,5});
            }
        }

    }
    else{
        setMovement({0,0});
    }

}