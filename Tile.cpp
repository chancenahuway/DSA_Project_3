//
// Created by samso on 3/13/2024.
//

#include "Tile.h"

Tile::Tile(int x, int y) {
    this->x = x;
    this->y = y;
    _tileFront.setTexture(TextureManager::GetTexture("square"));
    _tileFront.setPosition((x-1) * 10,y * 10);
}


sf::Sprite Tile::getSprite() {
    return _tileFront;
}
