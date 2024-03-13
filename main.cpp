#include <SFML/Graphics.hpp>
#include <iostream>
#include "TextureManager.h"
#include "Maze.h"

using namespace std;

int main()
{

    int width = 600;
    int height = 600;

    Maze maze(100, 1);

    sf::RenderWindow window(sf::VideoMode(width, height), "Maze Masters (What was our Name??)");

    sf::Sprite startButton(TextureManager::GetTexture("start"));
    startButton.setPosition(width/2, 500);

    sf::Sprite showButton(TextureManager::GetTexture("show"));
    showButton.setPosition(width/2, 550);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            else if (event.type == sf::Event::MouseButtonPressed) {

                if (event.mouseButton.button == sf::Mouse::Left) {
                    auto mousePosition = sf::Mouse::getPosition(window);
                    //have the maze account for the click if necessary automatically
                    //maze.mouse_press_left(mousePosition.x, mousePostion.y);}

                    if (startButton.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
                        cout << "1" << endl; //FIXME
                        //maze.start();
                        //starts a timer, and allows players to toggle the color of tiles
                        //DO NOT allow toggle ahead of time!

                    else if (showButton.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
                        cout << "2" << endl; //FIXME
                        //maze.solve();
                        //solve the maze using the selected solving algorithm from a drop down menu

            }
                if (event.mouseButton.button == sf::Mouse::Right) {
                    auto mousePosition = sf::Mouse::getPosition(window);
                    //add info if we need a right button press, but i dont think so
                }

            }

        }

        window.clear(sf::Color::White);

        window.draw(startButton);
        window.draw(showButton);

        //maze.draw_maze(window);
        window.display();
    }

    return 0;
}
