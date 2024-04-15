#include "Maze.h"
#include <iostream>
using namespace std;

int main() {
    Maze maze(10, 1);  //small maze : easier example
    maze.displayMaze();  // Display the maze layout
    cout << "\nFinding path through the maze:\n";

    vector<pair<int, int>> path = maze.BFS();
    for (auto& coord : path) {
        cout << "(" << coord.first << ", " << coord.second << ")" << endl;
    }

    return 0;
}
