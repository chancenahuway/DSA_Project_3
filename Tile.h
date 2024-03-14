//
// Created by samso on 3/13/2024.
//

#ifndef LEARNSFML_TILE_H
#define LEARNSFML_TILE_H
#pragma once
#include <vector>
#include "TextureManager.h"

using namespace std;


class Tile {
    int x;
    int y;
    sf::Sprite _tileFront;

    // Tile member functions
    sf::Sprite& GetSprite();


public:


// Tile constructor
Tile(int x, int y);



// Tile member variables
vector<Tile*> adjacent_tiles;
vector<Tile*> connected_tiles;

    sf::Sprite getSprite();
};



#endif //LEARNSFML_TILE_H
