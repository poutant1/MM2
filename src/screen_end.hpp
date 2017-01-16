#include "cScreen.hpp"
/**
End screen.
*/
class ScreenEnd : public cScreen
{
    public:
    /**
    Constructor for end screen.
    */
    ScreenEnd(std::shared_ptr<GameInfo> info) : cScreen(info){}
    /**
    The actual end screen functionality.
    */
    int Run(sf::RenderWindow &w);
};
