#ifndef MM2_PROJECTILE_HPP
#define MM2_PROJECTILE_HPP

#include "world.hpp"
#include "vehicle.hpp"
#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
/**
A class for the projectiles.
*/
class Projectile : public Object {
public :
    /**
    Constructor
    */
	Projectile(Vector2d pos, Vector2d sp, double m, sf::Texture &tex,
               std::shared_ptr<World> w);
    /**
    Updates the state of the projectile, meaning both its position and sprite.
    */
	void updateState(double dt);
    /**
    Collides the projectile with a wall.
    */
    void collide(Wall& w);
    /**
    Collides the projectile with an object.
    */
    virtual void collide(Object& o);
    ~Projectile() {}
    /**
    Returns whether the object is hit or not.
    */
    bool isHit() { return hit; }
    /**
    Sets the projectile as hit.
    */
    void setHit() { hit = true; }
    /**
    Checks whether the projectile has traveled its maximum distance.
    */
    bool maxDistanceSurpassed();
private :
    bool hit = false;
	void updatePosition(double dt);
	void updateSprite();
    std::shared_ptr<World> world;
    Vector2d spawnPos;
    double maxDistance = 750.0;
};

#endif
