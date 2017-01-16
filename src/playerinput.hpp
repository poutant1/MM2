#ifndef MM2_PLAYER_INPUT_HPP
#define MM2_PLAYER_INPUT_HPP

#include <SFML/Graphics.hpp>

/**
A class for taking input from player.
*/

class PlayerInput{
public:
    sf::Keyboard::Key getKeyUp() const;
    void setKeyUp(sf::Keyboard::Key k);
    sf::Keyboard::Key getKeyDown() const;
    void setKeyDown(sf::Keyboard::Key k);
    sf::Keyboard::Key getKeyRight() const;
    void setKeyRight(sf::Keyboard::Key k);
    sf::Keyboard::Key getKeyLeft() const;
    void setKeyLeft(sf::Keyboard::Key k);
    sf::Keyboard::Key getKeyShoot() const;
    void setKeyShoot(sf::Keyboard::Key k);
    bool Up();
    bool Down();
    bool Left();
    bool Right();
    bool Shoot();
private:
    sf::Keyboard::Key keyUp, keyDown, keyRight, keyLeft, keyShoot;
};



#endif
