#include <SFML/Graphics.hpp>
#include <vector>

const int width = 800;
const int height = 600;

sf::VideoMode vm(width, height);
sf::RenderWindow window(vm, "Paint Application By IF");

std::vector<sf::CircleShape> circles;
std::vector<sf::CircleShape>::iterator iter;

void add(sf::CircleShape shape)
{
    circles.push_back(shape);
}

void update()
{
    iter = circles.begin();

    while (iter != circles.end())
    {
        window.draw(*iter);
        iter++;
    }
}

void erase(sf::Vector2i mousePosition)
{
    iter = circles.begin();

    while (iter != circles.end())
    {
        sf::Vector2f circlePosition = (*iter).getPosition();
        sf::Vector2f circleSize = (*iter).getScale();
        float radius = (*iter).getRadius();

        float left = circlePosition.x - radius;
        float right = circlePosition.x + radius;
        float top = circlePosition.y - radius;
        float bottom = circlePosition.y + radius;

        if (mousePosition.x >= left && mousePosition.x <= right && mousePosition.y >= top && mousePosition.y <= bottom)
        {
            iter = circles.erase(iter);
        }
        else
        {
            iter++;
        }
    }
}

int main()
{
    sf::View view(sf::FloatRect(0, 0, width, height));
    window.setView(view);

    while (window.isOpen() && !sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            else if (event.type == sf::Event::Resized)
            {
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));
            }
        }

        float x, y;

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            x = sf::Mouse::getPosition(window).x;
            y = sf::Mouse::getPosition(window).y;

            sf::CircleShape point(5);
            point.setPosition(x, y);
            point.setFillColor(sf::Color::White);
            add(point);
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
        {
            x = sf::Mouse::getPosition(window).x;
            y = sf::Mouse::getPosition(window).y;

            sf::CircleShape point(20);
            point.setPosition(x, y);
            point.setFillColor(sf::Color::Black);
            add(point);

            if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
            {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                erase(mousePosition);
            }
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Middle))
        {
            circles.clear();

            if (sf::Mouse::isButtonPressed(sf::Mouse::Middle))
            {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                erase(mousePosition);
            }
        }

        window.clear();
        update();
        window.display();
    }

    return 0;

}
