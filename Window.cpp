//
// Created by zomer on 02/05/2023.
//
#include "Window.h"

void Window::EasyColision(Object *elem1, Object *elem2) {
        auto a1 = (*elem1).getMovemetn();
        auto a2 = (*elem2).getMovemetn();
        std::cout << a1.x << " " << a1.y << std::endl;
        std::cout << a2.x << " " << a2.y << std::endl;
        elem1->setMovement(a2);
        elem2->setMovement(a1);
        elem1->movement_funtion();
        elem2->movement_funtion();
}
void Window::Colision(Object *elem1, Object *elem2){
    float m1 = elem1->getRadius();
    float m2 = elem2->getRadius();
    float x1 = elem1->getPosition().x+elem1->getRadius();
    float y1 = elem1->getPosition().y+elem1->getRadius();
    float x2 = elem2->getPosition().x+elem2->getRadius();
    float y2 = elem2->getPosition().y+elem2->getRadius();
    float vx1 = elem1->getMovemetn().x;
    float vy1 = elem1->getMovemetn().y;
    float vx2 = elem2->getMovemetn().x;
    float vy2 = elem2->getMovemetn().y;
    float dx = x2 - x1;
    float dy = y2 - y1;
    float dist = std::sqrt(dx*dx + dy*dy);
    // Calculate the unit normal and tangential vectors
    float nx = dx / dist;
    float ny = dy / dist;
    float tx = -ny;
    float ty = nx;
    // Calculate the velocity components along the normal and tangential vectors
    float v1n = nx * vx1 + ny * vy1;
    float v1t = tx * vx1 + ty * vy1;
    float v2n = nx * vx2 + ny * vy2;
    float v2t = tx * vx2 + ty * vy2;
    // Calculate the new normal velocities after the collision
    float v1n_new = (v1n * (m1 - m2) + 2 * m2 * v2n) / (m1 + m2);
    float v2n_new = (v2n * (m2 - m1) + 2 * m1 * v1n) / (m1 + m2);

    // Calculate the new total velocities after the collision
    float vx1_new = v1n_new * nx + v1t * tx;
    float vy1_new = v1n_new * ny + v1t * ty;
    float vx2_new = v2n_new * nx + v2t * tx;
    float vy2_new = v2n_new * ny + v2t * ty;
    // Update the object velocities
    elem1->setMovement({vx1_new,vy1_new});
    elem2->setMovement({vx2_new,vy2_new});
    elem1->movement_funtion();
    elem2->movement_funtion();

}

int Window::IsTouching(Object *elem1, Object *elem2) {
    auto pos1 = (*elem1).getPosition();
    auto pos2 = (*elem2).getPosition();
    if(pow((pos2.x+(*elem2).getRadius())-(pos1.x+(*elem1).getRadius()),2)+pow((pos2.y+(*elem2).getRadius())-(pos1.y+(*elem1).getRadius()),2)<=pow((*elem1).getRadius()+(*elem2).getRadius(),2))
        return 1;
    return 0;
}
void Window::Action_Loop(int n) {
    float fps;
    sf::Clock clock = sf::Clock();
    sf::Time previousTime = clock.getElapsedTime();
    sf::Time currentTime;
    sf::RenderWindow window(sf::VideoMode(WIDTH,HEIGHT),"MY app");
    float x=0;
    float y=0;
    int z = 0 ;
    for(int i =0;i<n;i++){
        Object* Shape_new = new Object(x,y,10,sf::Color::Red);
        this->Elements.push_back(Shape_new);
        if(x >= WIDTH){
            x = -100;
            z += 100;
        }
        x+=100;
        y=z;
    }
    std::cout << this->Elements.size() << std::endl;
    for(auto a:this->Elements){
        std::cout << a <<std::endl;
    }
    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        for(auto a: Elements){
            (*a).movement_funtion();
        }
        for(auto a:Elements){
            window.draw(*a);
        }
        window.display();
        for(auto a :Elements){
            for(auto b : Elements){
                if(a!=b) {
                    if (IsTouching(a, b)) {
                        //vertlet integration tutaj
                        //EasyColision(a,b);
                        Colision(a,b);
                        window.draw(*a);
                        window.draw(*b);
                    }
                }
            }
        }
        currentTime = clock.getElapsedTime();
        fps = 1.0f / (currentTime.asSeconds() - previousTime.asSeconds()); // the asSeconds returns a float
        std::cout << "fps =" << floor(fps) << std::endl; // flooring it will make the frame rate a rounded number
        previousTime = currentTime;
    }
}