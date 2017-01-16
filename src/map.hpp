#ifndef MM2_MAP_HPP
#define MM2_MAP_HPP

#include "world.hpp"
#include "tilemap.hpp"
#include "gameinfo.hpp"
#include <vector>


typedef std::vector<std::vector<int>> Matrix; //Matrix for map representation

//class Tilemap;

/** Map-class reads game field from a text file in its constructor. Text file
   consists of characters representing tiles. The text file is assumed to have
   equally many characters in every row and it ends in newline-character*/

class Map {
public :
	/**
	Constructor for map. Loads the map from a map file. 
	*/
    Map(const char* filename,std::shared_ptr<World>);
    /**
    Sets the path for the tileset path to be used.
    */
	void setTilesetPath(std::string const& s){
        tilesetPath = s;
    }
    /**
    Loads the tilemap according to the map structure and tileset.
    */
    bool loadTileMap();
    /**
    Creates walls according to map structure.
    */
    void createWalls(std::shared_ptr<World> w);
    //void createCheckPoints(std::shared_ptr<World> w);
    /**
    Returns the tilemap structure.
    */
    Tilemap & getTilemap(){return tilemap;}
    /**
    Draws the tilemap.
    */
    void draw(Window &w);
    /**
    Returns the height of the map.
    */
    int getHeight() { return height; }
    /**
    Returns the idth of the map.
    */
    int getWidth() { return width; }
    /**
    Returns the tile size as a vector.
    */
    sf::Vector2u getTileSize() { return tilesize; }
    /**
    Returns the checkpoints as a vector. 
    */
    std::vector<std::shared_ptr<CheckPoint>> getCheckPoints() { return checkpoints; }
    /**
    Returns the mines of the map as a list
    */
    std::vector<std::shared_ptr<Mine>> getMines() { return mines; }
private:
    std::string name, tilesetPath;
    int width, height;
    std::shared_ptr<World> world;
    std::vector<std::string> tiletypes;
    std::vector<std::shared_ptr<CheckPoint>> checkpoints;
    std::vector<std::shared_ptr<Mine>> mines;
    Matrix mapmatrix; //Matrix for visible tiles
    Matrix cpmatrix;  //Matrix for checkpoints
    Tilemap tilemap;
    sf::Vector2u tilesize= sf::Vector2u(32,32);//tile size, we should probably change it to something that gets initialized
};
        

#endif
