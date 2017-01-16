#ifndef MM2_GAMEINFO_HPP
#define MM2_GAMEINFO_HPP
#include <memory>
#include <string>
#include "playerinput.hpp"

/**
*Class for storing user-defined game settings that is useful to all game screens.
*/

class GameInfo
{
public:
    /**
    Constructor
    */   
    GameInfo(){
        std::shared_ptr<PlayerInput> p1 = std::make_shared<PlayerInput>();
        std::shared_ptr<PlayerInput> p2 = std::make_shared<PlayerInput>();
        players.push_back(p1);
        players.push_back(p2);
    }
    
    /**
    Setting path of mapfile for map generation.
    */
    void set_map_path(std::string path){
        map_path = path;
    }
    
    /**    
    Returns the current path for mapfile for map generation.
    */
    std::string get_map_path(){
        return map_path;
    }
    
    /**
    Setting path for tilemap-file for map generation.
    */
    void set_tilemap_path(std::string tpath){
        tilemap_path = tpath;
    }
    
    /**
    Returns the current path for tilemap-file for map generation.
    */ 
    std::string get_tilemap_path(){
        return tilemap_path;
    }
    
    /**
     Setting the amount of laps in a race.
    */
    void set_lap_total(int number){
        laptotal = number;
    }
    
    /**
     Returns the amount of laps in a race.
    */
    int get_lap_total(){
        return laptotal;
    }
    
    /**
     Returns PlayerInput-object pointer for game controls of player
    */
    std::shared_ptr<PlayerInput> getPlayerInput(int p) {
        if (p==0)
            return players[0];
        return players[1];
    }
    
    /**
     Sets controls for player through PlayerInput-object.
    */
    void setPlayerInput(PlayerInput const & p, int player){
        if (player <2 && player >=0){
        players[player]->setKeyUp(p.getKeyUp());
        players[player]->setKeyDown(p.getKeyDown());
        players[player]->setKeyLeft(p.getKeyLeft());
        players[player]->setKeyRight(p.getKeyRight());
        players[player]->setKeyShoot(p.getKeyShoot());
        
        }
    }
    
    
    
private:
    std::string map_path = "";
    std::string tilemap_path = "";
    int laptotal = 1;
    std::vector<std::shared_ptr<PlayerInput>> players;
};


#endif
