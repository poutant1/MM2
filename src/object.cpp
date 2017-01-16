#include "objects.hpp"
#include "vector2help.hpp"
#include <cmath>
#include <iostream>
/**
Returns the objects position in pixels as a 2d vector. 
*/
const Vector2d& Object::getPosition() const{
    return position;
}

/**
Sets the position of an object.
*/
void Object::setPosition(Vector2d const& p){
    position = p;
}

/**
Returns the speed of an object.
*/
const Vector2d& Object::getSpeed() const{
    return speed;
}

/**
Sets the speed of an object.
*/
void Object::setSpeed(Vector2d const& s){
    speed=s;
}

/**
Returns the mass of an object.
*/
double Object::getMass() const{
    return mass;
}

/**
Sets the mass of an object.
*/
void Object::setMass(double const& m){
    mass = m;
}

/**
Returns the angle of an object in degrees.
*/
double Object::getAngle() const{
    return angle;
}

/**
Sets the angle of an object in degrees.
*/
void Object::setAngle(double const& a){
    angle = a;
}
/**
Returns the radius of an object.
*/
double Object::getRadius() const {
    return radius;
}
/**
Returns the sprite of an object.
*/
sf::Sprite Object::getSprite() const{
	return sprite;
}

/**
Draws an object on a window. 
*/
void Object::draw(Window &w) {
	w.draw(getSprite());
}

/**
Checks if an object collides with another object.
*/
bool Object::collides(Object const& o) const {
	double distance = length(getPosition() - o.getPosition());
	return distance < (radius + o.radius);
}
/**
Checks if an object collides with a wall.
*/
bool Object::collides(Wall const& w) const {

	double width = w.getWidth();
	double height = w.getHeight();
	double r = radius;
	double oX = getPosition().x;
	double oY = getPosition().y;
	double wX = w.getPosition().x + width/2;
	double wY = w.getPosition().y + height/2;		
	double distanceX = abs(oX - wX);
	double distanceY = abs(oY - wY);

	if(distanceX > (width/2 + r)) { return false; }
	if(distanceY > (height/2 + r)) { return false; }
	
	if(distanceX <= width/2) { return true; }
	if(distanceY <= height/2) { return true; }

	double cornerDistance = pow((distanceX - width/2), 2) + pow((distanceY - height/2), 2);
	return cornerDistance <= pow(r, 2);
}
/**
checks if an object collides with a map checkpoint.
*/
bool Object::collides(CheckPoint const& cp) const {
    
    // Fetch checkpoint data
    int width = cp.getWidth();
    int height = cp.getHeight();
    int cpx = cp.getPosition().x + width/2;
    int cpy = cp.getPosition().y + height/2;
    
    // Fetch vehicle data
    double vx = getPosition().x;
    double vy = getPosition().y;
    double radius = getRadius();
    
    double distanceX = abs(vx - cpx);
    double distanceY = abs(vy - cpy);
    
    if(distanceX > (width/2 + radius)) { return false; }
    if(distanceY > (height/2 + radius)) { return false; }
    
    if(distanceX <= width/2) { return true; }
    if(distanceY <= height/2) { return true; }
    
    double cornerDistance = pow((distanceX - width/2), 2) + pow((distanceY - height/2), 2);
    return cornerDistance <= pow(radius, 2);
}

