#pragma once
#include <vector>
#include <queue>
#include <set>
#include <map>
#include "SFML/Graphics.hpp"
#include "TextureManager.h"
using namespace std;

class Maze {
private:
    struct Tile {
        vector<Tile*> connectedTiles;
        vector<Tile*> adjacentTiles;
        int x, y;
        sf::Sprite sprite;
        sf::Sprite visiting;
        sf::Sprite path;

        Tile(int x, int y): x(x), y(y) {
            sprite.setTexture(TextureManager::GetTexture("square-white"));
            sprite.setPosition((x * 15) + 50, (y * 15) + 20); //adjust to match sprite size/grid size
            visiting.setTexture(TextureManager::GetTexture("square-red"));
            visiting.setPosition((x * 15) + 50, (y * 15) + 20);
            path.setTexture(TextureManager::GetTexture("square-blue"));
            path.setPosition((x * 15) + 50, (y * 15) + 20);


        };
    };

    int sideLength;
    int numTiles;
    int mazeType;
    vector<Tile*> tiles;

    void codifyAdjacencyInfo();
    void generateGrowingTree(int flavor);

public:
    Maze(int sideLength, int mazeType);
    ~Maze();
    vector<pair<int, int>> dijkstraAlgorithm(sf::RenderWindow& window);
    vector<pair<int, int>> depthFirstSearch(sf::RenderWindow& window);
    void displayMaze();
    vector<Tile*>& getAllTiles();
    int getSideLength() const { return sideLength; }
    void drawLines(sf::RenderWindow& window);
    void drawAndUpdate(sf::RenderWindow& window);

};
