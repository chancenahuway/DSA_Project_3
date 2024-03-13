//
// This program was written by Samson Carter, Dylan Dixon, and Chance Nahuway.
//

#pragma once
#include <vector>
using namespace std;

// Types of mazes:
// Type 1: Growing Tree Algorithm

class Maze {

private:

    // Nested Tile struct
    struct Tile {
        // Tile member variables
        vector<Tile*> adjacent_tiles;
        vector<Tile*> connected_tiles;
        int x;
        int y;

        // Tile member functions


        // Tile constructor
        Tile(int x, int y);
    };

    // Maze member variables
    int side_length;
    int num_tiles;
    int maze_type;
    vector<Tile*> tiles;

    // Maze member functions
    void codify_adjacency_info();
    void generate_growing_tree(int flavor);
    void mouse_press_left(int x, int y);
    void draw_maze(sf::RenderWindow& window);

public:

    // Maze Constructor
    Maze(int side_length, int maze_type);
};
