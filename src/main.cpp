#include <SFML/Graphics.hpp>
#include "screens.hpp"
#include "map.hpp"
#include "playerinput.hpp"
#include "vehicle.hpp"
#include "gameinfo.hpp"
#include <vector>
#include <iostream>
#include <memory>

int main(){
    // Initialzation of object for game settings:
    std::shared_ptr<GameInfo> infoptr = std::make_shared<GameInfo>(GameInfo());
    
    // Cointainer for different stages of the game
    std::vector<cScreen*> screens;
    
    // Create screens for different game modes and push them to container
    ScreenMenu menu(infoptr);
    ScreenInGame ingame(infoptr);
    ScreenEnd endgame(infoptr);
    
    screens.push_back(&menu); // index 0
    screens.push_back(&ingame); // index 1
    screens.push_back(&endgame); // index 2

    /*
    An indexing value to control the transition of game states.
    To control the program screens, return different indices for screen from the Run function.
    */
     int screen = 0;
    
    // Creating a (render)window
    sf::RenderWindow window(sf::VideoMode(1200, 600), "Micro Machines");
    
    while(screen >= 0) {
        /*
         Call the Run function of a screen.
         Each screens Run function is responsible for a game mode.
         Modes are changed through returning indices from the Run function to the screen indexing variable.
         */
        screen = screens[screen]->Run(window);
    }
    
    window.close();
    return 0;
}
