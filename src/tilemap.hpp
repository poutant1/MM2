#ifndef MM2_TILEMAP_HPP
#define MM2_TILEMAP_HPP
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <string> 

typedef std::vector<std::vector<int>> Matrix;
/**
A class for the drawing of the game world map.
Tilemap contains the tiles that form the game map.
This class is a slightly modified version of an example written by Laurent Gomila,
licensed under the zlib/png license.
*/
class Tilemap : public sf::Drawable, public sf::Transformable{
public:
    /**
    Creates the tilemap from a repserentation of the map as well as a tileset.
    */
    bool load(std::string const& tileSetPath, sf::Vector2u tilesize, Matrix map, int width, int height);
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const{
        // apply the transform
        states.transform *= getTransform();
        // apply the tileset texture
        states.texture = &tileSet;
        // draw the vertex array
        target.draw(vertices, states);
    }
    sf::VertexArray vertices;
    sf::Texture tileSet;
};


#endif
