#include <SFML/Graphics.hpp>
#include <cmath>

void odbijanie()
{
    // Ustawienia okna
    sf::RenderWindow window(sf::VideoMode(800, 600), "Odbijajaca sie kulka lecaca po paraboli");
    window.setFramerateLimit(60);

    //tlo
    sf::RectangleShape tlo(sf::Vector2f(800,580));
    tlo.setFillColor(sf::Color::Cyan);
    tlo.setPosition(0,0);

    sf::RectangleShape trawa(sf::Vector2f(800,20));
    trawa.setFillColor(sf::Color::Green);
    trawa.setPosition(0,580);

    sf::CircleShape triangle(15, 3);
    triangle.setFillColor(sf::Color::Green);
    triangle.setPosition(500,570);

    sf::CircleShape triangle2(15, 3);
    triangle2.setFillColor(sf::Color::Green);
    triangle2.setPosition(510,570);

    sf::CircleShape triangle3(15, 3);
    triangle3.setFillColor(sf::Color::Green);
    triangle3.setPosition(520,570);

    sf::CircleShape triangle4(15, 3);
    triangle4.setFillColor(sf::Color::Green);
    triangle4.setPosition(200,570);

    sf::CircleShape triangle5(15, 3);
    triangle5.setFillColor(sf::Color::Green);
    triangle5.setPosition(210,570);

    sf::CircleShape triangle6(15, 3);
    triangle6.setFillColor(sf::Color::Green);
    triangle6.setPosition(220,570);

    sf::CircleShape slonce(80);
    slonce.setFillColor(sf::Color::Yellow);
    slonce.setPosition(60,30);

    sf::CircleShape chmura1(70);
    chmura1.setFillColor(sf::Color::White);
    chmura1.setPosition(550,45);

    sf::CircleShape chmura2(50);
    chmura2.setFillColor(sf::Color::White);
    chmura2.setPosition(500,35);

    sf::CircleShape chmura3(70);
    chmura3.setFillColor(sf::Color::White);
    chmura3.setPosition(400,25);

    sf::CircleShape chmura4(60);
    chmura4.setFillColor(sf::Color::White);
    chmura4.setPosition(350,65);

    sf::CircleShape chmura5(80);
    chmura5.setFillColor(sf::Color::White);
    chmura5.setPosition(430,45);

    // Ustawienia kulki
    sf::CircleShape ball(30);
    ball.setFillColor(sf::Color::Red);
    sf::Vector2f position(100, 100);
    sf::Vector2f velocity(5, -5);
    float gravity = 0.2;
    double poczatek;

     // Flaga wskazująca, czy kulka jest przeciągana
    bool isDragging = false;

    // Punkt początkowy przeciągania
    sf::Vector2f dragStart;

    // Główna pętla programu
    while (window.isOpen())
    {
        // Obsługa zdarzeń
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();



            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    // Sprawdzenie, czy kliknięcie nastąpiło na kulce
                    if (ball.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
                    {
                        isDragging = true;
                       // dragStart = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
                    }
                }
            }

            if (event.type == sf::Event::MouseButtonReleased)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    isDragging = false;
                }
            }
        }

        // Aktualizacja pozycji kulki
         if (isDragging)
        {
            poczatek=sf::Mouse::getPosition(window).x;
            position.x=event.mouseMove.x;
            position.y=event.mouseMove.y;
            ball.setPosition(position);
            sf::Mouse::getPosition(window);
            if(sf::Mouse::getPosition(window).x>poczatek)
            velocity.x=5;
            else if(sf::Mouse::getPosition(window).x<poczatek) 
            velocity.x=-5;
        }

        else
        {
        velocity.y += gravity;
        position += velocity;

        // Odbicie od ścian okna
        if (position.x > 740)
        { 
            velocity.x = -velocity.x;
        }
        if (position.x < 0)
        {
            velocity.x = -velocity.x;
        }
        if (position.y > 530)
        {
            position.y = 530;
            velocity.y = -velocity.y;
            velocity.y *= 0.8; // Wytracanie prędkości
            velocity.x *= 0.9; 
        }
        //if(position.y=540)
        //velocity.x *= 0.8; 
        }

        // Rysowanie kulki na ekranie
        window.clear();
        ball.setPosition(position);
        window.draw(tlo);
        window.draw(trawa);
        window.draw(triangle);
        window.draw(triangle2);
        window.draw(triangle3);
        window.draw(triangle4);
        window.draw(triangle5);
        window.draw(triangle6);
        window.draw(chmura1);
        window.draw(chmura2);
        window.draw(chmura3);
        window.draw(chmura4);
        window.draw(chmura5);
        window.draw(slonce);
        window.draw(ball);
        window.display();
    }
}
