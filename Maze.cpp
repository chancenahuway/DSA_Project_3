//
// This program was written by Samson Carter, Dylan Dixon, and Chance Nahuway.
//

#include <algorithm>
#include <ctime>
#include <stack>
#include <random>
#include "Maze.h"
#include <iostream>
using namespace std;

void Maze::codifyAdjacencyInfo() {
    // Populate adjacentTiles vector for each tile
    for (unsigned int i = 0; i < tiles.size(); i++) {
        // Top left corner tile
        if (i == 0) {
            tiles[i]->adjacentTiles.push_back(tiles[i + 1]);
            tiles[i]->adjacentTiles.push_back(tiles[i + sideLength]);
        }
            // Top right corner tile
        else if (i == sideLength - 1) {
            tiles[i]->adjacentTiles.push_back(tiles[i - 1]);
            tiles[i]->adjacentTiles.push_back(tiles[i + sideLength]);
        }
            // Bottom left corner tile
        else if (i == tiles.size() - sideLength) {
            tiles[i]->adjacentTiles.push_back(tiles[i + 1]);
            tiles[i]->adjacentTiles.push_back(tiles[i - sideLength]);
        }
            // Bottom right corner tile
        else if (i == tiles.size() - 1) {
            tiles[i]->adjacentTiles.push_back(tiles[i - 1]);
            tiles[i]->adjacentTiles.push_back(tiles[i - sideLength]);
        }
            // Top exterior tiles
        else if (i < sideLength - 1) {
            tiles[i]->adjacentTiles.push_back(tiles[i - 1]);
            tiles[i]->adjacentTiles.push_back(tiles[i + 1]);
            tiles[i]->adjacentTiles.push_back(tiles[i + sideLength]);
        }
            // Bottom exterior tiles
        else if (tiles.size() - sideLength < i && i < tiles.size()) {
            tiles[i]->adjacentTiles.push_back(tiles[i - 1]);
            tiles[i]->adjacentTiles.push_back(tiles[i + 1]);
            tiles[i]->adjacentTiles.push_back(tiles[i - sideLength]);
        }
            // Left exterior tiles
        else if (i % sideLength == 0 && i < tiles.size() - sideLength) {
            tiles[i]->adjacentTiles.push_back(tiles[i + 1]);
            tiles[i]->adjacentTiles.push_back(tiles[i - sideLength]);
            tiles[i]->adjacentTiles.push_back(tiles[i + sideLength]);
        }
            // Right exterior tiles
        else if (i % sideLength == sideLength - 1 && sideLength - 1 < i && i < tiles.size() - 1) {
            tiles[i]->adjacentTiles.push_back(tiles[i - 1]);
            tiles[i]->adjacentTiles.push_back(tiles[i - sideLength]);
            tiles[i]->adjacentTiles.push_back(tiles[i + sideLength]);
        }
            // Interior tiles
        else {
            tiles[i]->adjacentTiles.push_back(tiles[i - 1]);
            tiles[i]->adjacentTiles.push_back(tiles[i + 1]);
            tiles[i]->adjacentTiles.push_back(tiles[i - sideLength]);
            tiles[i]->adjacentTiles.push_back(tiles[i + sideLength]);
        }
    }
}

void Maze::generateGrowingTree(int flavor) {
    // Construct a temporary list of tiles, starting with one random tile
    srand(time(nullptr));

    vector<Tile*> temp;
    int random1 = rand() % (this->numTiles);
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
        for (int i = 0; i < active->adjacentTiles.size(); i++) {
            if ((active->adjacentTiles[i]->connectedTiles).empty()) {
                unconnected_adjacent_tiles.push_back(active->adjacentTiles[i]);
            }
        }
        // If active has no unconnected adjacent tiles, remove active from temp
        if (unconnected_adjacent_tiles.empty()) {
            temp.erase(std::remove(temp.begin(), temp.end(), active), temp.end());
        }
            // Otherwise, connect active and one of its unconnected adjacent tiles to each other, and add that tile to temp
        else {
            int random3 = rand() % unconnected_adjacent_tiles.size();
            active->connectedTiles.push_back(unconnected_adjacent_tiles[random3]);
            unconnected_adjacent_tiles[random3]->connectedTiles.push_back(active);
            temp.push_back(unconnected_adjacent_tiles[random3]);
        }
    }
}


