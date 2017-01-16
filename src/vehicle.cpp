#include "world.hpp"
#include "objects.hpp"
#include "vector2help.hpp"
#include <SFML/System.hpp>
#include <cmath>
#include <vector>
#include <memory>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>



Vehicle::Vehicle(Vector2d pos, double orientationAngle, double maxSp, double maxF, double m, std::shared_ptr<PlayerInput> p1, std::shared_ptr<World> w) {
	position = pos;
	angle = orientationAngle;
	maxSpeed = maxSp;
	maxForce = maxF;
	mass = m;
	player = p1;
	world = w;
	sprite.setPosition(pos.x, pos.y);
	sprite.setScale(1, 1);
}

void Vehicle::updateState(double dt) {
	updateOrientation(dt);
	updatePosition(dt);
	updateSpeed(dt);
	updateSprite();
}

void Vehicle::updateOrientation(double dt) {
	if(player->Left()) angle -= (dt*angularVelocity);
	if(player->Right()) angle += (dt*angularVelocity);
}

void Vehicle::updateSpeed(double dt) {
	Vector2d dragVector = -drag*speed; //-drag * speed
	speed += (dt*dragVector);
	if(player->Up() || player->Down()) {
		Vector2d orientation = Vector2d(cos(angle*2*M_PI/360), sin(angle*2*M_PI/360));
		Vector2d acceleration = normalized(orientation) * (maxForce/mass);
		if(player->Up())	speed += (dt*acceleration);
		if(player->Down()) speed -= (dt*acceleration);
	} else if(length(speed) < 0.1) {
		speed = Vector2d(0.0, 0.0);
    }

	if(length(speed) > maxSpeed){
		setLength(speed, maxSpeed);
	}
	 
	if (player->Shoot()) {
        if (clock.getElapsedTime() > sf::seconds(0.1)){
            shoot(world);
            clock.restart();
        }
    }

	for(auto v : world->getVehicles()) {
		if(v->getPosition() != position && collides(*v)){ // Collide with another vehicle
			collide(*v);
		}
	}
    
    for(auto w : world->getWalls()) {
        if(collides(*w)) {
            collide(*w);
        }
    }

    for(auto p : world->getProjectiles()) {
        if(collides(*p)) {
            collide(*p);
            p.reset();
        }
    }
        
    for(auto c : world->getCheckPoints()) {
        if(collides(*c)) {
            collide(*c);
        }
    }
    for(auto m : world->getMines()) {
        if(collides(*m)) {
            collide(*m);
        }
    }
}

void Vehicle::updatePosition(double dt) {
	position += (dt*speed);
}

void Vehicle::updateSprite() {
	sprite.setOrigin(texture.getSize().x/2, texture.getSize().y/2);
	sprite.setPosition(position.x, position.y);
	sprite.setRotation(angle);
}
void Vehicle::setTexture(std::string path) {
	texture.loadFromFile(path);
	sprite.setTexture(texture);
	radius = sprite.getGlobalBounds().width/2;
}

void Vehicle::collide(Object& o) {
    double m1 = mass;
    double m2 = o.getMass();
    Vector2d v1 = speed;
    Vector2d v2 = o.getSpeed();
    double impulseMagn = 1.0*length(v1 - v2);
    Vector2d impulse = impulseMagn * (normalized(getPosition() - o.getPosition()));
    setSpeed(v1 + impulse/m1);
    o.setSpeed(v2 - impulse/m2);
}

void Vehicle::collide(Wall& w) {
	double width = w.getWidth();
	double height = w.getHeight();
	double r = radius;
	double oX = getPosition().x;
	double oY = getPosition().y;
	double wX = w.getPosition().x + width/2;
	double wY = w.getPosition().y + height/2;
	double xDifference = abs(oX - wX);
	double yDifference = abs(oY - wY);
	if((oX > wX + width/2) && (oX - r > wX) && xDifference >= yDifference) setPosition(Vector2d(wX + width/2 + r, oY));
	if((oX + r > wX - width/2) && (oX + r < wX) && xDifference >= yDifference) setPosition(Vector2d(wX - width/2 - r, oY));
	if((oY - r < wY + height/2) && (oY - r > wY) && xDifference < yDifference) setPosition(Vector2d(oX, wY + height/2 + r));
	if((oY + r > wY - height/2) && (oY + r < wY) && xDifference < yDifference) setPosition(Vector2d(oX, wY - height/2 - r));
}

void Vehicle::collide(Projectile& p) {
    p.setHit();
    double m1 = mass;
    Vector2d v1 = speed;
    Vector2d v2 = p.getSpeed();
    double impulseMagn = 1.0*length(v1 - v2);
    Vector2d impulse = impulseMagn * (normalized(getPosition() - p.getPosition()));
    setSpeed(v1 + impulse/m1);
	srand (time(NULL));
	double dAngle = (rand() % 180) - 90;
    angle += dAngle;
}

void Vehicle::collide(CheckPoint& c) {
    if(c.getNumber() == lastcp + 1)
        updateLastCp();
}

void Vehicle::collide(Mine& m) {
    if (m.isVisible()) {
        double x = getSpeed().x;
        double y = getSpeed().y;
        setSpeed(Vector2d(x*=(-10),y*=(-10)));
        angle += 150;
        m.detonate();
    }
}

void Vehicle::shoot(std::shared_ptr<World> world) {
    double m1 = 1; // Projectile mass
    Vector2d prjSpeed = angleToVector(angle); prjSpeed.x *= 25; prjSpeed.y *= 25  ;
    Vector2d prjPosition = position + angleToVector(angle)*(getRadius()+3);
    sf::Texture tex = ammoTexture; // Projectile texture
    std::shared_ptr<Projectile> p1 = std::make_shared<Projectile>
            (Projectile(prjPosition,prjSpeed,m1,ammoTexture,world));
    world->addProjectile(p1);
    setSpeed(speed + prjSpeed*(-0.1));
}

/*
void Vehicle::collide(Mine& m) {
    clock.restart();
    while(clock.getElapsedTime() < sf::seconds(1)) {
        angle += angularVelocity;
    }
}*/

void Vehicle::updateLastCp(){
    std::cout << "Checkpoint "<< lastcp+1 <<" passed."<< std::endl;
    lastcp++;
    
    // If the checkpoint is the last
    if ((unsigned)lastcp == world->getCheckPoints().size()) {
        currentlap++;
        lastcp = 0;
        std::cout << "Lap "<<currentlap-1<<" finished."<< std::endl;
    }
    
    
    
}


void Vehicle::setAmmoTexture(std::string path){
	ammoTexture.loadFromFile(path);
}

void Vehicle::setDrag(double d) {
    drag = d;
}

void Vehicle::setMaxForce(double f) {
    maxForce = f;
}

