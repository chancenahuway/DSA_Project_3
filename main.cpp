#include "Maze.h"
#include "TextureManager.h"
#include <iostream>
using namespace std;

int main() {
    cout << "Hello! Welcome to the Rat Race Rebels' Maze Simulator!" << endl << endl;
    cout << "Please begin by choosing which algorithm you'd like to generate the maze!" << endl << endl;
    cout << "Enter 0 for the Recursive Backtracker Algorithm or 1 for Prim's Algorith: ";
    int maze_type = -1;
    while (maze_type != 0 and maze_type != 1) {
        if (!(cin >> maze_type)) {
            cout << endl << "You have not selected a valid maze-generating algorithm. Please try again!" << endl << endl;
            cout << "Enter 0 for the Recursive Backtracker Algorithm or 1 for Prim's Algorith: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            maze_type = -1;
            continue;
        }
        cout << endl;
        if (maze_type !=0 and maze_type != 1) {
            cout << "You have not selected a valid maze-generating algorithm. Please try again!" << endl << endl;
            cout << "Enter 0 for the Recursive Backtracker Algorithm or 1 for Prim's Algorith: ";
            maze_type = -1;
        }
    }
    if (maze_type == 0) {
        cout << "Thank you for choosing the Recursive Backtracker Algorithm!" << endl << endl;
    }
    else if (maze_type == 1) {
        cout << "Thank you for choosing Prim's Algorithm!" << endl << endl;
    }
    cout << "Next, please enter how many tiles tall and how many tiles wide you'd like the the maze to be!" << endl << endl;
    cout << "Enter any number between 20 and 100: ";
    int maze_size = -1;
    while (maze_size < 20 or maze_size > 100) {
        if (!(cin >> maze_size)) {
            cout << endl << "You have not selected a valid maze size. Please try again!" << endl << endl;
            cout << "Enter any number between 20 and 100: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            maze_size = -1;
            continue;
        }
        cout << endl;
        if (maze_size < 20 or maze_size > 100) {
            cout << "You have not selected a valid maze size. Please try again!" << endl << endl;
            cout << "Enter any number between 20 and 100: ";
        }
    }
    cout << "Thank you for choosing a maze of dimensions " << maze_size << " tiles tall by " << maze_size << " tiles wide!" << endl << endl;

    Maze maze(maze_size, maze_type);
    maze.displayMaze();

    cout << "Finally, please select which algorithm you'd like to solve the maze!" << endl << endl;
    cout << "Enter 0 for Dijkstra's Algorithm or 1 for a Depth First Search: ";
    int search_type = -1;
    while (search_type != 0 and search_type != 1) {
        if (!(cin >> search_type)) {
            cout << endl << "You have not selected a valid maze-solving algorithm. Please try again!" << endl << endl;
            cout << "Enter 0 for Dijkstra's Algorithm or 1 for a Depth First Search: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            search_type = -1;
            continue;
        }
        cout << endl;
        if (search_type !=0 and search_type != 1) {
            cout << "You have not selected a valid maze-solving algorithm. Please try again!" << endl << endl;
            cout << "Enter 0 for Dijkstra's Algorithm or 1 for a Depth First Search: ";
        }
    }
    if (search_type == 0) {
        cout << "Thank you for choosing Dijkstra's Algorithm!" << endl << endl;
    }
    else if (search_type == 1) {
        cout << "Thank you for choosing a Depth First Search!" << endl << endl;
    }
    cout << "Finding path through the maze:";

    int windowSize = maze.getSideLength() * 15;
    sf::RenderWindow window(sf::VideoMode(windowSize + 100, windowSize + 100), "SFML Window");

    if (search_type == 0) {
        vector<pair<int, int>> path = maze.dijkstraAlgorithm(window);
    }
    else if (search_type == 1) {
        vector<pair<int, int>> path = maze.depthFirstSearch(window);
    }

    // Event loop to keep window open after maze is solved
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
