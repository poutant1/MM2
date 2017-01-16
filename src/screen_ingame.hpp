#include "cScreen.hpp"
#include <SFML/Graphics.hpp>
/**
Screen that contains the actual gameplay.
Shares information with other sceens by using the GameInfo class.
*/
class ScreenInGame : public cScreen {
    public:
    /**
    Constructor for the gameplay screen.
    */
    ScreenInGame(std::shared_ptr<GameInfo> info) : cScreen(info){}
    int Run(sf::RenderWindow&);
};
