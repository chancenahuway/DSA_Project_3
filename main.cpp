//
// This program was written by Samson Carter, Dylan Dixon, and Chance Nahuway.
//

#include <SFML/Graphics.hpp>
#include "Maze.h"
using namespace std;

void SFML_test_function() {
    sf::RenderWindow window(sf::VideoMode(640, 480), "SFML Application");
    sf::CircleShape shape;
    shape.setRadius(40.f);
    shape.setPosition(100.f, 100.f);
    shape.setFillColor(sf::Color::Cyan);

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }
}

int main() {
    Maze current = Maze(100, 1);
    SFML_test_function();
    return 0;
}
