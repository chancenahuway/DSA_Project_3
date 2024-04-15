#pragma once
#include <vector>
#include <queue>
#include <set>
#include <map>
using namespace std;

class Maze {
private:
    struct Tile {
        vector<Tile*> connected_tiles;
        vector<Tile*> adjacent_tiles;
        int x, y;
        Tile(int x, int y);
    };

    int side_length;
    int num_tiles;
    int maze_type;
    vector<Tile*> tiles;

    void codify_adjacency_info();
    void generate_growing_tree(int flavor);

public:
    Maze(int side_length, int maze_type);
    vector<pair<int, int>> BFS();
    void displayMaze();
};
