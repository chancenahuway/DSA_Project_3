#include "Maze.h"
#include "TextureManager.h"
#include <iostream>
using namespace std;

int main() {
    Maze maze(50, 1);
    maze.displayMaze();
    cout << "\nFinding path through the maze:\n";
    vector<pair<int, int>> path = maze.BFS();
    for (auto& coord : path) {
        cout << "(" << coord.first << ", " << coord.second << ")" << endl;
    }

    int windowSize = maze.getSideLength() * 15;
    sf::RenderWindow window(sf::VideoMode(windowSize + 100, windowSize + 100), "SFML Window");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);

        for (auto& tile : maze.getAllTiles()) {
            window.draw(tile->sprite);
        }

        maze.drawLines(window); // Draw walls as lines

        window.display();
    }

    return 0;
}
