//
// This program was written by Samson Carter, Dylan Dixon, and Chance Nahuway.
//

#include <algorithm>
#include <random>
#include <SFML/Graphics.hpp>
#include "Maze.h"
#include <iostream>

using namespace std;

void Maze::codify_adjacency_info() {
    // Populate adjacent_tiles vector for each tile
    for (unsigned int i = 0; i < tiles.size(); i++) {
        // Top left corner tile
        if (i == 0) {
            tiles[i]->adjacent_tiles.push_back(tiles[i + 1]);
            tiles[i]->adjacent_tiles.push_back(tiles[i + side_length]);
        }
        // Top right corner tile
        else if (i == side_length - 1) {
            tiles[i]->adjacent_tiles.push_back(tiles[i - 1]);
            tiles[i]->adjacent_tiles.push_back(tiles[i + side_length]);
        }
        // Bottom left corner tile
        else if (i == tiles.size() - side_length) {
            tiles[i]->adjacent_tiles.push_back(tiles[i + 1]);
            tiles[i]->adjacent_tiles.push_back(tiles[i - side_length]);
        }
        // Bottom right corner tile
        else if (i == tiles.size() - 1) {
            tiles[i]->adjacent_tiles.push_back(tiles[i - 1]);
            tiles[i]->adjacent_tiles.push_back(tiles[i - side_length]);
        }
        // Top exterior tiles
        else if (i < side_length - 1) {
            tiles[i]->adjacent_tiles.push_back(tiles[i - 1]);
            tiles[i]->adjacent_tiles.push_back(tiles[i + 1]);
            tiles[i]->adjacent_tiles.push_back(tiles[i + side_length]);
        }
        // Bottom exterior tiles
        else if (tiles.size() - side_length < i && i < tiles.size()) {
            tiles[i]->adjacent_tiles.push_back(tiles[i - 1]);
            tiles[i]->adjacent_tiles.push_back(tiles[i + 1]);
            tiles[i]->adjacent_tiles.push_back(tiles[i - side_length]);
        }
        // Left exterior tiles
        else if (i % side_length == 0 && i < tiles.size() - side_length) {
            tiles[i]->adjacent_tiles.push_back(tiles[i + 1]);
            tiles[i]->adjacent_tiles.push_back(tiles[i - side_length]);
            tiles[i]->adjacent_tiles.push_back(tiles[i + side_length]);
        }
        // Right exterior tiles
        else if (i % side_length == side_length - 1 && side_length - 1 < i && i < tiles.size() - 1) {
            tiles[i]->adjacent_tiles.push_back(tiles[i - 1]);
            tiles[i]->adjacent_tiles.push_back(tiles[i - side_length]);
            tiles[i]->adjacent_tiles.push_back(tiles[i + side_length]);
        }
        // Interior tiles
        else {
            tiles[i]->adjacent_tiles.push_back(tiles[i - 1]);
            tiles[i]->adjacent_tiles.push_back(tiles[i + 1]);
            tiles[i]->adjacent_tiles.push_back(tiles[i - side_length]);
            tiles[i]->adjacent_tiles.push_back(tiles[i + side_length]);
        }
    }
}

void Maze::generate_growing_tree(int flavor) {
    // Construct a temporary list of tiles, starting with one random tile
    vector<Tile*> temp;
    int random1 = rand() % (this->num_tiles);
    temp.push_back(tiles[random1]);

    // Build maze
    while (!temp.empty()) {
        // Choose a tile from temp
        Tile *active;
        if (flavor == 0) {
            active = temp[temp.size() - 1]; // Recursive Backtracker Algorithm chooses tile most recently added to temp
        }
        else {
            int random2 = rand() % temp.size();
            active = temp[random2]; // Prim's Algorithm chooses random tile from temp
        }
        // Construct a list of active's unconnected adjacent tiles
        vector <Tile*> unconnected_adjacent_tiles;
        for (int i = 0; i < active->adjacent_tiles.size(); i++) {
            if ((active->adjacent_tiles[i]->connected_tiles).empty()) {
                unconnected_adjacent_tiles.push_back(active->adjacent_tiles[i]);
            }
        }
        // If active has no unconnected adjacent tiles, remove active from temp
        if (unconnected_adjacent_tiles.empty()) {
            temp.erase(std::remove(temp.begin(), temp.end(), active), temp.end());
        }
        // Otherwise, connect active and one of its unconnected adjacent tiles to each other, and add that tile to temp
        else {
            int random3 = rand() % unconnected_adjacent_tiles.size();
            active->connected_tiles.push_back(unconnected_adjacent_tiles[random3]);
            unconnected_adjacent_tiles[random3]->connected_tiles.push_back(active);
            temp.push_back(unconnected_adjacent_tiles[random3]);
        }
    }
}

void Maze::mouse_press_left(int x, int y)
{
    cout << "Left Click Position: " << x << ", " << y << endl;
    //if tile is selected, toggle path color
}

void Maze::draw_maze(sf::RenderWindow& window)
{

}
Maze::Tile::Tile(int x, int y) {
    this->x = x;
    this->y = y;
}

Maze::Maze(int side_length, int maze_type) {
    // Assign input parameters
    this->side_length = side_length;
    this->num_tiles = side_length * side_length;
    this->maze_type = maze_type;

    // Construct list of tiles and codify adjacency info
    for (int i = 0; i < side_length; i++) {
        for (int j = 0; j < side_length; j++) {
            Tile *next_tile = new Tile(j, i);
            this->tiles.push_back(next_tile);
        }
    }
    this->codify_adjacency_info();

    // Build maze
    if (maze_type == 0) {
        // Growing Tree - Recursive Backtracker Algorithm
        this->generate_growing_tree(0);
    }
    else if (maze_type == 1) {
        // Growing Tree - Prim's Algorithm
        this->generate_growing_tree(1);
    }
}

// References:
// Growing tree algorithm: https://weblog.jamisbuck.org/2011/1/27/maze-generation-growing-tree-algorithm
// Remove entry from vector: https://stackoverflow.com/questions/3385229/c-erase-vector-element-by-value-rather-than-by-position
