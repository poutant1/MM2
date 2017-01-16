#ifndef MM2_MINE_HPP
#define MM2_MINE_HPP

#include "object.hpp"
/**
A class for the sole obstacle in the game.
*/
class Mine : public Object {
public:
    Mine(){}
    /**
    Constructor
    */
    Mine(Vector2d, int);
    /**
    Collides the mine with another object.
    */
    virtual void collide(Object& o);
    /**
    Sets the texture for the mine.
    */
    virtual void setTexture(sf::Texture&);
    /**
    Updates the mine's state, including its position.
    */
    void updateState();
    /**
    Checks whether the mine is inactive or not.
    */
    bool isVisible();
    /**
    Sets the mine inactive.
    */
    void setInvisible();
    /**
    Detonates the mine when it comes to contact with a vehicle.
    */
    void detonate();
    /**
    Draws the mine on the window.
    */
    void draw(Window& w);
    /**
    Returns the clock that controls the cooldown of the mine.
    */
    sf::Clock& getClock();
private:
    sf::Clock clock;
    sf::Texture tex;
    bool visible = true;
    sf::Time timeInactive = sf::seconds(5);
};

#endif // MM_MINE_HPP
