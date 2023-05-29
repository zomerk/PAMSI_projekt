#include <SFML/Graphics.hpp>
#include <cmath>

int main()
{
    // Ustawienia okna
    sf::RenderWindow window(sf::VideoMode(800, 600), "Odbijająca się kulka");
    window.setFramerateLimit(60);

    // Ustawienia kulki
    sf::CircleShape ball(20);
    ball.setFillColor(sf::Color::Red);
    sf::Vector2f position(100, 100);
    sf::Vector2f velocity(0, 0);
    float gravity = 0.2;
    bool isDragging = false;
    sf::Vector2f dragOffset;

    // Główna pętla programu
    while (window.isOpen())
    {
        // Obsługa zdarzeń
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                if (ball.getGlobalBounds().contains(mousePosition))
                {
                    isDragging = true;
                    dragOffset = position - mousePosition;
                }
            }
            else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
            {
                isDragging = false;
            }
        }

        // Aktualizacja pozycji kulki
        if (isDragging)
        {
            sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            position = mousePosition + dragOffset;
            velocity = sf::Vector2f(0, 0); // Zatrzymaj kulę podczas przeciągania
        }
        else
        {
            velocity.y += gravity;
            position += velocity;

            // Odbicie od ścian okna
            if (position.x < 0 || position.x > 750)//window.getSize().x)
                velocity.x = -velocity.x;
            if (position.y > window.getSize().y)
            {
                position.y = window.getSize().y;
                velocity.y = -velocity.y;
                velocity.y *= 0.8; // Wytracanie prędkości
            }
        }

        // Rysowanie kulki na ekranie
        window.clear();
        ball.setPosition(position);
        window.draw(ball);
        window.display();
    }

    return 0;
}