#include <SFML/Graphics.hpp>
#include <cmath>

int main()
{
    // Ustawienia okna
    sf::RenderWindow window(sf::VideoMode(800, 600), "Odbijajaca sie kulka po paraboli");
    window.setFramerateLimit(60);

    // Ustawienia kulki
    sf::CircleShape ball(10);
    ball.setFillColor(sf::Color::Red);
    sf::Vector2f position(100, 100);
    sf::Vector2f velocity(5, -5);
    float gravity = 0.2;

    // Główna pętla programu
    while (window.isOpen())
    {
        // Obsługa zdarzeń
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Aktualizacja pozycji kulki
        velocity.y += gravity;
        position += velocity;

        // Odbicie od ścian okna
        if (position.x < 0 || position.x > window.getSize().x)
            velocity.x = -velocity.x;
        if (position.y > window.getSize().y)
        {
            position.y = window.getSize().y;
            velocity.y = -velocity.y;
            velocity.y *= 0.8; // Wytracanie prędkości
        }

        // Rysowanie kulki na ekranie
        window.clear();
        ball.setPosition(position);
        window.draw(ball);
        window.display();
    }

    return 0;
}
