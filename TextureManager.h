//
// Created by Sam on 11/20/23.
//

#ifndef HELLOSFML_TEXTUREMANAGER_H
#define HELLOSFML_TEXTUREMANAGER_H
#pragma once
#include <unordered_map>
#include <string>
#include <SFML/Graphics.hpp>

using std::unordered_map;
using std::string;

class TextureManager
{
    //static == one and only one of these in memory EVER
    //because it is static, it can only be accessed through static functions
    static unordered_map<string, sf::Texture> _textures;
    static void LoadTexture(string textureName); //LoadTexture("space")
    static string imagesDirectory; //maybe not all images are in the same file/ Need to access multiple directories
public:
    static sf::Texture& GetTexture(string textureName); //GetTexture("space");
    static void SetImagesDirectory(string directoryPath);
    //IN MAIN WHERE NEEDED: TextureManager::SetImagesDirectory("whatever/file/path")
    static void Clear(); //Call this once at the end of main()

};


#endif //HELLOSFML_TEXTUREMANAGER_H
