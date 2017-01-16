#include "playerinput.hpp"

/**
Returns player up key value.
*/
sf::Keyboard::Key PlayerInput::getKeyUp() const{
    return keyUp;
}

/**
Sets player up key value.
*/
void PlayerInput::setKeyUp(sf::Keyboard::Key k){
    keyUp = k;
}

/**
Returns player down key value.
*/

sf::Keyboard::Key PlayerInput::getKeyDown() const{
    return keyDown;
}

/**
Sets player down key value.
*/
void PlayerInput::setKeyDown(sf::Keyboard::Key k){
    keyDown = k;
}

/**
Returns player right key value.
*/
sf::Keyboard::Key PlayerInput::getKeyRight() const{
    return keyRight;
}

/**
Sets player right key value.
*/
void PlayerInput::setKeyRight(sf::Keyboard::Key k){
    keyRight = k;
}

/**
Returns player left key value.
*/
sf::Keyboard::Key PlayerInput::getKeyLeft() const{
    return keyLeft;
}

/**
Sets player left key value.
*/
void PlayerInput::setKeyLeft(sf::Keyboard::Key k){
    keyLeft = k;
}

/**
Returns player shoot key value.
*/
sf::Keyboard::Key PlayerInput::getKeyShoot() const{
    return keyShoot;
}

/**
Sets player shoot key value.
*/
void PlayerInput::setKeyShoot(sf::Keyboard::Key k){
    keyShoot = k;
}

/**
Returns whether player is pressing his designated up key.
*/
bool PlayerInput::Up(){
    return sf::Keyboard::isKeyPressed(keyUp);
}

/**
Returns whether player is pressing his designated down key.
*/
bool PlayerInput::Down(){
    return sf::Keyboard::isKeyPressed(keyDown);
}

/**
Returns whether player is pressing his designated left key.
*/
bool PlayerInput::Left(){
    return sf::Keyboard::isKeyPressed(keyLeft);
}

/**
Returns whether player is pressing his designated right key.
*/
bool PlayerInput::Right(){
    return sf::Keyboard::isKeyPressed(keyRight);
}

/**
Returns whether player is pressing his designated shoot key.
*/
bool PlayerInput::Shoot(){
    return sf::Keyboard::isKeyPressed(keyShoot);
}
