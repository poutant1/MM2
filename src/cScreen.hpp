#ifndef CSCREEN_INCLUDED
#define CSCREEN_INCLUDED
#include <SFML/Graphics.hpp>
#include <memory>
#include "gameinfo.hpp"
/**
A generic class for different scenes or screens inside the game.
These include the main menu, the actual game and the end screen.
*/
class cScreen
{
public:
    /**
    Constuctor for the cScreen class.
    */
    cScreen(std::shared_ptr<GameInfo> info): InfoPtr(info){}
    /**
    A function to run the scene. The actual gameplay or a menu is completely
    contained inside this function. 
    */
    virtual int Run(sf::RenderWindow &w) = 0;
    
    
    /**
    Sets the shared information class to be used between different screens 
    for the screen.
    */
    void set_infoptr(std::shared_ptr<GameInfo> info){
        InfoPtr = info;
    }
    /**
    Returns the shared information class used by the screen. 
    */
    std::shared_ptr<GameInfo> get_infoptr(){
        return InfoPtr;
    }
    
private:
    std::shared_ptr<GameInfo> InfoPtr;
};

#endif // CSCREEN_INCLUDED