Maze::Maze(int sideLength, int mazeType) : sideLength(sideLength), numTiles(sideLength * sideLength), mazeType(mazeType) {
    // Construct list of tiles and codify adjacency info
    for (int i = 0; i < sideLength; i++) {
        for (int j = 0; j < sideLength; j++) {
            Tile *next_tile = new Tile(j, i);
            tiles.push_back(next_tile);
        }
    }
    codifyAdjacencyInfo();

    // Build maze
    if (mazeType == 0) {
        // Recursive Backtracker Algorithm
        generateGrowingTree(0);
    } else if (mazeType == 1) {
        // Prim's Algorithm
        generateGrowingTree(1);
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

vector<pair<int, int>> Maze::dijkstraAlgorithm(sf::RenderWindow& window) {
    priority_queue<pair<int, Tile*>, vector<pair<int, Tile*>>, greater<pair<int, Tile*>>> pq;
    set<Tile*> visited;
    map<Tile*, Tile*> parent;
    map<Tile*, int> distance;
    vector<pair<int, int>> path;

    Tile* start = tiles[0];
    Tile* end = tiles.back();

    for (Tile* tile : tiles) {
        distance[tile] = INT_MAX;
    }
    distance[start] = 0;

    pq.push({0, start});

    while (!pq.empty()) {
        Tile* current = pq.top().second;
        pq.pop();

        visited.insert(current);

        current->sprite = current->visiting;
        drawAndUpdate(window);

        if (current == end) {
            while (current != nullptr) {
                current->sprite = current->path;
                path.emplace_back(current->x, current->y);
                current = parent[current];
            }
            reverse(path.begin(), path.end());
            drawAndUpdate(window);
            return path;
        }

        for (Tile* neighbor : current->connectedTiles) {
            int new_distance = distance[current] + 1;

            if (new_distance < distance[neighbor]) {
                distance[neighbor] = new_distance;
                parent[neighbor] = current;
                pq.push({new_distance, neighbor});
                neighbor->sprite = neighbor->visiting;
            }
        }
        drawAndUpdate(window);
    }
    return path;
}

vector<pair<int, int>> Maze::depthFirstSearch(sf::RenderWindow& window) {
    stack<Tile*> s;
    set<Tile*> visited;
    map<Tile*, Tile*> parent;  // To reconstruct the path
    vector<pair<int, int>> path;  // Path as a vector of coordinates

    // Starting from the first tile
    Tile* start = tiles[0];    //start tile = tile 0
    Tile* end = tiles.back();  //end tile = last tile

    visited.insert(start);
    s.push(start);
    parent[start] = nullptr;  //start tile has no parent

    while (!s.empty()) {
        Tile* current = s.top();
        s.pop();

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
        for (Tile* neighbor : current->connectedTiles) {
            if (visited.find(neighbor) == visited.end()) {
                visited.insert(neighbor);
                s.push(neighbor);
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
    /*sf::sleep(sf::milliseconds(10)); // Delay for visualization effect*/
}

void Maze::drawLines(sf::RenderWindow& window) {
    sf::RectangleShape line(sf::Vector2f(15, 1)); // Horizontal line
    line.setFillColor(sf::Color::Blue);
    sf::RectangleShape vLine(sf::Vector2f(1, 15)); // Vertical line
    vLine.setFillColor(sf::Color::Blue);

    for (unsigned int i = 0; i < tiles.size(); i++) {
        // Draw horizontal line above top row and below last row tiles
        if (i < sideLength) { // Top row
            line.setPosition(tiles[i]->sprite.getPosition().x, tiles[i]->sprite.getPosition().y);
            window.draw(line);
        }

        if (i >= tiles.size() - sideLength) { // Last row
            bool hasBottomNeighbor = false;
            for (auto neighbor : tiles[i]->connectedTiles) {
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
        if (i % sideLength == 0) { // Left column
            vLine.setPosition(tiles[i]->sprite.getPosition().x, tiles[i]->sprite.getPosition().y);
            window.draw(vLine);
        }

        if ((i + 1) % sideLength == 0) { // Right column
            vLine.setPosition(tiles[i]->sprite.getPosition().x + 15, tiles[i]->sprite.getPosition().y);
            window.draw(vLine);
        }

        // Draw vertical lines between horizontally adjacent but not connected tiles
        if ((i + 1) % sideLength != 0) { // Not in right-most column
            Tile* currentTile = tiles[i];
            Tile* rightTile = tiles[i + 1]; // Right adjacent tile

            bool isConnectedToRight = false;
            for (auto& connectedTile : currentTile->connectedTiles) {
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
        if (i < tiles.size() - sideLength) { // Not in bottom-most row
            Tile* currentTile = tiles[i];
            Tile* bottomTile = tiles[i + sideLength]; // Bottom adjacent tile

            bool isConnectedToBottom = false;
            for (auto& connectedTile : currentTile->connectedTiles) {
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
    vector<vector<char>> displayGrid(2 * sideLength - 1, vector<char>(2 * sideLength - 1, ' '));

    for (int i = 0; i < tiles.size(); i++) {
        int row = 2 * (tiles[i]->y);
        int col = 2 * (tiles[i]->x);
        displayGrid[row][col] = 'X';  // Mark the tile position

        /*for (auto& connected : tiles[i]->connectedTiles) {
            if (connected->x == tiles[i]->x + 1) {
                displayGrid[row][col + 1] = '-';  // Horizontal connection to the right
            }
            if (connected->y == tiles[i]->y + 1) {
                displayGrid[row + 1][col] = '|';  // Vertical connection downward
            }
        }*/
    }

    /*for (auto& row : displayGrid) {
        for (auto& col : row) {
            cout << col;
        }
        cout << endl;
    }*/
}



// References:
// Growing tree algorithm: https://weblog.jamisbuck.org/2011/1/27/maze-generation-growing-tree-algorithm
// Remove entry from vector: https://stackoverflow.com/questions/3385229/c-erase-vector-element-by-value-rather-than-by-position
