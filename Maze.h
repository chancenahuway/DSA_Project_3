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
        vector<Tile*> connected_tiles;
        vector<Tile*> adjacent_tiles;
        int x, y;
        sf::Sprite sprite;

        Tile(int x, int y): x(x), y(y) {
            sprite.setTexture(TextureManager::GetTexture("square-white"));
            sprite.setPosition((x * 15) + 50, (y * 15) + 20); //adjust to match sprite size/grid size
        };
    };

    int side_length;
    int num_tiles;
    int maze_type;
    vector<Tile*> tiles;

    void codify_adjacency_info();
    void generate_growing_tree(int flavor);

public:
    Maze(int side_length, int maze_type);
    ~Maze();
    vector<pair<int, int>> BFS();
    void displayMaze();
    vector<Tile*>& getAllTiles();
    int getSideLength() const { return side_length; }
    void drawLines(sf::RenderWindow& window);

};
