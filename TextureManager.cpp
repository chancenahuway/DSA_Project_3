//
// Created by Sam on 11/20/23.
//
#include "TextureManager.h"
#include <iostream>

using namespace std;

//Redeclare static variable so it can be used elsewhere in our code
unordered_map<string, sf::Texture> TextureManager::_textures;

void TextureManager::LoadTexture(string fileName)
{
    string path = "../images/"; // OR use the variable imagesDirectory to set a different one/allow for different ones
    //IN MAIN WHERE NEEDED: TextureManager::SetImagesDirectory("whatever/file/path")
    path += fileName + ".png";
    _textures[fileName].loadFromFile(path);
}

sf::Texture& TextureManager::GetTexture(string textureName)
{
    //Check to see if hte texture already exists (i.e) has it been loaded yet?
    if(_textures.find(textureName) == _textures.end())
        LoadTexture(textureName);

    return _textures[textureName];
}

void TextureManager::Clear()
{
    _textures.clear();
}


