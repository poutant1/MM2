#include <SFML/Graphics.hpp>
#include "cScreen.hpp"
/**
Class dor the menu screen.
*/
class ScreenMenu : public cScreen
{
    public:
    /**
    Constructor for the menu screen.
    */
    ScreenMenu(std::shared_ptr<GameInfo> info) : cScreen(info){}
    /**
    The actual menu screen functionality.
    */
    int Run(sf::RenderWindow& w);

};

