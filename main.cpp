#include "Maze.h"
#include "TextureManager.h"
#include <iostream>
using namespace std;

int main() {
    Maze maze(50, 1);
    maze.displayMaze();
    cout << "\nFinding path through the maze:\n";

    int windowSize = maze.getSideLength() * 15;
    sf::RenderWindow window(sf::VideoMode(windowSize + 100, windowSize + 100), "SFML Window");

    vector<pair<int, int>> path = maze.BFS(window);

    // Event loop to keep window open after BFS is complete
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
    }

    return 0;
}
