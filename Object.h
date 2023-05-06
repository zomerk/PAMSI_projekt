//
// Created by zomer on 02/05/2023.
//

#ifndef PAMSI_PROJEKT_OBJECT_H
#define PAMSI_PROJEKT_OBJECT_H
#include <iostream>
#include <random>
#include <ctime>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <SFML/Audio.hpp>
#define HEIGHT 2100
#define WIDTH 3400

class Object: public sf::CircleShape {
private:
    sf::Vector2f movement;
public:
    Object(float x, float y, float radius, sf::Color color);
    void movement_funtion();
    sf::Vector2f getMovemetn();
    void setMovement(sf::Vector2f NewMovwement);
};


#endif //PAMSI_PROJEKT_OBJECT_H
