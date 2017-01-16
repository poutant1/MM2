#ifndef MM2_WALLS_HPP
#define MM2_WALLS_HPP

#include "object.hpp"
/**
A class for the walls in our game world.
*/
class Wall : public Object {
public:
    Wall() { }
    /**
    Constructor
    */
    Wall(Vector2d pos, int w, int h, double orientationAngle = 0) {
        position = pos;
        angle = orientationAngle;
        sf::Texture tex; tex.create(w, h);
        sprite.setTexture(tex);
        sprite.setPosition(pos.x, pos.y);
        sprite.setScale(1,1);
	width = w;
	height = h;
    }
    /**
    A function for colliding with objects.
    */
    void collide(Object& o);
    /**
    Returns the width of the wall
    */
	const double& getWidth() const;
    /**
    Returns the height of the wall.
    */
	const double& getHeight() const;
private:
	double width;
	double height;
};

#endif
