#include <SFML/Graphics.hpp>
#include <cmath>

const float PI = 3.14159265f;
const float maxDeflectionAngle = PI / 6.0f;  // Maksymalny kąt odkształcenia w radianach
const float frictionFactor = 0.001f;         // Współczynnik tarcia dla ruchu sznura
const float tensionFactor = 0.002f;          // Współczynnik naprężenia dla ruchu sznura
const float restoringForce = 0.03f;          // Siła powodująca powrot do pozycji początkowej sznura

float clamp(float value, float min, float max)
{
    if (value < min)
        return min;
    else if (value > max)
        return max;
    else
        return value;
}

int main()
{

    sf::RenderWindow window(sf::VideoMode(800, 600), "Deflecting Rope");

    // Definicja ilosci segmentów sznura
    const int numSegments = 20;
    const int numNodes = numSegments + 1;

    // Definicja "nodes"
    sf::CircleShape nodes[numNodes];
    sf::Vector2f originalPositions[numNodes];
    bool isNodeNearLimit[numNodes] = { false };  // Sprawdza czy node nie osiągnął limitu odkształcenia
    sf::Color nodeColor = sf::Color::Red;       // Kolor node'a
    sf::Color rodeColor = sf::Color::Green;      // Kolor rode'a

    for (int i = 0; i < numNodes; ++i)
    {
        nodes[i].setRadius(10.f);
        nodes[i].setFillColor(nodeColor);
        nodes[i].setOrigin(nodes[i].getRadius(), nodes[i].getRadius());
        nodes[i].setPosition(window.getSize().x / 2.f - 200.f + i * 20.f, window.getSize().y / 2.f);
        originalPositions[i] = nodes[i].getPosition();
    }

    // definicja rode'ów
    sf::VertexArray rodes(sf::Lines, numSegments * 2);
    for (int i = 0; i < numSegments; ++i)
    {
        rodes[i * 2].color = rodeColor;
        rodes[i * 2 + 1].color = rodeColor;
    }

    // Definicja obciążenia
    sf::CircleShape object(20.f);
    object.setFillColor(sf::Color::Blue);
    object.setOrigin(object.getRadius(), object.getRadius());
    object.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f - 200.f);

    // Promień polizji
    float collisionRadius = 30.f;

    // Współczynnik odkształcenia
    const float deflectionFactor = 0.01f;

    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

   
        sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition(window));
        object.setPosition(mousePosition);


        int numNodesToAffect = std::round(object.getRadius() / 10.f); 

        // Kolizja pomiędzy obiektem a nodem
        for (int i = 1; i < numNodes - 1; ++i)
        {
            sf::Vector2f nodeToObject = object.getPosition() - nodes[i].getPosition();
            float distance = std::sqrt(nodeToObject.x * nodeToObject.x + nodeToObject.y * nodeToObject.y);
            if (distance <= collisionRadius)
            {
                // Liczenie kąta odkształcenia na podstawie odległości
                float deflectionAngle = deflectionFactor * std::sin((PI / 2.f) * (distance / collisionRadius));

                // kierunek odkształcenia na podstawie pozycji obciążenia
                if (nodeToObject.y < 0)
                    deflectionAngle *= -1.f;

                // Clampowanie kąta odkształcenia z maksymalnym odkształceniem
                deflectionAngle = clamp(deflectionAngle, -maxDeflectionAngle, maxDeflectionAngle);

                // Wektor odkształcenia
                sf::Vector2f deflectionVector = sf::Vector2f(-nodeToObject.y, nodeToObject.x);
                deflectionVector = deflectionVector / std::sqrt(deflectionVector.x * deflectionVector.x + deflectionVector.y * deflectionVector.y);
                deflectionVector *= deflectionAngle * collisionRadius;

                // dodanie naprężenia i tarcia
                deflectionVector *= (1.0f - frictionFactor);
                deflectionVector += (nodes[i].getPosition() - nodes[i - 1].getPosition()) * tensionFactor;
                deflectionVector -= (nodes[i].getPosition() - nodes[i + 1].getPosition()) * tensionFactor;

                // Aktualizacja pozycji
                nodes[i].setPosition(nodes[i].getPosition() + deflectionVector);

                // Przypisanie pozycji do przeciwległego node'a
                if (i > 1)
                    nodes[i - 1].setPosition(nodes[i - 1].getPosition() + deflectionVector * 0.5f);
                if (i < numNodes - 2)
                    nodes[i + 1].setPosition(nodes[i + 1].getPosition() + deflectionVector * 0.5f);

                // sprawddza, czy node jest na granicy i zmienia jego kolor
                float nodeDeflection = std::abs(deflectionAngle);
                if (nodeDeflection >= maxDeflectionAngle * 0.9f)
                {
                    isNodeNearLimit[i] = true;
                    nodes[i].setFillColor(sf::Color::White);
                    rodes[(i - 1) * 2].color = sf::Color::White;
                    rodes[(i - 1) * 2 + 1].color = sf::Color::White;
                }
                else if (isNodeNearLimit[i])
                {
                    isNodeNearLimit[i] = false;
                    nodes[i].setFillColor(nodeColor);
                    rodes[(i - 1) * 2].color = rodeColor;
                    rodes[(i - 1) * 2 + 1].color = rodeColor;
                }
            }
            else
            {
                // Przyłożenie siły sprężystości któ©a sprawia że node wraca na miejsce
                sf::Vector2f restoringVector = originalPositions[i] - nodes[i].getPosition();
                nodes[i].setPosition(nodes[i].getPosition() + restoringVector * restoringForce);

                if (isNodeNearLimit[i])
                {
                    isNodeNearLimit[i] = false;
                    nodes[i].setFillColor(nodeColor);
                    rodes[(i - 1) * 2].color = rodeColor;
                    rodes[(i - 1) * 2 + 1].color = rodeColor;
                }
            }
        }

      
        for (int i = 0; i < numSegments; ++i)
        {
            rodes[i * 2].position = nodes[i].getPosition();
            rodes[i * 2 + 1].position = nodes[i + 1].getPosition();
        }

        
        window.clear(sf::Color::Black);
 
        window.draw(rodes);

        for (int i = 0; i < numNodes; ++i)
        {
            window.draw(nodes[i]);
        }

        window.draw(object);

        window.display();
    }

    return 0;
}
