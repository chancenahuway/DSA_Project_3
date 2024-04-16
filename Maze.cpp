//
// This program was written by Samson Carter, Dylan Dixon, and Chance Nahuway.
//

#include <algorithm>
#include <random>
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


Maze::Maze(int side_length, int maze_type) : side_length(side_length), num_tiles(side_length * side_length), maze_type(maze_type) {
    // Construct list of tiles and codify adjacency info
    for (int i = 0; i < side_length; i++) {
        for (int j = 0; j < side_length; j++) {
            Tile *next_tile = new Tile(j, i);
            tiles.push_back(next_tile);
        }
    }
    codify_adjacency_info();

    // Build maze
    if (maze_type == 0) {
        // Recursive Backtracker Algorithm
        generate_growing_tree(0);
    } else if (maze_type == 1) {
        // Prim's Algorithm
        generate_growing_tree(1);
    }
}

Maze::~Maze() {
    for (Tile* tile : tiles) {
        delete tile;
    }
}

vector<Maze::Tile*>& Maze::getAllTiles() {
    return tiles;
}

vector<pair<int, int>> Maze::BFS(sf::RenderWindow& window) {
    queue<Tile*> q;
    set<Tile*> visited;
    map<Tile*, Tile*> parent;  // To reconstruct the path
    vector<pair<int, int>> path;  // Path as a vector of coordinates

    // Starting from the first tile
    Tile* start = tiles[0];    //start tile = tile 0
    Tile* end = tiles.back();  //end tile = last tile

    visited.insert(start);
    q.push(start);
    parent[start] = nullptr;  //start tile has no parent

    while (!q.empty()) {
        Tile* current = q.front();
        q.pop();

        // Visualize visiting
        current->sprite = current->visiting;
        drawAndUpdate(window);

        if (current == end) {
            // Reconstruct the path
            while (current != nullptr) {
                current->sprite = current->path;
                path.emplace_back(current->x, current->y);
                current = parent[current];
            }
            reverse(path.begin(), path.end());
            drawAndUpdate(window);
            return path;
        }

        // Explore connected tiles
        for (Tile* neighbor : current->connected_tiles) {
            if (visited.find(neighbor) == visited.end()) {
                visited.insert(neighbor);
                q.push(neighbor);
                parent[neighbor] = current;  // Mapping the path
                neighbor->sprite = neighbor->visiting;
            }
        }
        drawAndUpdate(window);
    }
    return path;  // If no path is found, return an empty vector
}

void Maze::drawAndUpdate(sf::RenderWindow& window) {
    window.clear(sf::Color::White);
    for (auto& tile : tiles) {
        window.draw(tile->sprite);
    }
    // Draw lines
    drawLines(window);

    window.display();
    sf::sleep(sf::milliseconds(10)); // Delay for visualization effect
}

void Maze::drawLines(sf::RenderWindow& window) {
    sf::RectangleShape line(sf::Vector2f(15, 1)); // Horizontal line
    line.setFillColor(sf::Color::Blue);
    sf::RectangleShape vLine(sf::Vector2f(1, 15)); // Vertical line
    vLine.setFillColor(sf::Color::Blue);

    for (unsigned int i = 0; i < tiles.size(); i++) {
        // Draw horizontal line above top row and below last row tiles
        if (i < side_length) { // Top row
            line.setPosition(tiles[i]->sprite.getPosition().x, tiles[i]->sprite.getPosition().y);
            window.draw(line);
        }

        if (i >= tiles.size() - side_length) { // Last row
            bool hasBottomNeighbor = false;
            for (auto neighbor : tiles[i]->connected_tiles) {
                if (neighbor->y > tiles[i]->y) {
                    hasBottomNeighbor = true;
                    break;
                }
            }
            if (!hasBottomNeighbor) {
                line.setPosition(tiles[i]->sprite.getPosition().x, tiles[i]->sprite.getPosition().y + 15);
                window.draw(line);
            }
        }

        // Draw vertical line for left and right side boundaries
        if (i % side_length == 0) { // Left column
            vLine.setPosition(tiles[i]->sprite.getPosition().x, tiles[i]->sprite.getPosition().y);
            window.draw(vLine);
        }

        if ((i + 1) % side_length == 0) { // Right column
            vLine.setPosition(tiles[i]->sprite.getPosition().x + 15, tiles[i]->sprite.getPosition().y);
            window.draw(vLine);
        }

        // Draw vertical lines between horizontally adjacent but not connected tiles
        if ((i + 1) % side_length != 0) { // Not in right-most column
            Tile* currentTile = tiles[i];
            Tile* rightTile = tiles[i + 1]; // Right adjacent tile

            bool isConnectedToRight = false;
            for (auto& connectedTile : currentTile->connected_tiles) {
                if (connectedTile == rightTile) {
                    isConnectedToRight = true;
                    break;
                }
            }

            if (!isConnectedToRight) {
                vLine.setPosition(currentTile->sprite.getPosition().x + 15, currentTile->sprite.getPosition().y);
                window.draw(vLine);
            }
        }

        // Draw horizontal lines between vertically adjacent but not connected tiles
        if (i < tiles.size() - side_length) { // Not in bottom-most row
            Tile* currentTile = tiles[i];
            Tile* bottomTile = tiles[i + side_length]; // Bottom adjacent tile

            bool isConnectedToBottom = false;
            for (auto& connectedTile : currentTile->connected_tiles) {
                if (connectedTile == bottomTile) {
                    isConnectedToBottom = true;
                    break;
                }
            }

            if (!isConnectedToBottom) {
                line.setPosition(currentTile->sprite.getPosition().x, currentTile->sprite.getPosition().y + 15);
                window.draw(line);
            }
        }
    }
}

void Maze::displayMaze() {
    vector<vector<char>> displayGrid(2 * side_length - 1, vector<char>(2 * side_length - 1, ' '));

    for (int i = 0; i < tiles.size(); i++) {
        int row = 2 * (tiles[i]->y);
        int col = 2 * (tiles[i]->x);
        displayGrid[row][col] = 'X';  // Mark the tile position

        for (auto& connected : tiles[i]->connected_tiles) {
            if (connected->x == tiles[i]->x + 1) {
                displayGrid[row][col + 1] = '-';  // Horizontal connection to the right
            }
            if (connected->y == tiles[i]->y + 1) {
                displayGrid[row + 1][col] = '|';  // Vertical connection downward
            }
        }
    }

    for (auto& row : displayGrid) {
        for (auto& col : row) {
            cout << col;
        }
        cout << endl;
    }
}



// References:
// Growing tree algorithm: https://weblog.jamisbuck.org/2011/1/27/maze-generation-growing-tree-algorithm
// Remove entry from vector: https://stackoverflow.com/questions/3385229/c-erase-vector-element-by-value-rather-than-by-position
