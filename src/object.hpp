#ifndef MM2_OBJECT_HPP
#define MM2_OBJECT_HPP

#include "world.hpp"
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

typedef sf::Vector2<double> Vector2d;

class Wall;
/**
Generic class for game objects, such players, checkpoints and projectiles.
*/
class Object {
public:
    const Vector2d& getPosition() const;
    void setPosition(Vector2d const& p);
    const Vector2d& getSpeed() const;
    void setSpeed(Vector2d const& s);
    /**
        virtual function for the setting of a texture.
    */
    virtual void setTexture(sf::Texture&) {};
    double getMass() const;
    void setMass(double const& m);
    double getAngle() const;
    void setAngle(double const& a);
	sf::Sprite getSprite() const;
	void draw(Window &w);
    double getRadius() const;
	
    
protected :
    /**
    Position of the object as a vector.
    */
	Vector2d position;
	/**
    Speed of the object as a vector.
    */
    Vector2d speed;
	/**
    Angle of the object in degrees.
    */
    double angle;
	/**
    Mass of the object.
    */
    double mass;
    /**
    Radius of the object.
    */
	double radius;

	bool collides(Object const& o) const;
	bool collides(Wall const& w) const;
    bool collides(CheckPoint const& cp) const;
    virtual void collide(Object& o) = 0;
    /**
    Sprite of the object.
    */
	sf::Sprite sprite;
	/**
    Texture of the object.
    */
    sf::Texture texture;
	
	
};

#endif
