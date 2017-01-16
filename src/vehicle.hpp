#ifndef MM2_VEHICLE_HPP
#define MM2_VEHICLE_HPP

#include "world.hpp"
#include "objects.hpp"
#include "playerinput.hpp"
#include "mine.hpp"
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <memory>



/**
A structure for setting the initial configurations for
vehicles in a map.
*/
struct VehicleInfo {
    Vector2d position1;
    Vector2d position2;
    double orientation;
    double maxSp;
    double maxF;
    double mass;
    double drag;
};

/**
A class for containing the vehicles in the game.
A vehicle is derived from the object class, and therefore has
the physical properties that an object has.
*/

class Vehicle : public Object {
public : 
	Vehicle() {}
    /**
    Constructor
    */
	Vehicle(Vector2d pos, double orientationAngle, double maxSp, double maxF, double m, std::shared_ptr<PlayerInput> p1, std::shared_ptr<World> w);
    /**
    Updates the state of the vehicle. This includes both the physics as well as the input for the vehicle.
    */
	void updateState(double dt);
    /**
    Sets the texture for the vehicle. 
    */
    virtual void setTexture(std::string path);
	/**
    Sets a texture for the ammo type the vehicle uses.
    */
    void setAmmoTexture(std::string path);
    /**
    This function handles the shooting of a projectile.
    */
    void shoot(std::shared_ptr<World> world);
    /**
    Returns the lap the vehicle is currently on.
    */
    int getLap() const {return currentlap;}
    /**
     This function sets the vehicle drag
     */
    void setDrag(double);
    /**
     This function sets the vehicle max Force
     */
    void setMaxForce(double);
    
private :
	//Functions for updating the state of vehicle.
    /**
    Updates the vehicle's position based on its speed.
    */
	void updatePosition(double dt);
	/**
    Updates the vehicle's speed.
    */
    void updateSpeed(double dt);
    /**
    Updates the vehicle's orientation.
    */
	void updateOrientation(double dt);
    /**
    Updates the vehicle's checkpoint.
    */
    void updateLastCp();

	//Constants that define the physics of the vehicle.
	double maxSpeed;
	double maxForce;
	double drag = 0.1;
	double angularVelocity = 6;
    int lastcp = 0;
    int currentlap = 0;

	//The player that controls the vehicle.
	std::shared_ptr<PlayerInput> player;
	
	//The world class tied to the vehicle.
	std::shared_ptr<World> world;

	//Vehicle graphics.
	sf::Texture ammoTexture;
	void updateSprite();
    sf::Clock clock;
    virtual void collide(Object& o);
    virtual void collide(Projectile& p);
    virtual void collide(Wall& w);
    virtual void collide(CheckPoint& c);
    virtual void collide(Mine& m);
    //virtual void collide(Mine& m);
};

#endif
