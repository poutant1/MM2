#include "tilemap.hpp"
#include "vector2help.hpp"
#include <iostream>

//heavily adapted from sfml's vertex array tutorial
bool Tilemap::load(std::string const& tileSetPath, sf::Vector2u tileSize, Matrix map, int width, int height){
    //load tileset to our tileset texture
    if (!tileSet.loadFromFile(tileSetPath))
        return false;
    //create our set of rectangles. Each rectangle needs four vertices.
    //vertices are not shared.
    vertices.setPrimitiveType(sf::Quads);
    vertices.resize(width*height*4);
    
    for (int j = 0;j<height;j++){
        for (int i = 0;i<width;i++){
            
            //get tile type, e.g. road, offroad...
            
            int tileType = map[j][i];
            
            
            
            //texture tile position
            //i is the remainder of our type per tile row count
            //we can divide freely since tileset size is multiple of tile size
            int ti = tileType % (tileSet.getSize().x / tileSize.x);
            int tj = tileType / (tileSet.getSize().y / tileSize.y);
            
            //get pointer to our tile
            sf::Vertex* quad = &vertices[(i+j*width)*4];
            
            // define our tile's corner positions
            quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
            quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
            quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
            quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);
            
             // define its 4 texture coordinates
            quad[0].texCoords = sf::Vector2f(ti * tileSize.x, tj * tileSize.y);
            quad[1].texCoords = sf::Vector2f((ti + 1) * tileSize.x, tj * tileSize.y);
            quad[2].texCoords = sf::Vector2f((ti + 1) * tileSize.x, (tj + 1) * tileSize.y);
            quad[3].texCoords = sf::Vector2f(ti * tileSize.x, (tj + 1) * tileSize.y);

            
            
        }
    }
    
    return true;
}
