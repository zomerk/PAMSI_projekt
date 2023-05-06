//
// Created by zomer on 02/05/2023.
//

#include "Object.h"
Object::Object(float x, float y, float radius, sf::Color color){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> distr(0.5, 1);
    float  random_number1 = distr(gen);
    float  random_number2 = distr(gen);
    //std::cout << random_number1 <<" "<<  random_number2 << std::endl ;
    this->movement.x = random_number1;
    this->movement.y = random_number2;
    this->setRadius(radius);
    this->setPosition(x,y);
    this->setFillColor(color);
}

void Object::movement_funtion(){
    this->move(this->movement);
    sf::Vector2<float> rozmiar = this->getPosition();
    if (rozmiar.y>= HEIGHT - 2*this->getRadius()) {
        this->movement.y *= -1;
    }
    if (rozmiar.y<= 0) {
        this->movement.y *= -1;
    }
    if (rozmiar.x + 2 * this->getRadius() >= WIDTH) {
        this->movement.x *= -1;
    }
    if (rozmiar.x <= 0) {
        this->movement.x *= -1;
    }
}
void Object::setMovement(sf::Vector2f NewMovement) {
    this->movement = NewMovement;
}
sf::Vector2f Object::getMovemetn(){
    return this->movement;
}

